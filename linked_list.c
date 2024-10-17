/*#include <stdio.h>
#include <string.h>
#include "linked_list.h" 
#include "memory_manager.h"

// Function to initialize the list, setting the head to NULL and initializing memory management.
void list_init(Node** head,size_t size) {
    *head = NULL;  // Set the head to NULL, indicating the list is empty.
    mem_init(size); 
}

// Function to insert a new value at the end of the list.
void list_insert(Node** head, uint16_t data) {
   // Allocate memory for a new node.
    Node* new_node = (Node*)mem_alloc(sizeof(Node));
    if (new_node == NULL) {  // Check if memory allocation was successful, If allocation failed, exit the function.
        printf("Memory allocation failed!\n");
        return;
    }

    new_node->data = data;   // Set the node's data.
    new_node->next = NULL;   // Set the next pointer to NULL.

   // If the list is empty, set the new node as the head.
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

// Function to insert a node after a given node.
void list_insert_after(Node* prev_node, uint16_t data) {
    if (prev_node == NULL) { // Check if the previous node is NULL, If it is NULL, exit the function.
        printf("Error: Previous node is NULL.\n");
        return;
    }

    Node* new_node = (Node*)mem_alloc(sizeof(Node));  // Allocate memory for the new node.
    if (new_node == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    new_node->data = data;  // Set the node's data.
    new_node->next = prev_node->next;  // Link the new node's next to the previous node's next.
    prev_node->next = new_node;   // Link the previous node's next to the new node.
}


// Function to insert a node before a given node.
void list_insert_before(Node** head, Node* next_node, uint16_t data) {
    if (next_node == NULL) { // Check if the next node is NULL, If it is NULL, exit the function.
        printf("Error: Next node is NULL.\n");
        return; 
    }

    Node* new_node = (Node*)mem_alloc(sizeof(Node)); // Allocate memory for the new node.  
    if (new_node == NULL) { 
        printf("Memory allocation failed!\n");
        return; 
    }

    new_node->data = data; // Set the node's data.
    new_node->next = next_node; // Link the new node's next to the given node.

    if (*head == next_node) { // If the next node is the head, update the head to the new node.
        *head = new_node;  
    } else {
        Node* temp = *head; 
        while (temp != NULL && temp->next != next_node) {
            temp = temp->next;
        }
        if (temp == NULL) { // If the previous node is not found, free the new node and exit.
            printf("Error: Next node not found.\n");
            mem_free(new_node);
            return;
        }

        temp->next = new_node; // Link the previous node's next to the new node.
    }
}

// Function to delete a node with a specific value from the list.
void list_delete(Node** head, uint16_t data) {
    if (*head == NULL) { // Check if the list is empty, If it is empty, exit the function.
        printf("List is empty.\n");
        return; 
    }

    Node* temp = *head; // Start traversing from the head.
    Node* prev = NULL; // Keep track of the previous node.

    if (temp != NULL && temp->data == data) { // If the first node needs to be removed.
        *head = temp->next; // Move the head to the next node.
        mem_free(temp); // Free the memory for the removed node.
        return;
    }

    while (temp != NULL && temp->data != data) { // Traverse the list to find the node.
        prev = temp; // Update the previous node.
        temp = temp->next; // Move to the next node.
    }

    if (temp == NULL) { // If the node was not found, exit.
        printf("Node not found.\n");
        return;
    }

    prev->next = temp->next; // Unlink the node from the list.
    mem_free(temp); // Free the memory for the removed node.
    printf("Node was deleted.\n");
}

// Function to search for a node with a specific value in the list.
Node* list_search(Node** head, uint16_t data) {
    Node* temp = *head; // Start from the head.
    while (temp != NULL) { 
        if (temp->data == data) { // If the node's data matches, return the node.
            return temp;  
        }
        temp = temp->next; // Move to the next node.
    }
    return NULL; // If the node was not found, return NULL.
}

// Function to print the entire list.
void list_display(Node** head) {
    Node* temp = *head; // Start from the head.
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

// Function to print a part of the list between two nodes.
void list_display_range(Node** head, Node* start_node, Node* end_node) {
    if (*head == NULL) { // Check if the list is empty.
        printf("List is empty.\n");
        return; // If it is empty, exit the function.
    }

    Node* temp = (start_node == NULL) ? *head : start_node; // Start from start_node or the head.

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

// Function to count the number of nodes in the list.
int list_count_nodes(Node** head) {
    Node* temp = *head; // Start from the head.
    int count = 0; // Initialize the counter.
    while (temp != NULL) { // Traverse the list.
        count++; // Increment the counter.
        temp = temp->next; // Move to the next node.
    }
    return count; // Return the number of nodes.
}

// Function to clean up the list and free all memory.
void list_cleanup(Node** head) {
    Node* temp = *head; // Start from the head.
    while (temp != NULL) { // Traverse the list.
        Node* next = temp->next; // Save the next node.
        mem_free(temp); // Free the memory for the current node.
        temp = next; // Move to the next node.
    }
    *head = NULL; // Set the head to NULL to indicate the list is empty.
}*/
/*
#include "linked_list.h" 
#include "memory_manager.h"



// 
void list_init(Node** head, size_t size) {
    mem_init(size); //
    *head = NULL;
}

// إ
void list_insert(Node** head, uint16_t data) {
    Node* new_node = (Node*)mem_alloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    new_node->data = data;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node; //
    } else {
        Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next; // ا
        }
        temp->next = new_node;
    }
}

// إ
void list_insert_after(Node* prev_node, uint16_t data) {
    if (prev_node == NULL) {
        printf("Previous node cannot be NULL.\n");
        return;
    }

    Node* new_node = (Node*)mem_alloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    new_node->data = data;
    new_node->next = prev_node->next;
    prev_node->next = new_node;
}


void list_insert_before(Node** head, Node* next_node, uint16_t data) {
    if (*head == NULL || next_node == NULL) {
        printf("Cannot insert before NULL node.\n");
        return;
    }

    Node* new_node = (Node*)mem_alloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    new_node->data = data;

    if (*head == next_node) {
      
        new_node->next = *head;
        *head = new_node;
    } else {
        Node* temp = *head;
        while (temp != NULL && temp->next != next_node) {
            temp = temp->next;
        }
        if (temp == NULL) {
            printf("Node not found in the list.\n");
            mem_free(new_node);
            return;
        }
        new_node->next = temp->next;
        temp->next = new_node;
    }
}

// 
void list_delete(Node** head, uint16_t data) {
    if (*head == NULL) {
        printf("List is empty.\n");
        return;
    }

    Node* temp = *head;
    Node* prev = NULL;

    if (temp != NULL && temp->data == data) {
        // 
        *head = temp->next;
        mem_free(temp);
        return;
    }

    while (temp != NULL && temp->data != data) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Data not found in the list.\n");
        return;
    }

    prev->next = temp->next;
    mem_free(temp);
}

Node* list_search(Node** head, uint16_t data) {
    Node* temp = *head;
    while (temp != NULL) {
        if (temp->data == data) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

//
int list_count_nodes(Node** head) {
    int count = 0;
    Node* temp = *head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

void list_cleanup(Node** head) {
    Node* temp = *head;
    while (temp != NULL) {
        Node* next = temp->next;
        mem_free(temp);
        temp = next;
    }
    *head = NULL;
}




void list_display(Node** head) {
    Node* temp = *head;

    if (temp == NULL) {
        printf("[]"); //
        return;
    }

    printf("[");
    while (temp != NULL) {
        printf("%d", temp->data); //   
        temp = temp->next;
        if (temp != NULL) {
            printf(", "); //  
        }
    }
    printf("]"); //   
}

void list_display_range(Node** head, Node* start_node, Node* end_node) {
    Node* temp = (start_node != NULL) ? start_node : *head;

    if (temp == NULL) {
        printf("[]");
        return;
    }

    printf("[");
    while (temp != NULL && (end_node == NULL || temp != end_node->next)) {
        printf("%d", temp->data); // 
        temp = temp->next;
        if (temp != NULL && (end_node == NULL || temp != end_node->next)) {
            printf(", "); // 
        }
    }
    printf("]");
}*/



