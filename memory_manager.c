#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "memory_manager.h"


void mem_init(size_t size) {
    if (size > POOL_SIZE) {
        fprintf(stderr, "Error: Requested size bigger than memory pool size.\n");
        return;
    }

    free_list = (Block*)memory_pool; 
    free_list->size = size ; 
    free_list->free = 1; 
    free_list->next = NULL;
}
 
void* mem_alloc(size_t size) {
    if (size == 0) return (void*)free_list;;

    Block* current = free_list;

    while (current) {
        if (current->free && current->size >= size) {
            if (current->size >= size)  { 
                Block* new_block = (Block*)((char*)current + size);
                new_block->size = current->size - size ;
                new_block->free = 1;
                new_block->next = current->next;

                current->size = size; 
                current->free = 0; 
                current->next = new_block;
            } else {
                current->free = 0; 
            }
            return (char*)current; 
        }
        current = current->next;
    }
    return NULL; 
}


void mem_free(void* block) {
    if (block == NULL) return;

    Block* current = (Block*)((char*)block);
    
    if (current->free) {
        //fprintf(stderr, "Error: This block already free \n");
        return; 
    }
    current->free = 1; 
    
    Block* next = current->next;
    if (next && next->free) {
        current->size += next->size; 
        current->next = next->next; 
    }
}

void* mem_resize(void* block, size_t size) {
    if (block == NULL) {
        return mem_alloc(size); 
    }
    
    Block* current = (Block*)((char*)block);
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
}
