
#include "memory_manager.h"



// Function to initialize the memory pool
void mem_init(size_t size) {
    // Allocate the memory pool with the specified size
    memory_pool = malloc(size);
    if (memory_pool == NULL) {
        printf("Failed to allocate memory pool.\n");  // Error handling if allocation fails
        return;
    }

    // Create an initial block representing the entire pool
    head_pool = (Block*)malloc(sizeof(Block));
    if (head_pool == NULL) {
        printf("Failed to allocate head block.\n");  // Error handling if block allocation fails
        return;
    }

    // Initialize first block
    head_pool->address = memory_pool;
    head_pool->size = size;
    head_pool->is_free = true;  // The block is marked as free
    head_pool->next = NULL;
}

// Function to allocate memory from the pool
void* mem_alloc(size_t size) {
    Block* current = head_pool;  // Start with first block

    // Loop through the blocks until a large enough free block is found
    while (current != NULL) {
        if (current->is_free && current->size >= size) {
            // If a free block of sufficient size is found, mark it as not free
            current->is_free = false;

            // If the block is larger than needed, split it into two blocks
            if (current->size > size) {
                Block* new_block = (Block*)malloc(sizeof(Block));
                new_block->address = current->address + size;
                new_block->size = current->size - size; // New block size is remaining space
                new_block->is_free = true;  // The new block is free
                new_block->next = current->next;  // The new block points to the next block in the list
                // Update the size of the allocated block and associate the new block
                current->size = size;
                current->next = new_block;
            }

            return current->address; // Return the address of the allocated block
        }
        current = current->next;  // Go to the next block
    }
    // If no matching block is found, print an error message and return NULL
    printf("No suitable block found.\n");
    return NULL; 
}

// Function to free a block
void mem_free(void* block) {
    Block* current = head_pool; // Start with first block

     // Loop through the blocks to find the one corresponding to the given address
    while (current != NULL) {
        if (current->address == block) {
            current->is_free = true; // Mark the block as free
            
            // Check if the next block is also free and merge them to reduce fragmentation
            if (current->next != NULL && current->next->is_free) {
                current->size += current->next->size;  // Add the size of the next block
                Block* temp = current->next;  // Temporary pointer to free the next block
                current->next = current->next->next;  // Skip the next block in the list
                free(temp);  // Free the memory for the merged block
            }
            return;
        }
        current = current->next;  // Go to the next block
    }
    printf("Block not found.\n"); // If the block is not found, print an error message
}

// Function to resize an allocated block
void* mem_resize(void* block, size_t size) {
    Block* current = head_pool;

    // Loop through the blocks to find the one corresponding to the given address
    while (current != NULL) {
        if (current->address == block) {
            // If the current block is already large enough, return the same block
            if (current->size >= size) {
                return block;
            }
            // Otherwise, allocate a new block of the desired size
            void* new_block = mem_alloc(size);
            if (new_block == NULL) {
                return NULL; // If the allocation fails, return NULL
            }

            // Copy the data from the old block to the new one
            memcpy(new_block, block, current->size);
            mem_free(block);  // Free the old block
            return new_block;  // Return the address of the new block
        }
        current = current->next;  // Go to the next block
    }
    printf("Block not found for resizing.\n");  // If the block is not found, print an error message
    return NULL;
}

// Function to uninitialize the memory manager
void mem_deinit() {
    free(memory_pool); // 
    memory_pool = NULL;

    // Free all blocks in the linked list
    Block* current = head_pool;
    while (current != NULL) {
        Block* temp = current; // Temporary pointer to hold the block to be freed
        current = current->next; 
        free(temp); // Free current block
    }
    head_pool = NULL;  // Reset head_pool when all blocks are freed
}