#include "linked_list.h"
#include "memory_manager.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>




void list_init(Node** head, size_t size) {
    mem_init(size); 
    *head = NULL;
}


Node* create_node(uint16_t data) {
    Node* new_node = (Node*)mem_alloc(sizeof(Node));
    if (!new_node) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    new_node->data = data;
    new_node->next = NULL;
    pthread_mutex_init(&new_node->node_mutex, NULL); // 
    return new_node;
}

//
void list_insert(Node** head, uint16_t data) {
    Node* new_node = create_node(data);
    if (!new_node) {
        return;
    }

    if (*head == NULL) {
        *head = new_node;
    } else {
        Node* temp = *head;
        pthread_mutex_lock(&temp->node_mutex); 

        while (temp->next != NULL) {
            Node* next = temp->next;
            pthread_mutex_lock(&next->node_mutex); // 
            pthread_mutex_unlock(&temp->node_mutex); // 
            temp = next;
        }

        temp->next = new_node;
        pthread_mutex_unlock(&temp->node_mutex); // 
    }
}

// 
void list_insert_after(Node* prev_node, uint16_t data) {
    if (prev_node == NULL) {
        printf("Previous node cannot be NULL.\n");
        return;
    }

    pthread_mutex_lock(&prev_node->node_mutex); 
    Node* new_node = create_node(data);
    if (!new_node) {
        pthread_mutex_unlock(&prev_node->node_mutex);
        return;
    }
    
    new_node->next = prev_node->next;
    prev_node->next = new_node;
    pthread_mutex_unlock(&prev_node->node_mutex); // 
}

