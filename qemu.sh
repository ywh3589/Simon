#!/bin/sh
set -e

if [ ! -d ./seabios/out ]; then
	make -C ./seabios/
fi

make qemu
