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

// 
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

// 
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
}
