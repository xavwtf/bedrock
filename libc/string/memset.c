#include <string.h>

void* memset(void* buf_ptr, int value, size_t size) {
    unsigned char* buffer = (unsigned char*)buf_ptr;

    for (size_t i = 0; i < size; i++) {
        buffer[i] = (unsigned char)value;
    }

    return buf_ptr;
}