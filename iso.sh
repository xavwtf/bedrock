#!/bin/bash

set -e
. ./build.sh

mkdir -p iso
mkdir -p iso/boot
mkdir -p iso/boot/grub

cp sysroot/boot/bedrock.bin iso/boot/bedrock.bin
cat > iso/boot/grub/grub.cfg << EOF
set timeout=0
menuentry "Bedrock" {
    multiboot /boot/bedrock.bin
}
EOF
grub-mkrescue -o bedrock.iso iso