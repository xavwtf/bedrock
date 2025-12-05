# host can be specified with make HOST={whatever}, otherwise fallback to default target
DEFAULT_TARGET=$(shell ../scripts/default-target.sh)
HOST?=$(DEFAULT_TARGET)
HOSTARCH=$(shell ../scripts/parse-triplet.sh $(HOST))

BUILDDIR?=build

CFLAGS?=-O2 -g
CPPFLAGS?=
LDFLAGS?=
LIBS?=

DESTDIR?=
# temporary
PREFIX?=/usr/local
EXEC_PREFIX?=$(PREFIX)
BOOTDIR?=$(EXEC_PREFIX)/boot
INCLUDEDIR?=$(PREFIX)/include

CFLAGS:=$(CFLAGS) -ffreestanding -Wall -Wextra
CPPFLAGS:=$(CPPFLAGS) -D__is_kernel -Iinclude
LDFLAGS:=$(LDFLAGS)
LIBS:=$(LIBS) -nostdlib -lk -lgcc

ARCHDIR=arch/$(HOSTARCH)

include $(ARCHDIR)/make.config

CFLAGS:=$(CFLAGS) $(KERNEL_ARCH_CFLAGS)
CPPFLAGS:=$(CPPFLAGS) $(KERNEL_ARCH_CPPFLAGS)
LDFLAGS:=$(LDFLAGS) $(KERNEL_ARCH_LDFLAGS)
LIBS:=$(LIBS) $(KERNEL_ARCH_LIBS)

KERNEL_C_SRC:=$(shell find kernel -name "*.c")
KERNEL_ASM_SRC:=$(shell find kernel -name "*.s")

KERNEL_C_OBJS:=$(patsubst kernel/%.c,$(BUILDDIR)/kernel/%.o,$(KERNEL_C_SRC))
KERNEL_ASM_OBJS:=$(patsubst kernel/%.s,$(BUILDDIR)/kernel/%.o,$(KERNEL_ASM_SRC))

KERNEL_OBJS:=$(KERNEL_C_OBJS) $(KERNEL_ASM_OBJS) $(patsubst %.o,$(BUILDDIR)/%.o,$(KERNEL_ARCH_OBJS))

OBJS=\
	$(KERNEL_OBJS) \

LINK_LIST=\
	$(LDFLAGS) \
	$(KERNEL_OBJS) \
	$(LIBS) \

KERNEL_BIN:=$(BUILDDIR)/bedrock.bin

.PHONY: all clean install install-headers install-kernel
.SUFFIXES: .o .c .s

all: $(KERNEL_BIN)

$(KERNEL_BIN): $(OBJS) $(ARCHDIR)/linker.ld
	$(CC) -T $(ARCHDIR)/linker.ld -o $@ $(CFLAGS) $(LINK_LIST)
	grub-file --is-x86-multiboot $(KERNEL_BIN)

$(BUILDDIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) -MD -c $< -o $@ -std=gnu11 $(CFLAGS) $(CPPFLAGS)

$(BUILDDIR)/%.o: %.s
	mkdir -p $(dir $@)
	$(CC) -MD -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

clean:
	rm -rf $(BUILDDIR)

install: install-headers install-kernel

install-headers:
	mkdir -p $(DESTDIR)$(INCLUDEDIR)
	cp -R -p include/. $(DESTDIR)$(INCLUDEDIR)/.

install-kernel: $(KERNEL_BIN)
	mkdir -p $(DESTDIR)$(BOOTDIR)
	cp $(KERNEL_BIN) $(DESTDIR)$(BOOTDIR)

-include $(OBJS:.o=.d)