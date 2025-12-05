# multiboot stuff
.set ALIGN,    1 << 0 # page boundary
.set MEMINFO,  1 << 1 # memory map
.set FLAGS,    ALIGN | MEMINFO # multiboot flags
.set MAGIC,    0x1BADB002 # magic number for multiboot so it knows it found the header
.set CHECKSUM, -(MAGIC + FLAGS)

# define our multiboot header
.section .multiboot
.align 4 # bytes
.long MAGIC
.long FLAGS
.long CHECKSUM

# WE must define a stack pointer.
# sys-v requires us to align our stack to 16 bytes
.section .bss
.align 16
stack_bottom:
.skip 16384 # size of the stack
stack_top:

# entrypoint
.section .text
.global _start
.type _start, @function
_start:
        # we are now in 32-bit protected mode.
        # at this point we are GOD

        mov $stack_top, %esp

        call gdt_init
        # TODO: paging, c++ compat

        call kernel_main

        cli
1:      hlt
        jmp 1b
