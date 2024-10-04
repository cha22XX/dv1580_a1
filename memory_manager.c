#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define POOL_SIZE 1024  //Define a constant that specifies the size of the memory pool,in this case (1024 bytes)

//a block of memory with size, status (free), and pointer to the next block in the memory pool
typedef struct Block {
    size_t size;        
    int free;          
    struct Block* next; 
} Block;

static char memory_pool[POOL_SIZE];   //a static array of 2048 bytes
static Block* free_list = NULL;      //a pointer to the first free block in the linked list of memory blocks
static size_t total_allocated = 0;

void mem_init(size_t size) {
    if (size > POOL_SIZE) {
        fprintf(stderr, "Error: Requested size bigger than memory pool size.\n");
        return;
    }

    free_list = (Block*)memory_pool; 
    free_list->size = size - sizeof(Block); // Subtract size of Block metadata
    free_list->free = 1; 
    free_list->next = NULL;
}

void* mem_alloc(size_t size) {
    if (size == 0) return NULL;

    // Kontrollera om den totala allokeringen skulle överskrida POOL_SIZE
    if (total_allocated + size + sizeof(Block) > POOL_SIZE) {
        fprintf(stderr, "Error: Not enough memory available in pool.\n");
        return NULL;
    }

    Block* current = free_list;

    while (current) {
        if (current->free && current->size >= size) {
            if (current->size >= size + sizeof(Block)) { 
                Block* new_block = (Block*)((char*)current + sizeof(Block) + size);
                new_block->size = current->size - size - sizeof(Block);
                new_block->free = 1;
                new_block->next = current->next;

                current->size = size; 
                current->free = 0; 
                current->next = new_block;
            } else {
                current->free = 0; 
            }

            total_allocated += size + sizeof(Block);  // Uppdatera total allokering
            return (char*)current + sizeof(Block); // Returnera pekaren efter Block metadata
        }
        current = current->next;
    }
    return NULL; 
}
void mem_free(void* block) {
    if (block == NULL) return;

    Block* current = (Block*)((char*)block - sizeof(Block));  // Justera pekaren för att komma åt Block-metadata

    if (current->free) {
        fprintf(stderr, "Error: This block is already free.\n");
        return;
    }

    current->free = 1;  
    total_allocated -= current->size + sizeof(Block);  

    // Sammanslå med nästa block om det är ledigt
    Block* next = current->next;
    if (next && next->free) {
        current->size += next->size + sizeof(Block);  // Sammanslå storleken på blocken
        current->next = next->next;  // Hoppa över nästa block
    }
}

void* mem_resize(void* block, size_t size) {
    if (block == NULL) {
        return mem_alloc(size); 
    }
    
    Block* current = (Block*)((char*)block - sizeof(Block));
    if (current->free) {
        fprintf(stderr, "Error: Can't resize a free block!\n");
        return NULL;
    }

    if (size <= current->size) {
        return block;
    }

    void* new_block = mem_alloc(size);
    if (new_block == NULL) {
        return NULL; 
    }

    memcpy(new_block, block, current->size);
    mem_free(block); 
    return new_block;
}

void mem_deinit(void) {
    free_list = NULL; 
    total_allocated = 0;
}
