// Console input and output.
// Input is from the keyboard or serial port.
// Output is written to the screen and serial port.

#include "types.h"
#include "defs.h"
#include "param.h"
#include "traps.h"
#include "spinlock.h"
#include "sleeplock.h"
#include "fs.h"
#include "file.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "x86.h"

#define BACKSPACE 0x100
#define CRTPORT 0x3d4
static ushort *crt = (ushort*)P2V(0xb8000);  // CGA memory

static int panicked = 0;

static struct {
	struct spinlock lock;
	int locking;
} cons;

enum console_color {				// Upper byte for VGA is the color byte - lower byte will be the character to print
	COLOR_BLACK 		= 0x0000,	
	COLOR_BLUE		= 0x0100,
	COLOR_GREEN 		= 0x0200,
	COLOR_CYAN 		= 0x0300,
	COLOR_RED 		= 0x0400,
	COLOR_MAGENTA 		= 0x0500,
	COLOR_BROWN 		= 0x0600,
	COLOR_LIGHT_GRAY 	= 0x0700,
	COLOR_DARK_GRAY 	= 0x0800,
	COLOR_LIGHT_BLUE 	= 0x0900,
	COLOR_LIGHT_GREEN 	= 0x0A00,
	COLOR_LIGHT_CYAN 	= 0x0B00,
	COLOR_LIGHT_RED 	= 0x0C00,
	COLOR_LIGHT_MAGENTA 	= 0x0D00,
	COLOR_LIGHT_BROWN 	= 0x0E00,
	COLOR_WHITE 		= 0x0F00	
};

static enum console_color current_color_setting = COLOR_LIGHT_GRAY;

static void consputc(int, enum console_color);

static void printint(int xx, int base, int sign)
{
	static char digits[] = "0123456789abcdef";
	char buf[16];
	int i;
	uint x;

	if(sign && (sign = xx < 0))
		x = -xx;
	else
		x = xx;

	i = 0;
	do{
		buf[i++] = digits[x % base];
	}while((x /= base) != 0);

	if(sign)
		buf[i++] = '-';

	while(--i >= 0)
		consputc(buf[i], current_color_setting);
}

int get_cursor_position()
{
	int pos;

	// Cursor position: col + 80*row.
	outb(CRTPORT, 14);
	pos = inb(CRTPORT+1) << 8;
	outb(CRTPORT, 15);
	pos |= inb(CRTPORT+1);

	return pos;
}

void set_cursor_position(int position)
{
	outb(CRTPORT, 14);
	outb(CRTPORT+1, position>>8);
	outb(CRTPORT, 15);
	outb(CRTPORT+1, position);
	crt[position] = ' ' | 0x0700;
}

void scroll_up(int position)
{
	memmove(crt, crt+80, sizeof(crt[0])*24*80);			// move all console output up one line
	position = 24 * 80; 						// put cursor at beginning of last line
	memset(crt+position, 0, sizeof(crt[0])*(25*80 - position)); 	// clear the last line

	set_cursor_position(position);
}

void clear_terminal();

// Print to the console. only understands %d, %x, %p, %s.
void cprintf(char *fmt, ...)
{
	int i, c, locking;
	uint *argp;
	char *s;

	locking = cons.locking;
	if(locking)
		acquire(&cons.lock);

	if (fmt == 0)
		panic("null fmt");

	argp = (uint*)(void*)(&fmt + 1);
	int position = get_cursor_position();

	for(i = 0; (c = fmt[i] & 0xff) != 0; i++)
	{
		if(c == '#')
			clear_terminal();

		if(c == '\t')
		{
			position = get_cursor_position();
			position = position % 80;		// this will set the position = column #
			position = (position + 1) % 4;	// this will compute how many spaces need to be added to reach a multiple of 4 for the column number
			if(position == 0) position = 4;    // set the position to be 4 if it is on a tab boundary

			while(position > 0) 		// put spaces until we reach tab boundary
			{
				consputc(' ', current_color_setting);
				--position;
			}

			continue;      
		}

		if(c != '%')
		{
			consputc(c, current_color_setting);
			continue;
		}
    
		c = fmt[++i] & 0xff;
    
		if(c == 0)
			break;
    
		switch(c)
		{
			case 'd':
				printint(*argp++, 10, 1);
				break;

			case 'x':
			case 'p':
				printint(*argp++, 16, 0);
				break;
			
			case 's':
				if((s = (char*)*argp++) == 0)
				s = "(null)";
				for(; *s; s++)
					consputc(*s, current_color_setting);
				break;

			case '%':
				consputc('%', current_color_setting);
				break;

			default:
				// Print unknown % sequence to draw attention.
				consputc('%', current_color_setting);
				consputc(c, current_color_setting);
				consputc('B', current_color_setting);
				break;
		}
	}

	if(locking)
		release(&cons.lock);
}

