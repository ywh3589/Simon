// Format of an ELF executable file

#define ELF_MAGIC 0x464C457FU  // 0x7F, 'E', 'L', 'F' in little endian

// File header
struct elfhdr {
  uint magic;  		// must equal ELF_MAGIC
  uchar elf[12];
  ushort type;
  ushort machine;
  uint version;
  uint entry;
  uint phoff;		// offset of the first program header
  uint shoff;
  uint flags;
  ushort ehsize;
  ushort phentsize;
  ushort phnum;		// number of program headers to load
  ushort shentsize;
  ushort shnum;
  ushort shstrndx;
};

// Program section header
struct proghdr {
  uint type;
  uint offset;		// location of contents relative to ELF header
  uint vaddr;		// virtual address
  uint paddr;
  uint filesz;		// number of bytes that need to be loaded from the file
  uint memsz;		// number of bytes that need to be allocated in memory
			// if memsz > filesz, the bytes not loaded from the file are to be zeroed
  uint flags;
  uint align;
};

// Values for Proghdr type
#define ELF_PROG_LOAD           1

// Flag bits for Proghdr flags
#define ELF_PROG_FLAG_EXEC      1
#define ELF_PROG_FLAG_WRITE     2
#define ELF_PROG_FLAG_READ      4
