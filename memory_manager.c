#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "memory_manager.h"

// Function to initialize the memory pool.
void mem_init(size_t size) {
    // Check if the requested size is greater than the maximum pool size.
    if (size > POOL_SIZE) {
        fprintf(stderr, "Error: Requested size bigger than memory pool size.\n");
        return; // Exit the function if the size is too large.
    }

    free_list = (Block*)memory_pool; // Initialize the free list to point to the start of the memory pool.
    free_list->size = size; // Set the size of the free block.
    free_list->free = 1; // Mark the block as free.
    free_list->next = NULL; // Set the next pointer to NULL, indicating it's the only block.
}

// Function to allocate a block of memory of the specified size.
void* mem_alloc(size_t size) {
    // Return the free list if the requested size is 0.
    if (size == 0) return (void*)free_list;

    Block* current = free_list; // Start from the free list.

    // Traverse the free list to find a suitable block.
    while (current) {
        // Check if the current block is free and large enough.
        if (current->free && current->size >= size) {
            if (current->size >= size) { 
                Block* new_block = (Block*)((char*)current + size); // Create a new block after the allocated size.
                new_block->size = current->size - size; // Set the size of the new block.
                new_block->free = 1; // Mark the new block as free.
                new_block->next = current->next; // Link the new block to the next block.

                current->size = size; // Resize the current block.
                current->free = 0; // Mark the current block as allocated.
                current->next = new_block; // Update the next pointer.
            } else {
                // If the block is exactly the requested size, mark it as allocated.
                current->free = 0; 
            }
            return (char*)current; // Return the pointer to the allocated block.
        }
        current = current->next; // Move to the next block in the free list.
    }
    return NULL; // Return NULL if no suitable block was found.
}

// Function to free a previously allocated block of memory.
void mem_free(void* block) {
    if (block == NULL) return; // Exit if the block is NULL.

    Block* current = (Block*)((char*)block); // Cast the block pointer to a Block type.

    // Check if the block is already free.
    if (current->free) {
        // Uncomment the next line to print an error if the block is already free.
        // fprintf(stderr, "Error: This block already free \n");
        return; // Exit the function if the block is already free.
    }
    current->free = 1; // Mark the block as free.
    
    Block* next = current->next; // Get the next block.
    // If the next block is free, merge it with the current block.
    if (next && next->free) {
        current->size += next->size; // Increase the size of the current block.
        current->next = next->next; // Link to the next block in the free list.
    }
}

// Function to resize a previously allocated block of memory.
void* mem_resize(void* block, size_t size) {
    if (block == NULL) { // If the block is NULL, allocate a new block.
        return mem_alloc(size); 
    }
    
    Block* current = (Block*)((char*)block); // Cast the block pointer to a Block type.
    // Check if the block is free.
    if (current->free) {
        fprintf(stderr, "Error: Can't resize a free block!\n");
        return NULL; // Exit if trying to resize a free block.
    }

    // If the requested size is less than or equal to the current size, return the same block.
    if (size <= current->size) {
        return block;
    }

    // Allocate a new block of the requested size.
    void* new_block = mem_alloc(size);
    if (new_block == NULL) {
        return NULL; // Return NULL if the allocation fails.
    }

    // Copy the data from the old block to the new block.
    memcpy(new_block, block, current->size);
    mem_free(block); // Free the old block.
    return new_block; // Return the pointer to the newly allocated block.
}

// Function to deinitialize the memory manager and reset the free list.
void mem_deinit(void) {
    free_list = NULL; // Reset the free list to indicate that no memory is allocated.
}
