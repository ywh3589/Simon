DEFAULT_HOST!=../default-host.sh			# "i686-elf"
HOST?=$(DEFAULT_HOST)					# "i686-elf"
HOSTARCH!=../target-triplet-to-arch.sh $(HOST)		# search the host name for "i[digit]86" - if found, return "i386"

CFLAGS?=-O2 -g						# set compiler flags
CPPFLAGS?=
LDFLAGS?=
LIBS?=

DESTDIR?=						# this should have been set to SYSROOT before calling make
PREFIX?=/usr/local					# should be set to /usr in config.sh
EXEC_PREFIX?=$(PREFIX)					# /usr
INCLUDEDIR?=$(PREFIX)/include				# /usr/boot
LIBDIR?=$(EXEC_PREFIX)/lib				# /usr/include

CFLAGS:=$(CFLAGS) -ffreestanding -Wall -Wextra
CPPFLAGS:=$(CPPFLAGS) -D__is_libc -Iinclude
LIBK_CFLAGS:=$(CFLAGS)
LIBK_CPPFLAGS:=$(CPPFLAGS) -D__is_libk

#       arch/i386
ARCHDIR=arch/$(HOSTARCH)

include $(ARCHDIR)/make.config
	# sets the following:
	#	ARCH_CFLAGS=
	#	ARCH_CPPFLAGS=
	#	KERNEL_ARCH_CFLAGS=
	#	KERNEL_ARCH_CPPFLAGS=
	#	
	#	ARCH_FREEOBJS=\
	#
	#	ARCH_HOSTEDOBJS=\

CFLAGS:=$(CFLAGS) $(ARCH_CFLAGS)			# append kernel flags
CPPFLAGS:=$(CPPFLAGS) $(ARCH_CPPFLAGS)
LIBK_CFLAGS:=$(LIBK_CFLAGS) $(KERNEL_ARCH_CFLAGS)
LIBK_CPPFLAGS:=$(LIBK_CPPFLAGS) $(KERNEL_ARCH_CPPFLAGS)

# combine all free library object files
FREEOBJS= \
$(ARCH_FREEOBJS) \
stdio/printf.o \
stdio/putchar.o \
stdio/puts.o \
stdlib/abort.o \
string/memcmp.o \
string/memcpy.o \
string/memmove.o \
string/memset.o \
string/strlen.o \

# combine all hosted library object files
HOSTEDOBJS=\
$(ARCH_HOSTEDOBJS) \

# create set of all object files
OBJS=\
$(FREEOBJS) \
$(HOSTEDOBJS) \

LIBK_OBJS=$(FREEOBJS:.o=.libk.o)

#BINARIES=libc.a libk.a # Not ready for libc yet.
BINARIES=libk.a

.PHONY: all clean install install-headers install-libs
.SUFFIXES: .o .libk.o .c .S

all: $(BINARIES)

libc.a: $(OBJS)
	$(AR) rcs $@ $(OBJS)

libk.a: $(LIBK_OBJS)
	$(AR) rcs $@ $(LIBK_OBJS)

.c.o:
	$(CC) -MD -c $< -o $@ -std=gnu11 $(CFLAGS) $(CPPFLAGS)

.c.S:
	$(CC) -MD -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

.c.libk.o:
	$(CC) -MD -c $< -o $@ -std=gnu11 $(LIBK_CFLAGS) $(LIBK_CPPFLAGS)

.S.libk.o:
	$(CC) -MD -c $< -o $@ $(LIBK_CFLAGS) $(LIBK_CPPFLAGS)

clean:
	rm -f $(BINARIES) *.a
	rm -f $(OBJS) $(LIBK_OBJS) *.o */*.o */*/*.o
	rm -f $(OBJS:.o=.d) $(LIBK_OBJS:.o=.d) *.d */*.d */*/*.d

install: install-headers install-libs

install-headers:
	mkdir -p $(DESTDIR)$(INCLUDEDIR)
	cp -R --preserve=timestamps include/. $(DESTDIR)$(INCLUDEDIR)/.

install-libs: $(BINARIES)
	mkdir -p $(DESTDIR)$(LIBDIR)
	cp $(BINARIES) $(DESTDIR)$(LIBDIR)

-include $(OBJS:.o=.d)
-include $(LIBK_OBJS:.o=.d)
