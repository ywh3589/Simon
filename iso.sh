#!/bin/sh
set -e				# exit if build.sh fails
. ./build.sh			# run build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/simon.kernel isodir/boot/simon.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "simon" {
	multiboot /boot/simon.kernel
}
EOF
grub-mkrescue -o simon.iso isodir