// 
void list_insert_before(Node** head, Node* next_node, uint16_t data) {
    if (*head == NULL || next_node == NULL) {
        printf("Cannot insert before NULL node.\n");
        return;
    }

    pthread_mutex_lock(&(*head)->node_mutex); 
    Node* new_node = create_node(data);
    if (!new_node) {
        pthread_mutex_unlock(&(*head)->node_mutex);
        return;
    }

    if (*head == next_node) {
        //
        new_node->next = *head;
        *head = new_node;
        pthread_mutex_unlock(&new_node->node_mutex);
        return;
    }

    Node* temp = *head;
    while (temp != NULL && temp->next != next_node) {
        Node* next = temp->next;
        pthread_mutex_lock(&next->node_mutex); // 
        pthread_mutex_unlock(&temp->node_mutex); //
        temp = next;
    }

    if (temp == NULL) {
        printf("Node not found in the list.\n");
        pthread_mutex_unlock(&temp->node_mutex);
        return;
    }

    new_node->next = temp->next;
    temp->next = new_node;
    pthread_mutex_unlock(&temp->node_mutex); // 
}

// 
void list_delete(Node** head, uint16_t data) {
    if (*head == NULL) {
        printf("List is empty.\n");
        return;
    }

    pthread_mutex_lock(&(*head)->node_mutex); //

    Node* temp = *head;
    Node* prev = NULL;

    if (temp != NULL && temp->data == data) {
        // 
        *head = temp->next;
        pthread_mutex_unlock(&temp->node_mutex);
        pthread_mutex_destroy(&temp->node_mutex);
        mem_free(temp);
        return;
    }

    while (temp != NULL && temp->data != data) {
        prev = temp;
        temp = temp->next;
        if (temp != NULL) {
            pthread_mutex_lock(&temp->node_mutex); // 
        }
        pthread_mutex_unlock(&prev->node_mutex); // 
    }

    if (temp == NULL) {
        printf("Data not found in the list.\n");
        return;
    }

    prev->next = temp->next;
    pthread_mutex_unlock(&temp->node_mutex); // 
    pthread_mutex_destroy(&temp->node_mutex); //
    mem_free(temp);
}

// 
Node* list_search(Node** head, uint16_t data) {
    Node* temp = *head;
    while (temp != NULL) {
        pthread_mutex_lock(&temp->node_mutex); //
        if (temp->data == data) {
            pthread_mutex_unlock(&temp->node_mutex);
            return temp;
        }
        Node* next = temp->next;
        pthread_mutex_lock(&next->node_mutex); // 
        pthread_mutex_unlock(&temp->node_mutex); // 
        temp = next;
    }
    return NULL;
}

// 
int list_count_nodes(Node** head) {
    int count = 0;
    Node* temp = *head;
    while (temp != NULL) {
        pthread_mutex_lock(&temp->node_mutex); // 
        count++;
        Node* next = temp->next;
        pthread_mutex_lock(&next->node_mutex); //
        pthread_mutex_unlock(&temp->node_mutex); // 
        temp = next;
    }
    return count;
}

// 
void list_cleanup(Node** head) {
    Node* temp = *head;
    while (temp != NULL) {
        Node* next = temp->next;
        pthread_mutex_destroy(&temp->node_mutex); // 
        mem_free(temp); // 
        temp = next;
    }
    *head = NULL;
}

//
void list_display(Node** head) {
    Node* temp = *head;
    if (temp == NULL) {
        printf("[]");
        return;
    }

    printf("[");
    while (temp != NULL) {
        pthread_mutex_lock(&temp->node_mutex); // 
        printf("%d", temp->data); // 
        Node* next = temp->next;
        if (next != NULL) {
            printf(", "); // 
        }
        pthread_mutex_unlock(&temp->node_mutex); // 
        temp = next;
    }
    printf("]\n");
}

//
void list_display_range(Node** head, Node* start_node, Node* end_node) {
    Node* temp = (start_node != NULL) ? start_node : *head;

    if (temp == NULL) {
        printf("[]");
        return;
    }

    printf("[");
    while (temp != NULL && (end_node == NULL || temp != end_node->next)) {
        pthread_mutex_lock(&temp->node_mutex); // 
        printf("%d", temp->data); // 
        Node* next = temp->next;
        if (next != NULL && (end_node == NULL || next != end_node->next)) {
            printf(", "); // 
        }
        pthread_mutex_unlock(&temp->node_mutex); // 
        temp = next;
    }
    printf("]\n");
}
