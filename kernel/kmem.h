// Early-stage kernel memory

#include <stddef.h>

#define KMEM_ALIGN 4
#define KMEM_PAGE_SIZE 0x1000

// Memory block descriptor
typedef struct memblock {
    size_t addr;
    size_t num_pages;
    size_t alloc_offset;
} memblock;

// Initialize early-stage kernel memory
void kmem_init(size_t ram_base);

// Allocate a block of memory with `n` amount of pages
memblock kmem_block(size_t n);

// Allocate memory from a block of memory
void* kmem_alloc(memblock* block, size_t size);