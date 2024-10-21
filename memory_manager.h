#ifndef MEMORY_MANAGER_H  
#define MEMORY_MANAGER_H  

#include <stdio.h>  // Includes standard input and output functions
#include <string.h>  // Includes string handling functions
#include <stdint.h>  // Includes standardized integer types
#include <stddef.h>  // Includes standard definitions, including the size type size_t
#include <stdbool.h>  // Includes boolean type and true/false constants
#include <stdlib.h>  // Includes functions for memory management and conversion


// Defines the size of the memory pool (80 MB)
#define POOL_SIZE 81920000 
// Defines the maximum number of blocks that can be created
#define MAX_BLOCKS 100000      

// Structure representing a block of memory
typedef struct Block {
    void* address;  // Pointer to the block's starting address
    size_t size;   // Size of the block in bytes
    bool is_free;  // Flag indicating whether the block is free or busy
    struct Block* next; // Pointer to the next block in the linked list
} Block;


void* memory_pool; // Pointer to the entire memory pool
Block* head_pool;  // Pointer to the first block in the linked list of blocks

void mem_init(size_t size);
void* mem_alloc(size_t size);
void mem_free(void* block);
void* mem_resize(void* block, size_t size);
void mem_deinit(void);

#endif 


