SYSTEM_HEADER_PROJECTS="libc kernel"		# keep list of directories
PROJECTS="libc kernel"				# keep list of directories

export MAKE=${MAKE:-make}			# export the "make" command
export HOST=${HOST:-$(./default-host.sh)}	# HOST = i686-elf

export AR=${HOST}-ar				# AR = i686-elf-ar
export AS=${HOST}-as				# AS = i686-elf-as
export CC=${HOST}-gcc				# CC = i686-elf-gcc

export PREFIX=/usr				# PREFIX = /usr
export EXEC_PREFIX=$PREFIX			# EXEC_PREFIX = /usr
export BOOTDIR=/boot				# BOOTDIR = /boot
export LIBDIR=$EXEC_PREFIX/lib			# LIBDIR = /usr/lib
export INCLUDEDIR=$PREFIX/include		# INCLUDEDIR = /usr/include

export CFLAGS='-O2 -g -fstack-protector --param ssp-buffer-size=4 -Wstack-protector'
export CPPFLAGS=''

export SYSROOT="$(pwd)/sysroot"			# create a pseudo system root
export CC="$CC --sysroot=$SYSROOT"		# add system root to compiler flags

# Work around that the -elf gcc targets doesn't have a system include directory
# because it was configured with --without-headers rather than --with-sysroot.

# -isystem will make the compiler look in the specified directory first before searching elsewhere
if echo "$HOST" | grep -Eq -- '-elf($|-)'; then
  export CC="$CC -isystem=$INCLUDEDIR"		# add -isystem to compiler flags
fi
