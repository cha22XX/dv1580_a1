/*#ifndef MEMORY_MANAGER_H  
#define MEMORY_MANAGER_H  

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>  


#define POOL_SIZE 50000000 
typedef struct Block {
    size_t size;        
    int free;          
    struct Block* next; 
} Block;

static char memory_pool[POOL_SIZE];   
static Block* free_list = NULL;


void mem_init(size_t size);
void* mem_alloc(size_t size);
void mem_free(void* block);
void* mem_resize(void* block, size_t new_size);
void mem_deinit(void);

#endif // MEMORY_MANAGER_H*/

#ifndef MEMORY_MANAGER_H  
#define MEMORY_MANAGER_H  

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>  


#define POOL_SIZE 81920000 
#define MAX_BLOCKS 100000      

typedef struct Block {
    size_t size;
    int free;     
} Block;

static char memory_pool[POOL_SIZE];  
static Block block_list[MAX_BLOCKS]; 
static size_t num_blocks = 0; 

void mem_init(size_t size);
void* mem_alloc(size_t size);
void mem_free(void* block);
void* mem_resize(void* block, size_t size);
void mem_deinit(void);

#endif


