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

/*initializes memory management by allocating a block from the memory pool,
if the requested size exceeds the size of the pool, an error message is printed and the function exits.*/
void mem_init(size_t size) {               
    if (size > POOL_SIZE) {
        fprintf(stderr, "Error: Requested size bigger than memory pool size.\n");
        return;
    }
    free_list = (Block*)memory_pool;     //the pointer to the free list is initialized and points to the beginning of the memory pool
    free_list->size = size - sizeof(Block);  //the size of the first block is set to the requested size minus the size of the Block structure
    free_list->free = 1;     //the block is marked as free (free = 1) and ready for future allocations
    free_list->next = NULL;
}


void* mem_alloc(size_t size) {
    if (size == 0 || size + sizeof(Block) > POOL_SIZE - total_allocated) {
        return NULL;
    }

    Block* current = free_list;

    while (current) {
        if (current->free && current->size >= size) {
            if (current->size >= size + sizeof(Block) + 1) {
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

            total_allocated += size + sizeof(Block); 
            return (char*)current + sizeof(Block);
        }
        current = current->next;
    }
    return NULL;
}

void mem_free(void* block) {
    if (block == NULL) return;

    Block* current = (Block*)((char*)block - sizeof(Block));

    if (current->free) {
        fprintf(stderr, "Error: This block is already free\n");
        return;
    }

    current->free = 1;

    total_allocated -= current->size + sizeof(Block); 

    Block* next = current->next;
    if (next && next->free) {
        current->size += sizeof(Block) + next->size;
        current->next = next->next;
    }
}

/*resizes an allocated block of memory.*/
void* mem_resize(void* block, size_t new_size) {
    
    //if the block is NULL, a new block with the requested size is allocated
    if (block == NULL) {
        return mem_alloc(new_size); 
    }
    //compute the pointer to the Block structure associated with the beginning of the specified memory block
    Block* current = (Block*)((char*)block - sizeof(Block));
    if (current->free) {  //Check if the block is free; if so, print an error message
        fprintf(stderr, "Error: Can't resize a free block!\n");   
        return NULL;
    }
    //if the new size is less than or equal to the current size, return the original block
    if (new_size <= current->size) {
        return block;
    }
    //allocate a new block with the new size
    void* new_block = mem_alloc(new_size);
    if (new_block == NULL) {
        return NULL; 
    }
    //copy the contents from the old block to the new one and free the old block
    memcpy(new_block, block, current->size);
    mem_free(block); 
    return new_block; //return the pointer to the new block
}

//Sets the free list to NULL to clear the state
void mem_deinit(void) {
    free_list = NULL;    
}
