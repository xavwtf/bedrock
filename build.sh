#!/bin/bash -e
. scripts/install-headers.sh

for PROJECT in $PROJECTS; do
    (cd $PROJECT && DESTDIR="$SYSROOT" $MAKE install)
done