#include "kmem.h"
#include "kutil.h"

static size_t s_block_base = 0;
static size_t s_block_offset = 0;

void kmem_init(size_t ram_base) {
    s_block_base = ram_base;
    s_block_offset = 0;
}

memblock kmem_block(size_t n) {
    memblock block = {
        .addr = s_block_base + s_block_offset,
        .num_pages = n,
        .alloc_offset = 0
    };
    
    s_block_offset += n * KMEM_PAGE_SIZE;

    return block;
}

void* kmem_alloc(memblock* block, size_t size) {
    // Force allocation size alignment
    size = ALIGN(KMEM_ALIGN, size);

    // Allocation will exceed block size, return nothing
    if (block->alloc_offset + size >= block->num_pages * KMEM_PAGE_SIZE)
        return NULL;

    void* alloc = (void*)(block->addr + block->alloc_offset);
    block->alloc_offset += size;

    return alloc;
}