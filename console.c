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

static void consputc(int);
static int panicked = 0;

static struct {
  struct spinlock lock;
  int locking;
} cons;

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
    consputc(buf[i]);
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
  memmove(crt, crt+80, sizeof(crt[0])*23*80);			// move all console output up one line
  position = 23 * 80; 						// put cursor at beginning of last line
  memset(crt+position, 0, sizeof(crt[0])*(24*80 - position)); 	// clear the last line

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
        consputc(' ');
        --position;
      }

      continue;      
    }

    if(c != '%')
    {
      consputc(c);
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
        consputc(*s);
      break;
    case '%':
      consputc('%');
      break;
    case 'Z':
      clear_terminal();
      consputc('A');
    default:
      // Print unknown % sequence to draw attention.
      consputc('%');
      consputc(c);
      consputc('B');
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


static void cgaputc(int c);

void cgaputc_n(int c, int n)
{
  while(n > 0)
  {
    cgaputc(c);
    --n;
  }
}

static void cgaputc(int c)
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

    cgaputc_n(32, spaces);   		// 32 = ASCII code for space char - ' '
  }
  else
    crt[pos++] = (c&0xff) | 0x0700;  // black on white

  if(pos < 0 || pos > 25*80)
    panic("pos under/overflow");

  if((pos/80) >= 24)
    scroll_up(pos);
  else
    set_cursor_position(pos);
}

void clear_terminal()
{
  memset(crt, 0, sizeof(crt[0])*(24*80)); 	// clear the last line

  set_cursor_position(0);
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

void consputc(int c)
{
  if(panicked){
    cli();
    for(;;)
      ;
  }

//  if(c == BACKSPACE){
//    uartputc('\b'); uartputc(' '); uartputc('\b');
//  } else
//    uartputc(c);
  cgaputc(c);
}

#define INPUT_BUF 128
struct {
  char buf[INPUT_BUF];
  uint r;  // Read index
  uint w;  // Write index
  uint e;  // Edit index
} input;

#define C(x)  ((x)-'@')  // Control-x

void consoleintr(int (*getc)(void))
{
  int c, doprocdump = 0;

  acquire(&cons.lock);
  while((c = getc()) >= 0){
    switch(c){
    case C('P'):  // Process listing.
      // procdump() locks cons.lock indirectly; invoke later
      doprocdump = 1;
      break;
    case C('U'):  // Kill line.
      while(input.e != input.w &&
            input.buf[(input.e-1) % INPUT_BUF] != '\n'){
        input.e--;
        consputc(BACKSPACE);
      }
      break;
    case C('H'): case '\x7f':  // Backspace
      if(input.e != input.w){
        input.e--;
        consputc(BACKSPACE);
      }
      break;
    default:
      if(c != 0 && input.e-input.r < INPUT_BUF){
        c = (c == '\r') ? '\n' : c;
        input.buf[input.e++ % INPUT_BUF] = c;
        consputc(c);
        if(c == '\n' || c == C('D') || input.e == input.r+INPUT_BUF){
          input.w = input.e;
          wakeup(&input.r);
        }
      }
      break;
    }
  }
  release(&cons.lock);
  if(doprocdump) {
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
  while(n > 0){
    while(input.r == input.w){
      if(myproc()->killed){
        release(&cons.lock);
        ilock(ip);
        return -1;
      }
      sleep(&input.r, &cons.lock);
    }
    c = input.buf[input.r++ % INPUT_BUF];
    if(c == C('D')){  // EOF
      if(n < target){
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

static int clear_flag = 0;

int consolewrite(struct inode *ip, char *buf, int n)
{
  int i;

  iunlock(ip);
  acquire(&cons.lock);

  for(i = 0; i < n; i++)
  {
    if(buf[i] == '%')
    { 
      clear_flag = 1;
      consputc(buf[i] & 0xff);
    }
    else
    {
      if(clear_flag == 1 && buf[i] == 'Z')
        clear_terminal();
      else
      {
        consputc(buf[i] & 0xff);
      }

      clear_flag = 0;
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

