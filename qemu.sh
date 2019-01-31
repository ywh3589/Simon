#!/bin/sh
set -e		# exit immediately if iso.sh returns non-zero status
. ./iso.sh	# period -> runs iso.sh within this shell script

# qemu-system-i386  
qemu-system-$(./target-triplet-to-arch.sh $HOST) -cdrom simon.iso -display curses
