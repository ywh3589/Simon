#!/bin/sh
set -e			# exit if headers.sh fails
. ./headers.sh		# run headers.sh

# change director to project directory and then call make install
for PROJECT in $PROJECTS; do
  (cd $PROJECT && DESTDIR="$SYSROOT" $MAKE install)
done
