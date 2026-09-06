#include <kernel/panic.h>
#include <stdio.h>

__attribute__((noreturn))
void kpanic(char* message) {
    printf("The kernel has encountered an unrecoverable error.\nThe system will now halt.\n");
    printf("Error message: %s\n", message);
    asm volatile ("cli; hlt;");
    for (;;);
}

__attribute__((noreturn))
void kpanic_exception(char* message, struct interrupt_frame* frame) {
    #if defined(__i386__)
    printf("The kernel has encountered an unrecoverable exception.\nThe system will now halt.\n");
    printf("Error message: %s\n", message);
    printf("Exception frame:\n");
    printf("EAX: 0x%08X\n", frame->eax);
    printf("EBX: 0x%08X\n", frame->ebx);
    printf("ECX: 0x%08X\n", frame->ecx);
    printf("EDX: 0x%08X\n", frame->edx);
    printf("ESI: 0x%08X\n", frame->esi);
    printf("EDI: 0x%08X\n", frame->edi);
    printf("EBP: 0x%08X\n", frame->ebp);
    printf("ESP: 0x%08X\n", frame->esp);
    printf("DS: 0x%08X\n", frame->ds);
    printf("ES: 0x%08X\n", frame->es);
    printf("Vector: 0x%08X\n", frame->vector);
    printf("Error code: 0x%08X\n", frame->error);
    printf("EIP: 0x%08X\n", frame->eip);
    printf("CS: 0x%08X\n", frame->cs);
    printf("EFLAGS: 0x%08X\n", frame->eflags);
    #endif

    asm volatile ("cli; hlt;");
    for (;;);
}