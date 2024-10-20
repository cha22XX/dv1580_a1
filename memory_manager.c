
#include "memory_manager.h"



// 
void mem_init(size_t size) {
    memory_pool = malloc(size);
    if (memory_pool == NULL) {
        printf("Failed to allocate memory pool.\n");
        return;
    }

    head_pool = (Block*)malloc(sizeof(Block));
    if (head_pool == NULL) {
        printf("Failed to allocate head block.\n");
        return;
    }

    // 
    head_pool->address = memory_pool;
    head_pool->size = size;
    head_pool->is_free = true;
    head_pool->next = NULL;
}

// 
void* mem_alloc(size_t size) {
    Block* current = head_pool;

    // 
    while (current != NULL) {
        if (current->is_free && current->size >= size) {
            // 
            current->is_free = false;

            // 
            if (current->size > size) {
                Block* new_block = (Block*)malloc(sizeof(Block));
                new_block->address = current->address + size;
                new_block->size = current->size - size;
                new_block->is_free = true;
                new_block->next = current->next;

                current->size = size;
                current->next = new_block;
            }

            return current->address; // 
        }
        current = current->next;
    }

    printf("No suitable block found.\n");
    return NULL; //
}

// 
void mem_free(void* block) {
    Block* current = head_pool;

    // 
    while (current != NULL) {
        if (current->address == block) {
            current->is_free = true;

            // 
            if (current->next != NULL && current->next->is_free) {
                current->size += current->next->size;
                Block* temp = current->next;
                current->next = current->next->next;
                free(temp);
            }
            return;
        }
        current = current->next;
    }

    printf("Block not found.\n");
}

//
void* mem_resize(void* block, size_t size) {
    Block* current = head_pool;

    // 
    while (current != NULL) {
        if (current->address == block) {
            if (current->size >= size) {
                
                return block;
            }

            // 
            void* new_block = mem_alloc(size);
            if (new_block == NULL) {
                return NULL;
            }

            // 
            memcpy(new_block, block, current->size);
            mem_free(block);
            return new_block;
        }
        current = current->next;
    }

    printf("Block not found for resizing.\n");
    return NULL;
}

// 
void mem_deinit() {
    free(memory_pool); // 
    memory_pool = NULL;

    // 
    Block* current = head_pool;
    while (current != NULL) {
        Block* temp = current;
        current = current->next;
        free(temp);
    }
    head_pool = NULL;
}

