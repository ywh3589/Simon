// Boot loader.
//
// Part of the boot block, along with bootasm.S, which calls bootmain().
// bootasm.S has put the processor into protected 32-bit mode.
// bootmain() loads an ELF kernel image from the disk starting at
// sector 1 and then jumps to the kernel entry routine.

#include "types.h"
#include "elf.h"
#include "x86.h"
#include "memlayout.h"

#define SECTSIZE  512

void readseg(uchar*, uint, uint);

/* Execution begins here after a call to 'bootmain' in bootasm.S.
 * bootmain's sole job is to load a kernel from a disk into CPU memory.
 * It does this by loading the first 4096 bytes from an ELF format binary
 * found on the disk. It places the in-memory copy of the kernel at address
 * 0x10000. It then loads each program segment that is pointed to by the
 * ELF header.
*/
void bootmain(void)
{
	struct elfhdr *elf;
	struct proghdr *ph, *eph;
	void (*entry)(void);
	uchar* pa;

	elf = (struct elfhdr*)0x10000;  // place the elf header to begin at address 0x10000

	readseg((uchar*)elf, 4096, 0); 	// Read 4096 bytes off the disk into address 0x10000

	// Is this an ELF executable?
	if(elf->magic != ELF_MAGIC)
		return;  		// let bootasm.S handle error

	// Load each program segment (ignores ph flags).
	ph = (struct proghdr*)((uchar*)elf + elf->phoff);
	eph = ph + elf->phnum;
	
	for(; ph < eph; ph++)	// load each program segment defined in the ELF header
	{
		// get the address of the program to be loaded and load it into memory
		// read filesz number of bytes starting at offset and read them into addresses beginning at vaddr
		pa = (uchar*)ph->paddr;
		readseg(pa, ph->filesz, ph->offset);

		// if memsz > filesz, then we need to allocate more memory to this section than was in the file
		// call stosb to zero out this extra section of memory
		// stosb calls assembly instruction 'rep stosb' to repeatedly zero out every byte in this block of memory
		if(ph->memsz > ph->filesz)
			stosb(pa + ph->filesz, 0, ph->memsz - ph->filesz);
	}

	// Call the entry point from the ELF header.
	// Does not return!
	entry = (void(*)(void))(elf->entry);
	entry();
}

// simply block until disk is ready to be read from
void waitdisk(void)
{
	// Wait for disk ready.
	// The disk will set the top 2 bits of its status byte (at 0x1F7) when available - and 0xC0 = 1100 0000
	// 0x40 = 0100 0000
	// So this will read the status byte until both upper bits are set
	while((inb(0x1F7) & 0xC0) != 0x40)  
		;
}

// Read a single sector at offset into dst.
void readsect(void *dst, uint offset)
{
	// Wait until disk can be read from
	waitdisk();

	// Tell the disk how many sectors to read and from what sector
	outb(0x1F2, 1);   			// This says we will be only reading 1 sector
	outb(0x1F3, offset);			// Pass the first byte of the 32-bit offset
	outb(0x1F4, offset >> 8);		// Pass the second byte
	outb(0x1F5, offset >> 16);		// Pass the third byte
	outb(0x1F6, (offset >> 24) | 0xE0);	// Pass the fourth byte (0xE0 signifies that we are passing as sector number - not an actual addres)
	outb(0x1F7, 0x20);  			// This issues a command saying we will be reading sectors

	// Wait again until the disk can be read from
	waitdisk();

	// Read in a single sector
	// must divide by 4 because it reads in 4-byte chunks and we only want SECTSIZE bytes
	insl(0x1F0, dst, SECTSIZE/4); 
}

// Read 'count' bytes at 'offset' from kernel into physical address 'pa'.
// Might copy more than asked.
void readseg(uchar* pa, uint count, uint offset)
{
	uchar* epa;

	// compute the address to stop reading at
	epa = pa + count;

	// Round down to sector boundary.
	pa -= offset % SECTSIZE;

	// Translate from bytes to sectors; kernel starts at sector 1.
	offset = (offset / SECTSIZE) + 1;

	// If this is too slow, we could read lots of sectors at a time.
	// We'd write more to memory than asked, but it doesn't matter --
	// we load in increasing order.
	// -- Read in one sector (512 bytes) at a time and read into physical address 'pa'
	for(; pa < epa; pa += SECTSIZE, offset++)
		readsect(pa, offset);
}
