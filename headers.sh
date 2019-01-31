#!/bin/sh
set -e			# exit if config.sh fails
. ./config.sh		# run config.sh

mkdir -p "$SYSROOT"	# create the sysroot directory 

# navigate to project directories and call "make install-headers"
for PROJECT in $SYSTEM_HEADER_PROJECTS; do
  (cd $PROJECT && DESTDIR="$SYSROOT" $MAKE install-headers)
done
