#!/bin/bash -e
. ./iso.sh

qemu-system-i386 -cdrom bedrock.iso $@