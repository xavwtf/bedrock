#include <string.h>

void* memcpy(void* restrict dst_ptr, const void* restrict src_ptr, size_t size) {
    unsigned char* dst = (unsigned char*)dst_ptr;
    const unsigned char* src = (const unsigned char*)src_ptr;

    for (size_t i = 0; i < size; i++) {
        dst[i] = src[i];
    }

    return dst_ptr;
}