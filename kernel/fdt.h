// Flattened Devicetree support
// See: https://www.devicetree.org/

#pragma once

#include "kutil.h"

#define FDT_MAGIC   ((u32)0xd00dfeed)
#define FDT_VERSION 17

typedef struct fdt_header {
    u32 magic;
    u32 totalsize;
    u32 off_dt_struct;
    u32 off_dt_strings;
    u32 off_mem_rsvmap;
    u32 version;
    u32 last_comp_version;
    u32 boot_cpuid_phys;
    u32 size_dt_strings;
    u32 size_dt_struct;
} fdt_header;

typedef struct fdt_reserve_entry {
    u64 address;
    u64 size;
} fdt_reserve_entry;

typedef enum fdt_token {
    FDT_BEGIN_NODE  = 0x01,
    FDT_END_NODE    = 0x02,
    FDT_PROP        = 0x03,
    FDT_NOP         = 0x04,
    FDT_END         = 0x05
} fdt_token;

typedef struct fdt_prop {
    u32 len;
    u32 nameoff;
} fdt_prop;


// Initialize FDT reader state with FDT header
b8 fdt_init(const fdt_header* fdt);