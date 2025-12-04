#!/bin/bash -e
. ./configure.sh

for PROJECT in $PROJECTS; do
    (cd $PROJECT && $MAKE clean)
done

rm -rf $SYSROOT
rm -rf iso
rm -rf bedrock.iso