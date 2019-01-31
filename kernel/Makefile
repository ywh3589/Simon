DEFAULT_HOST!=../default-host.sh		# this script returns "i686-elf"
HOST?=$(DEFAULT_HOST)				# sets the host variable if not already set
HOSTARCH!=../target-triplet-to-arch.sh $(HOST)	# search the host name for "i[digit]86" - if found, return "i386"

CFLAGS?=-O2 -g					# set compile and linker flags
CPPFLAGS?=
LDFLAGS?=
LIBS?=

DESTDIR?=					# this should have been set to SYSROOT before calling make
PREFIX?=/usr/local				# should be set to /usr in config.sh
EXEC_PREFIX?=$(PREFIX)				# /usr
BOOTDIR?=$(EXEC_PREFIX)/boot			# /usr/boot
INCLUDEDIR?=$(PREFIX)/include			# /usr/include

CFLAGS:=$(CFLAGS) -ffreestanding -Wall -Wextra
CPPFLAGS:=$(CPPFLAGS) -D__is_kernel -Iinclude
LDFLAGS:=$(LDFLAGS)
LIBS:=$(LIBS) -nostdlib -lk -lgcc

# 	arch/i386
ARCHDIR=arch/$(HOSTARCH)

include $(ARCHDIR)/make.config
	# sets the following:
	# 	KERNEL_ARCH_CFLAGS=
	# 	KERNEL_ARCH_CPPFLAGS=
	# 	KERNEL_ARCH_LDFLAGS=
	# 	KERNEL_ARCH_LIBS=
	#
	# 	KERNEL_ARCH_OBJS=$(ARCHDIR)/boot.o $(ARCHDIR)/tty.o

CFLAGS:=$(CFLAGS) $(KERNEL_ARCH_CFLAGS)		# append kernel flags
CPPFLAGS:=$(CPPFLAGS) $(KERNEL_ARCH_CPPFLAGS)
LDFLAGS:=$(LDFLAGS) $(KERNEL_ARCH_LDFLAGS)
LIBS:=$(LIBS) $(KERNEL_ARCH_LIBS)

KERNEL_OBJS=$(KERNEL_ARCH_OBJS) kernel/kernel.o	# all kernel object files

# combine all object files in correct order
OBJS=\
     $(ARCHDIR)/crti.o \
     $(ARCHDIR)/crtbegin.o \
     $(KERNEL_OBJS) \
     $(ARCHDIR)/crtend.o \
     $(ARCHDIR)/crtn.o \

# combine all object files plus linker object files
LINK_LIST=\
	  $(LDFLAGS) \
	  $(ARCHDIR)/crti.o \
	  $(ARCHDIR)/crtbegin.o \
	  $(KERNEL_OBJS) \
	  $(LIBS) \
	  $(ARCHDIR)/crtend.o \
	  $(ARCHDIR)/crtn.o \

.PHONY: all clean install install-headers install-kernel
.SUFFIXES: .o .c .S

all: simon.kernel

# create kernel by linking all object files
simon.kernel: $(OBJS) $(ARCHDIR)/linker.ld
	$(CC) -T $(ARCHDIR)/linker.ld -o $@ $(CFLAGS) $(LINK_LIST)
	grub-file --is-x86-multiboot simon.kernel


$(ARCHDIR)/crtbegin.o $(ARCHDIR)/crtend.o:
	OBJ=`$(CC) $(CFLAGS) $(LDFLAGS) -print-file-name=$(@F)` && cp "$$OBJ" $@

# compile all c files
.c.o:
	$(CC) -MD -c $< -o $@ -std=gnu11 $(CFLAGS) $(CPPFLAGS)

# compile all assembly files
.S.o:
	$(CC) -MD -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

clean:
	rm -f simon.kernel
	rm -f $(OBJS) *.o */*.o */*/*.o
	rm -f $(OBJS:.o=.d) *.d */*.d */*/*.d

install: install-headers install-kernel

install-headers:
	mkdir -p $(DESTDIR)$(INCLUDEDIR)
	cp -R --preserve=timestamps include/. $(DESTDIR)$(INCLUDEDIR)/.

install-kernel: simon.kernel
	mkdir -p $(DESTDIR)$(BOOTDIR)
	cp simon.kernel $(DESTDIR)$(BOOTDIR)

-include $(OBJS:.o=.d)
