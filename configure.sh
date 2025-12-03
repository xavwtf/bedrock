#!/bin/bash

SYS_HEADER_PROJECTS="libc kernel"
PROJECTS="libc kernel"

export MAKE=${MAKE:-make}
export HOST=${HOST:-$(scripts/default-target.sh)}

export AR=${HOST}-ar
export AS=${HOST}-as
export CC=${HOST}-gcc

export PREFIX=/usr # temporary
export BOOTDIR=/boot
export LIBDIR=$PREFIX/lib
export INCLUDEDIR=$PREFIX/include

export CFLAGS="-O2 -g"
export CPPFLAGS=""

export SYSROOT="$(pwd)/sysroot"
export CC="$CC --sysroot=$SYSROOT"

if echo "$HOST" | grep -Eq -- "-elf($|-)"; then
    export CC="$CC -isystem=$INCLUDEDIR"
fi