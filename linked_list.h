#ifndef MEMORY_MANAGER_H  
#define MEMORY_MANAGER_H  

#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define POOL_SIZE 1024  

typedef struct Block {
    size_t size;        
    int free;          
    struct Block* next; 
} Block;

typedef struct Node {
    uint16_t data;
    struct Node* next;
} Node;

static char memory_pool[POOL_SIZE];   
static Block* free_list = NULL;      

void list_init(Node** head, size_t size);
void list_insert(Node** head, int data);
void list_insert_after(Node* prev_node, int data);
void list_insert_before(Node** head, Node* next_node, int data);
void list_delete(Node** head, int data);
Node* list_search(Node** head, int data);
void list_display(Node** head);
void list_display_range(Node** head, Node* start_node, Node* end_node);
int list_count_nodes(Node** head);
void list_cleanup(Node** head);

#endif // MEMORY_MANAGER_H