#!/bin/bash

set -e
. ./configure.sh

mkdir -p "$SYSROOT"

for PROJECT in $SYS_HEADER_PROJECTS; do
    (cd $PROJECT && DESTDIR="$SYSROOT" $MAKE install-headers)
done