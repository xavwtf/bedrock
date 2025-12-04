#!/bin/bash -e

. ./build.sh

GRUB_MKRESCUE=$(command -v grub-mkrescue || command -v grub2-mkrescue)

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
$GRUB_MKRESCUE -o bedrock.iso iso