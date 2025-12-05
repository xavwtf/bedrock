SYS_HEADER_PROJECTS:=libc kernel
PROJECTS:=libc kernel

MAKE:=make
HOST:=$(shell scripts/default-target.sh)

AR:=$(HOST)-ar
AS:=$(HOST)-as
CC:=$(HOST)-gcc

ARGS?=

GRUB_MKRESCUE:=$(shell command -v grub-mkrescue || command -v grub2-mkrescue)

ifeq (GRUB_MKRESCUE,)
$(error grub-mkrescue not found: install grub)
endif

PREFIX:=/usr
BOOTDIR:=/boot
LIBDIR:=$(PREFIX)/lib
INCLUDEDIR:=$(PREFIX)/include

CFLAGS:=-O2 -g
CPPFLAGS:=

SYSROOT:=$(CURDIR)/sysroot
CC+=--sysroot=$(SYSROOT)

TARGET_IS_ELF:=$(if $(shell echo $(HOST) | grep -E "-elf($$|-)"),yes,no)

ifeq ($(TARGET_IS_ELF),yes)
CC+=-isystem=$(INCLUDEDIR)
endif

MAKEFLAGS:=--no-print-directory

export HOST AR AS CC PREFIX BOOTDIR LIBDIR INCLUDEDIR CFLAGS CPPFLAGS

.PHONY: all build install-headers clean iso run-i386

all: iso

install-headers:
	@$(foreach proj,$(PROJECTS),$(MAKE) -C $(proj) DESTDIR=$(SYSROOT) install-headers $(MAKEFLAGS);)

build: install-headers
	@$(foreach proj,$(PROJECTS),$(MAKE) -C $(proj) DESTDIR=$(SYSROOT) install $(MAKEFLAGS);)

clean:
	@$(foreach proj,$(PROJECTS),$(MAKE) -C $(proj) clean $(MAKEFLAGS);)
	rm -rf sysroot
	rm -rf iso
	rm -f bedrock.iso

iso: build
	mkdir -p iso/boot/grub
	cp sysroot/boot/bedrock.bin iso/boot/bedrock.bin
	cp misc/grub.cfg iso/boot/grub/grub.cfg

	$(GRUB_MKRESCUE) -o bedrock.iso iso

run-i386: iso
	qemu-system-i386 -cdrom bedrock.iso $(ARGS)