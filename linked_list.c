#include "linked_list.h" 
#include "memory_manager.h"




void list_init(Node** head, size_t size) {
    mem_init(size);
    *head = NULL;
}

// 
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
            temp = temp->next; // 
        }
        temp->next = new_node;
    }
}

// 
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

// 
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
        // 
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
