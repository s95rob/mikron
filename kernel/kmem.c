#include "kmem.h"


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
    // Force size alignment
    size = (size + KMEM_ALIGN - 1) & ~(KMEM_ALIGN - 1);

    // Wrap around the block if we've exceeded block size
    if (block->alloc_offset + size >= block->num_pages * KMEM_PAGE_SIZE)
        block->alloc_offset = 0;

    void* alloc = (void*)(block->addr + block->alloc_offset);
    block->alloc_offset += size;

    return alloc;
}