void panic(char *s)
{
	int i;
	uint pcs[10];

	cli();
	cons.locking = 0;
	// use lapiccpunum so that we can call panic from mycpu()
	cprintf("lapicid %d: panic: ", lapicid());
	cprintf(s);
	cprintf("\n");
	getcallerpcs(&s, pcs);
	
	for(i=0; i<10; i++)
		cprintf(" %p", pcs[i]);
	panicked = 1; // freeze other CPU
	
	for(;;)
		;
}


static void cgaputc(int c, enum console_color foreground_color);

void cgaputc_n(int c, int n, enum console_color foreground_color)
{
	while(n > 0)
	{
		cgaputc(c, foreground_color);
		--n;
	}
}

static void cgaputc(int c, enum console_color foreground_color)
{
	int pos = get_cursor_position();

	if(c == '\n')
		pos += 80 - pos%80;
	else if(c == BACKSPACE)
	{
		if(pos > 0) --pos;
	}
	else if(c == '\t')
	{
		int spaces = (pos + 1) % 8;		// determine how many space characters to add so it is a multiple of 4
		if (spaces == 0)
			spaces = 4;

		cgaputc_n(32, spaces, COLOR_LIGHT_GRAY);  // 32 = ASCII code for space char - ' '
	}
	else
		crt[pos++] = (c & 0xFF) | foreground_color; 
//		crt[pos++] = (c&0xff) | 0x0700;  	// light gray on white

	if(pos < 0 || pos > 25*80)
		panic("pos under/overflow");

	if((pos/80) >= 25)
		scroll_up(pos);
	else
		set_cursor_position(pos);
}

void clear_terminal()
{
	memset(crt, 0, sizeof(crt[0])*25*80); 	// clear the entire screen
	set_cursor_position(0);			// reset cursor to top left
}

void write_header()
{
	cprintf("Welcome to Simon!\n\n");
	cprintf("To see a list of commands, type \"command\" and press ENTER\n\n");
  
/*
  int pos = 0;

  char space = ' ';
  char _S = 'S';
  char _I = 'I';
  char _M = 'M';
  char _O = 'O';
  char _N = 'N';

  while(pos < 80)
  {
    // Cursor position: col + 80*row.
    outb(CRTPORT, 14);
    pos = inb(CRTPORT+1) << 8;
    outb(CRTPORT, 15);
    pos |= inb(CRTPORT+1);

    if(pos < 37 || pos > 41)
      crt[pos++] = (space & 0xff) | 0x8000; // Black on dark grey
    else if (pos == 37)
      crt[pos++] = (_S & 0xff) | 0x8000; // Black on dark grey
    else if (pos == 37)
      crt[pos++] = (_I & 0xff) | 0x8000; // Black on dark grey
    else if (pos == 37)
      crt[pos++] = (_M & 0xff) | 0x8000; // Black on dark grey
    else if (pos == 37)
      crt[pos++] = (_O & 0xff) | 0x8000; // Black on dark grey
    else if (pos == 37)
      crt[pos++] = (_N & 0xff) | 0x8000; // Black on dark grey

    outb(CRTPORT, 14);
    outb(CRTPORT+1, pos>>8);
    outb(CRTPORT, 15);
    outb(CRTPORT+1, pos);

  }
*/
}

void initialize_terminal()
{
	clear_terminal();
	write_header();
}

void consputc(int c, enum console_color color)
{
	if(panicked)
	{
		cli();
		for(;;)
      			;
	}

	cgaputc(c, color);
}

#define INPUT_BUF 128
struct {
	char buf[INPUT_BUF];
	uint r;  // Read index
	uint w;  // Write index
	uint e;  // Edit index
} input;

#define C(x)  ((x)-'@')  // Control-x

