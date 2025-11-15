// Kernel utilities

#pragma once

#include "kdef.h"

// Aligns `x` to `n` bytes
#define ALIGN(n, x) (((x) + (n - 1)) & ~(n - 1)) 

// Aligns `x` to 4 bytes
#define ALIGN4(x) ALIGN(4, x)

static inline u16 bswap16(u16 val) {
    return __builtin_bswap16(val);
}

static inline u32 bswap32(u32 val) {
    return __builtin_bswap32(val);
}

static inline u64 bswap64(u64 val) {
    return __builtin_bswap64(val);
}