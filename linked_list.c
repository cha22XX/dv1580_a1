#include "linked_list.h"  // Includes the header file that defines the structure and functions of the linked list
#include "memory_manager.h"




void list_init(Node** head, size_t size) {
    mem_init(size); // Initializes the memory manager with the specified size
    *head = NULL;  // Sets the list's head to NULL (empty list)
}

// 
void list_insert(Node** head, uint16_t data) {
    Node* new_node = (Node*)mem_alloc(sizeof(Node)); // Allocates memory for a new node
    if (new_node == NULL) {
        // Checks if the memory allocation failed, Prints an error message
        printf("Memory allocation failed.\n");
        return;  // end the function if the allocation failed
    }
    new_node->data = data;  // Sets the data value for the new node
    new_node->next = NULL; // Initially, the next node points to NULL

    // Checks if the list is empty
    if (*head == NULL) {
        *head = new_node; // Sets the new node as the head of the list
    } else {
        Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next; 
        }
        temp->next = new_node; // Adds the new node to the end of the list
    }
}

// 
void list_insert_after(Node* prev_node, uint16_t data) {
    if (prev_node == NULL) {
        // Checks if the previous node is NULL, Prints an error message
        printf("Previous node cannot be NULL.\n");
        return;
    }
    // Allocates memory for the new node
    Node* new_node = (Node*)mem_alloc(sizeof(Node));
    if (new_node == NULL) {  // Checks if the memory allocation failed, Prints an error message
        printf("Memory allocation failed.\n"); 
        return;
    }
    new_node->data = data;
    new_node->next = prev_node->next;
    prev_node->next = new_node;
}


void list_insert_before(Node** head, Node* next_node, uint16_t data) {
    if (*head == NULL || next_node == NULL) { 
        // Checks if the list is empty or if the next node is NULL, Prints an error message
        printf("Cannot insert before NULL node.\n");
        return;
    }

    Node* new_node = (Node*)mem_alloc(sizeof(Node));  // Allocates memory for the new node
    if (new_node == NULL) {  // Checks if the memory allocation failed, Prints an error message
        printf("Memory allocation failed.\n");
        return;
    }
    new_node->data = data;

    if (*head == next_node) { // Checks if the next node is the head of the list
        new_node->next = *head;  // Links the new node's next to the head of the list
        *head = new_node;   // Sets the new node as the head of the list
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
        new_node->next = temp->next;  // Links the new node's next to next_node
        temp->next = new_node;
    }
}

// Removes a node with a specific data value
void list_delete(Node** head, uint16_t data) {
    if (*head == NULL) {
        printf("List is empty.\n"); // Check if the list is empty
        return;
    }

    Node* temp = *head;  // Temporary pointer to traverse the list
    Node* prev = NULL; // Pointer to keep track of the previous node

    if (temp != NULL && temp->data == data) {
        // Om noden som ska tas bort är huvudnoden, Sätt listans huvud till nästa nod
        *head = temp->next;
        mem_free(temp);  // Free the memory for the removed node
        return;
    }

    while (temp != NULL && temp->data != data) {
        prev = temp; // Update the previous node
        temp = temp->next; // Go to the next node
    }

    if (temp == NULL) { // Check if the data value was found
        printf("Data not found in the list.\n");
        return; // Exit the function if the data value was not found
    }

    prev->next = temp->next;  // Switch the previous node's next pointer
    mem_free(temp);  // Free the memory for the removed node
}  

// Search for a node with a specific data value
Node* list_search(Node** head, uint16_t data) {
    Node* temp = *head;
    while (temp != NULL) {
        if (temp->data == data) {
            return temp; // Return the node if the data value is found
        }
        temp = temp->next;  // Go to the next node
    }
    return NULL;  // Return NULL if the data value was not found
}

// Count the number of nodes in the list
int list_count_nodes(Node** head) {
    int count = 0;
    Node* temp = *head;
    while (temp != NULL) {
        count++; // Increment the counter
        temp = temp->next; // Go to the next node
    }
    return count;  // Return the number of nodes
}

// Clear the entire list and free the memory
void list_cleanup(Node** head) {
    Node* temp = *head;
    while (temp != NULL) {
        Node* next = temp->next;  //Save the pointer to the next node
        mem_free(temp);  // Free the memory for the current node
        temp = next;  // Go to the next node
    }
    *head = NULL;  // Set the list's head to NULL to indicate that the list is empty
}

// Display the entire list
void list_display(Node** head) {
    Node* temp = *head;

    if (temp == NULL) {
        printf("[]"); 
        return;
    }

    printf("[");
    while (temp != NULL) {
        printf("%d", temp->data); 
        temp = temp->next;
        if (temp != NULL) {
            printf(", "); 
        }
    }
    printf("]"); 
}

// Display nodes within a certain range
void list_display_range(Node** head, Node* start_node, Node* end_node) {
    Node* temp = (start_node != NULL) ? start_node : *head; // If start node is NULL, start from the head of the list

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
}
