//
// assembler macros to create x86 segments
//

#define GDT_NULL_SEGMENT                                        \
        .word 0, 0;                                             \
        .byte 0, 0, 0, 0

// The 0xC0 means the limit is in 4096-byte units
// and (for executable segments) 32-bit mode.
#define GDT_SEGMENT(type,base,lim)                              \
        .word (((lim) >> 12) & 0xffff), ((base) & 0xffff);      \
        .byte (((base) >> 16) & 0xff), (0x90 | (type)),         \
                (0xC0 | (((lim) >> 28) & 0xf)), (((base) >> 24) & 0xff)

#define GDT_ADDRESS_MIN	  0x0	    	// Minimum address is 0
#define GDT_ADDRESS_MAX	  0xffffffff	// Maximum address is 4GB

#define GDT_SEGMENT_X     0x8       // Executable segment
#define GDT_SEGMENT_W     0x2       // Writeable (non-executable segments)
#define GDT_SEGMENT_R     0x2       // Readable (executable segments)
