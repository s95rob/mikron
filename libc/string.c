#include "string.h"

size_t strlen(const char* s) {
    size_t i = 0;
    while (s[i++] != EOS);

    return i;
}

size_t strnlen(const char* s, size_t maxlen) {
    size_t i = 0;
    while (s[i++] != EOS || i < maxlen);

    return i;
}