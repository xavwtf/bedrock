.section .text
.globl isr_stub_table

.extern kpanic

# define to make this a lot easier
.macro isr_stub num
isr\num:
    call kpanic
    iret
.endm

.macro isr_stub_err num
isr\num:
    call kpanic
    iret
.endm

isr_stub     0
isr_stub     1
isr_stub     2
isr_stub     3
isr_stub     4
isr_stub     5
isr_stub     6
isr_stub     7
isr_stub_err 8
isr_stub     9
isr_stub_err 10
isr_stub_err 11
isr_stub_err 12
isr_stub_err 13
isr_stub_err 14
isr_stub     15
isr_stub     16
isr_stub_err 17
isr_stub     18
isr_stub     19
isr_stub     20
isr_stub_err 21

# beyond here, all vectors are unused and reserved.

isr_stub     22
isr_stub     23
isr_stub     24
isr_stub     25
isr_stub     26
isr_stub     27
isr_stub     28
isr_stub     29
isr_stub     30
isr_stub     31

.macro isr_st_entry num
.long isr\num
.endm

# ISR stubs are populated from here
# okay, this pains me but GAS .rept doesn't have the capability to use values like this, so prepare for a manual expansion... using macros
isr_stub_table:
    isr_st_entry 1
    isr_st_entry 2
    isr_st_entry 3
    isr_st_entry 4
    isr_st_entry 5
    isr_st_entry 6
    isr_st_entry 7
    isr_st_entry 8
    isr_st_entry 9
    isr_st_entry 10
    isr_st_entry 11
    isr_st_entry 12
    isr_st_entry 13
    isr_st_entry 14
    isr_st_entry 15
    isr_st_entry 16
    isr_st_entry 17
    isr_st_entry 18
    isr_st_entry 19
    isr_st_entry 20
    isr_st_entry 21
    isr_st_entry 22
    isr_st_entry 23
    isr_st_entry 24
    isr_st_entry 25
    isr_st_entry 26
    isr_st_entry 27
    isr_st_entry 28
    isr_st_entry 29
    isr_st_entry 30
    isr_st_entry 31