void consoleintr(int (*getc)(void))	// called from kdb.c with function 'kdbgetc'
{
	int c, doprocdump = 0;

	acquire(&cons.lock);
	while((c = getc()) >= 0)
	{
		switch(c)
		{
			case C('P'):  	// Process listing.
					// procdump() locks cons.lock indirectly; invoke later
				doprocdump = 1;
				break;
			
			case C('U'):  // Kill line.
				while(input.e != input.w && input.buf[(input.e-1) % INPUT_BUF] != '\n')
				{
					input.e--;
					consputc(BACKSPACE, current_color_setting);
				}
				break;
			
			case C('H'): case '\x7f':  // Backspace
				if(input.e != input.w)
				{
					input.e--;
					consputc(BACKSPACE, current_color_setting);
				}
				break;

			default:
				if(c != 0 && input.e-input.r < INPUT_BUF)
				{
					c = (c == '\r') ? '\n' : c;
					input.buf[input.e++ % INPUT_BUF] = c;
					consputc(c, current_color_setting);
					if(c == '\n' || c == C('D') || input.e == input.r+INPUT_BUF)
					{
						input.w = input.e;
						wakeup(&input.r);
					}
				}
				break;
		}
	}

	release(&cons.lock);
	if(doprocdump) 
	{
		procdump();  // now call procdump() wo. cons.lock held
	}
}

int consoleread(struct inode *ip, char *dst, int n)
{
	uint target;
	int c;

	iunlock(ip);
	target = n;
	acquire(&cons.lock);
	
	while(n > 0)
	{
		while(input.r == input.w)
		{
			if(myproc()->killed)
			{
				release(&cons.lock);
				ilock(ip);
				return -1;
			}
			
			sleep(&input.r, &cons.lock);
		}

		c = input.buf[input.r++ % INPUT_BUF];

		if(c == C('D')) // EOF
		{
			if(n < target)
			{
				// Save ^D for next time, to make sure
				// caller gets a 0-byte result.
				input.r--;
			}
			break;
		}

		*dst++ = c;
		--n;

		if(c == '\n')
			break;
	}

	release(&cons.lock);
	ilock(ip);

	return target - n;
}

void set_console_color(char setting)
{
	switch(setting)
	{
		case '0':
			current_color_setting = COLOR_BLACK;
			break;
		case '1':
			current_color_setting = COLOR_BLUE;
			break;
		case '2':
			current_color_setting = COLOR_GREEN;
			break;
		case '3':
			current_color_setting = COLOR_CYAN;
			break;
		case '4':
			current_color_setting = COLOR_RED;
			break;
		case '5':
			current_color_setting = COLOR_MAGENTA;
			break;
		case '6':
			current_color_setting = COLOR_BROWN;
			break;
		case '7':
			current_color_setting = COLOR_LIGHT_GRAY;
			break;
		case '8':
			current_color_setting = COLOR_DARK_GRAY;
			break;
		case '9':
			current_color_setting = COLOR_LIGHT_BLUE;
			break;
		case 'A':
			current_color_setting = COLOR_LIGHT_GREEN;
			break;
		case 'B':
			current_color_setting = COLOR_LIGHT_CYAN;
			break;
		case 'C':
			current_color_setting = COLOR_LIGHT_RED;
			break;
		case 'D':
			current_color_setting = COLOR_LIGHT_MAGENTA;
			break;
		case 'E':
			current_color_setting = COLOR_LIGHT_BROWN;
			break;
		case 'F':
			current_color_setting = COLOR_WHITE;
			break;
		default:
			current_color_setting = COLOR_LIGHT_GRAY;
	}
}

static int percent_flag = 0;
static int color_flag = 0;

int consolewrite(struct inode *ip, char *buf, int n)
{
	int i;

	iunlock(ip);
	acquire(&cons.lock);

	for(i = 0; i < n; i++)
	{
		if(buf[i] == '%')
		{ 
			// set the flag to signify a percent symbol has been found
			percent_flag = 1;

			// print the '%' char if the next char is not 'Z' or 'C'
			if(i + 1 < n && buf[i + 1] != 'Z' && buf[i + 1] != 'C')
				consputc(buf[i] & 0xff, current_color_setting);
		}
		else
		{
			if(color_flag == 1)
			{
				set_console_color(buf[i]);
				color_flag = 0;
				percent_flag = 0;
			}
			else if(percent_flag == 1)
			{
				if(buf[i] == 'Z')
				{
					percent_flag = 0;
					clear_terminal();
				}
				else if(buf[i] == 'C')
				{
					color_flag = 1;			
				}
				else
				{
					percent_flag = 0;
					consputc(buf[i] & 0xFF, current_color_setting);
				}				
			}
			else
			{
				consputc(buf[i] & 0xff, current_color_setting);
			}
		}
	}

	release(&cons.lock);
	ilock(ip);

	return n;
}

void consoleinit(void)
{
	initlock(&cons.lock, "console");

	devsw[CONSOLE].write = consolewrite;
	devsw[CONSOLE].read = consoleread;
	cons.locking = 1;

	ioapicenable(IRQ_KBD, 0);
}

