    #include "gdt.h"

    #include <stdint.h>

    // most of this is overkill considering we want a flat memory model, good to have just in case tho
    #define MAKE_GDT_ENTRY(base, limit, access, flags) /* flags are shifted to upper nibble, you should pass flags in the lower nibble */ \
    (struct gdt_entry) \
    { \
        (uint16_t)(limit & 0xFFFF), /* limit_low */ \
        (uint16_t)(base & 0xFFFF), /* base_low */ \
        (uint8_t)((base >> 16) & 0xFF), /* base_middle */ \
        (uint8_t)(access & 0xFF), /* access */ \
        (uint8_t)(((limit >> 16) & 0x0F) | ((flags << 4) & 0xF0)), /* granularity, bits 0-3 are limit_high, 4-7 are flags */ \
        (uint8_t)((base >> 24) & 0xFF), /* base_high */ \
    }

    struct gdt_entry {
        uint16_t limit_low;
        uint16_t base_low;
        uint8_t base_middle;
        uint8_t access;
        uint8_t flags_limit;
        uint8_t base_high;
    } __attribute__((packed));

    struct {
        uint16_t limit;
        struct gdt_entry* base;
    } __attribute__((packed)) gdtr;

    struct gdt_entry gdt[5] = {
        MAKE_GDT_ENTRY(0, 0, 0, 0), // GDT requires a null descriptor at index 0, some emulators (bochs!!) cry if it's not nulled out, don't think it matters on hardware tho

        MAKE_GDT_ENTRY(0, 0xFFFFF, 0b10011011, 0b1100), // kernel code, dpl=0, base=0, limit=4gb, 32-bit non-conforming (!)
        MAKE_GDT_ENTRY(0, 0xFFFFF, 0b10010011, 0b1100), // kernel data, dpl=0, base=0, limit=4gb, 32-bit
        MAKE_GDT_ENTRY(0, 0xFFFFF, 0b11111011, 0b1100), //   user code, dpl=3, base=0, limit=4gb, 32-bit non-conforming (!)
        MAKE_GDT_ENTRY(0, 0xFFFFF, 0b11110011, 0b1100)  //   user data, dpl=3, base=0, limit=4gb, 32-bit
    };

    void gdt_init(void) {
        // disable interrupts
        asm volatile ("cli");

        // write to our gdtr
        gdtr.limit = sizeof(struct gdt_entry) * 5 - 1;
        gdtr.base = (struct gdt_entry*)&gdt;

        // load gdtr into the gdtr register
        asm volatile (
            "lgdt (%0)"
            : : "r"(&gdtr)
        );

        // from here, the gdt is loaded, but segment selectors aren't loaded.
        // to reload data segment registers, we can simply perform a mov instruction
        // however, cs requires a far jump or call.
        
        asm volatile (
            "ljmp $0x08, $reload_cs;" // perform the far jump - 0x08 corresponds to the first index in the gdt at rpl=0 (kernel code segment) 
            "reload_cs:"
        );

        // cs is reloaded now, but the data segment registers have yet to be reloaded
        // let's do that now

        asm volatile (
            "movw $0x10, %%ax;" // 0x10 corresponds to the second index in the gdt at rpl=0, this is our kernel data segment
            "movw %%ax, %%ds;"
            "movw %%ax, %%es;"
            "movw %%ax, %%fs;"
            "movw %%ax, %%gs;"
            "movw %%ax, %%ss;"
            : : : "ax", "memory"
        );

        // the gdt is now fully loaded, segment registers are synced, and we can celebrate. yay!
        
        // we can now re-enable interrupts
        asm volatile ("sti");

        return;
    }