#include "fdt.h"

#define FDT_BASE ((size_t)s_fdt)

static const fdt_header* s_fdt = NULL;

b8 fdt_init(const fdt_header* fdt) {
    if (bswap32(fdt->magic) == FDT_MAGIC) {
        if (bswap32(fdt->version) >= FDT_VERSION) {
            s_fdt = fdt;
            return TRUE;
        }
    }

    return FALSE;
}