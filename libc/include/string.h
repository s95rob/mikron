#pragma once

#include <stddef.h>

// End of string
#define EOS ((char)'\0')

size_t strlen(const char* s);
size_t strnlen(const char* s, size_t maxlen);