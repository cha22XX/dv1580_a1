#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define POOL_SIZE 1024  //Define a constant that specifies the size of the memory pool,in this case (2048 bytes)

//a block of memory with size, status (free), and pointer to the next block in the memory pool
typedef struct Block {
    size_t size;        
    int free;          
    struct Block* next; 
} Block;

//a structure for storing 16-bit data in a linked list
typedef struct Node {
    uint16_t data;
    struct Node* next;
} Node;

static char memory_pool[POOL_SIZE];   //a static array of 2048 bytes
static Block* free_list = NULL;      //a pointer to the first free block in the linked list of memory blocks

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

/*Allocates a memory block of the requested size from the static memory pool.Traverses the linked list of free blocks to find a large enough block. 
Splits the block if it is larger than the requested size. 
Returns a pointer to the allocated block, or NULL if no large enough block exists.*/
void* mem_alloc(size_t size) {
    if (size == 0 || size + sizeof(Block) > POOL_SIZE) return NULL;

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
            return (char*)current + sizeof(Block);
        }
        current = current->next;
    }
    return NULL; 
}

/*The function checks if the block is NULL and if so returns without doing anything.*/
void mem_free(void* block) {
    if (block == NULL) return;

    Block* current = (Block*)((char*)block - sizeof(Block));
    //Check if the block is already free; if so, print an error message
    if (current->free) {
        fprintf(stderr, "Error: This block already free \n");
        return; 
    }
    current->free = 1;   //mark the block as free
    //Check if the subsequent block is also free, If it is free, merge it with the current block
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

//Initializes a linked list by setting the main pointer to NULL.
void list_init(Node** head, size_t size) {
    *head = NULL;     //sets the main pointer to NULL to signal an empty list
    mem_init(size);
}

/*it adds a new node with the specified data value to the end of a linked list. It allocates memory for the node and checks if the allocation was successful.
If the list is empty, the new node becomes the master node; otherwise, the list is traversed to find the last node, to which the new node is connected.*/
void list_insert(Node** head, int data) {
    //allocates memory for a new node using mem_alloc
    Node* new_node = (Node*)mem_alloc(sizeof(Node));
    //Checks if the memory allocation was successful. If it fails, an error message is printed and the function exits
    if (new_node == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    new_node->data = data;
    new_node->next = NULL;

    /*Checks if the list is empty (head is NULL), if the list is empty, set the new node as the parent node, 
    if the list is not empty, traverse the list to find the last node*/
    if (*head == NULL) {
        *head = new_node;
    } else {
        Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

/*it inserts a new node with a specified data value after a specified previous node in a linked list.
It starts by checking if the previous node is NULL, and if so, prints an error message. 
If the node is valid, the function allocates memory for the new node and checks whether the allocation succeeds.*/
void list_insert_after(Node* prev_node, int data) {
    //Checks if the previous node is NULL. If it is, an error message is printed and the function is terminated.
    if (prev_node == NULL) {
        printf("Error: Previous node is NULL.\n");
        return;
    }
    /*Allocates memory for a new node using mem_alloc. 
    Checks if the memory allocation was successful. If it fails, an error message is printed and the function exits.*/
    Node* new_node = (Node*)mem_alloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    new_node->data = data;   //Assigns data to the new node.
    new_node->next = prev_node->next;   //Sets the new node's next pointer to the current next node of the previous node
    prev_node->next = new_node;    //Updates the previous node's next pointer to point to the new node. 
}

/*It inserts a new node with a specified data value before a specified node in a linked list. 
It starts by checking if the specified node is NULL, and if so, prints an error message. 
If the node is valid, the function allocates memory for the new node and checks whether the allocation succeeds. */
void list_insert_before(Node** head, Node* next_node, int data) {
    //Checks if the node that should be after the new node is NULL. If it is, an error message is printed and the function is terminated.
    if (next_node == NULL) {
        printf("Error: Next node is NULL.\n");
        return;
    }
    /*Allocate memory for the new node using mem_alloc.
    Checks if the memory allocation was successful. If it fails, an error message is printed and the function exits.*/
    Node* new_node = (Node*)mem_alloc(sizeof(Node));  
    if (new_node == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    new_node->data = data;   //Assigns data to the new node
    new_node->next = next_node;   //Sets the new node's next pointer to the node that should be behind

    //Checks if the new node should become the master node. If so, the main pointer is updated
    if (*head == next_node) {
        *head = new_node;  
    } else {
        Node* temp = *head;
        while (temp != NULL && temp->next != next_node) {
            temp = temp->next;
        }
    //Checks if the specified node was not found in the list. If not found, an error message is printed, and the new node is released
    if (temp == NULL) {
            printf("Error: Next node not found .\n");
            mem_free(new_node);
            return;
        }
        temp->next = new_node;   //Updates the next pointer of the found node to point to the new node
    }
}

/*it removes a node from a linked list based on a specified data value.
if the list is empty, a message is printed. If the first node contains the value, it is removed and the memory is freed.
otherwise, the list is traversed until the node with the specific value is found.*/
void list_delete(Node** head, int data) {
    //check if the list is empty. If so, a message is printed and the function exits
    if (*head == NULL) {
        printf("List is empty.\n");
        return;
    }

    Node* temp = *head;   //create a temporary pointer to traverse the list
    Node* prev = NULL;   //pointer to keep track of previous node during traversal

    /*if the first node contains the searched data value, update the main pointer
    and free the memory for the first node.*/
    if (temp != NULL && temp->data == data) {
        *head = temp->next;
        mem_free(temp);
        return;
    }

    while (temp != NULL && temp->data != data) {  //traverse the list until the node with the searched data value is found
        prev = temp;
        temp = temp->next;
    }
    //if the node is not found, a message is printed and the function exits
    if (temp == NULL) {
        printf("Node not found.\n");
        return;
    }

    prev->next = temp->next;   //update the previous node's next pointer to skip the removed node
    mem_free(temp);  //free the memory for the removed node
    printf("Node was deleted.\n");
}

/*It looks for a node in the linked list that contains the specified data value. It starts from the head node and goes through each node in the list one by one. 
If a node with the matching data value is found, the function returns the pointer to that node. 
If no such node exists, NULL is returned, indicating that the data value is not in the list.*/
Node* list_search(Node** head, int data) {
    Node* temp = *head; 
    while (temp != NULL) { 
        if (temp->data == data) {
            return temp;  
        }
        temp = temp->next;  
    }
    return NULL;
}

/*prints the contents of a linked list. It starts from the head node and goes through each node in the list.*/
void list_display(Node** head) {
    Node* temp = *head;
    printf("[");
    while (temp != NULL) {
        printf("%d", temp->data);
        temp = temp->next;
        if (temp != NULL) {
            printf(", ");
        }
    }
    printf("]\n");
}

//prints values ​​from a linked list between two specific nodes
void list_display_range(Node** head, Node* start_node, Node* end_node) {
    if (*head == NULL) {
        printf("List is empty.\n");
        return;
    }
    Node* temp = (start_node == NULL) ? *head : start_node;
    printf("[");
    while (temp != NULL && temp != end_node) {
        printf("%d", temp->data);
        if (temp->next != NULL && temp->next != end_node) {
            printf(", ");
        }
        temp = temp->next;
    }
    if (end_node != NULL && temp == end_node) {
        printf("%d", temp->data);
    }
    printf("]\n");
}

/*counts the number of nodes in a linked list. 
It starts from the head of the list and iterates through each node using a temporary pointer, temp.*/
int list_count_nodes(Node** head) {
    Node* temp = *head;
    int count = 0;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

//is used to free all nodes in a linked list and reset the list.
void list_cleanup(Node** head) {
    Node* temp = *head;
    while (temp != NULL) {
        Node* next = temp->next;
        mem_free(temp);
        temp = next;
    }
    *head = NULL;
}
