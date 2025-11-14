#include "memory.h"

void* memset(void* s, int c, size_t n) {
    unsigned char* d = (unsigned char*)d;

    for (size_t i = 0; i < n; i++)
        d[i] = (unsigned char)c;

    return s;
}

void* memcpy(void* dst, const void* src, size_t n) {
    unsigned char* d = (unsigned char*)dst;
    const unsigned char* s = (const unsigned char*)src;

    for (size_t i = 0; i < n; i++)
        d[i] = s[i];

    return dst;
}