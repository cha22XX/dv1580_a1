#include "linked_list.h"   // Inkludera header-filen för länkad lista
#include "memory_manager.h" // Inkludera minneshanteringssystemet

// Initierar den länkade listan
void list_init(Node** head, size_t size) {
    *head = NULL; // Sätt listans huvud till NULL, vilket innebär att listan är tom
}

// Infogar en ny nod i slutet av listan
void list_insert(Node** head, uint16_t data) {
    Node* new_node = (Node*)mem_alloc(sizeof(Node)); // Allokera minne för en ny nod
    if (new_node == NULL) {
        printf("Memory allocation failed.\n"); // Kontrollera om minnesallokering misslyckades
        return; // Avsluta funktionen om allokeringen misslyckades
    }
    new_node->data = data; // Tilldela data till den nya noden
    new_node->next = NULL; // Sätt nästa pekare till NULL

    if (*head == NULL) {
        *head = new_node; // Om listan är tom, gör den nya noden till huvud
    } else {
        Node* temp = *head; // Temporär pekare för att traversera listan
        while (temp->next != NULL) {
            temp = temp->next; // Gå till slutet av listan
        }
        temp->next = new_node; // Koppla den nya noden till slutet av listan
    }
}

// Infogar en ny nod efter en given nod
void list_insert_after(Node* prev_node, uint16_t data) {
    if (prev_node == NULL) {
        printf("Previous node cannot be NULL.\n"); // Kontrollera att den föregående noden inte är NULL
        return; // Avsluta om den föregående noden är NULL
    }

    Node* new_node = (Node*)mem_alloc(sizeof(Node)); // Allokera minne för en ny nod
    if (new_node == NULL) {
        printf("Memory allocation failed.\n"); // Kontrollera om allokeringen misslyckades
        return; // Avsluta funktionen om allokeringen misslyckades
    }
    new_node->data = data; // Tilldela data till den nya noden
    new_node->next = prev_node->next; // Koppla den nya nodens nästa pekare
    prev_node->next = new_node; // Koppla den nya noden efter den föregående noden
}

// Infogar en ny nod före en given nod
void list_insert_before(Node** head, Node* next_node, uint16_t data) {
    if (*head == NULL || next_node == NULL) {
        printf("Cannot insert before NULL node.\n"); // Kontrollera att listan och nästa nod inte är NULL
        return; // Avsluta om någon av dem är NULL
    }

    Node* new_node = (Node*)mem_alloc(sizeof(Node)); // Allokera minne för en ny nod
    if (new_node == NULL) {
        printf("Memory allocation failed.\n"); // Kontrollera om allokeringen misslyckades
        return; // Avsluta funktionen om allokeringen misslyckades
    }
    new_node->data = data; // Tilldela data till den nya noden

    if (*head == next_node) {
        // Om nästa nod är huvud, sätt den nya noden till huvud
        new_node->next = *head;
        *head = new_node;
    } else {
        Node* temp = *head; // Temporär pekare för att traversera listan
        while (temp != NULL && temp->next != next_node) {
            temp = temp->next; // Gå till noden innan nästa nod
        }
        if (temp == NULL) {
            printf("Node not found in the list.\n"); // Kontrollera om noden hittades
            mem_free(new_node); // Frigör minnet för den nya noden
            return; // Avsluta funktionen om noden inte hittades
        }
        new_node->next = temp->next; // Koppla nästa pekare till den nya noden
        temp->next = new_node; // Koppla den nya noden
    }
}

// Tar bort en nod med ett specifikt datavärde
void list_delete(Node** head, uint16_t data) {
    if (*head == NULL) {
        printf("List is empty.\n"); // Kontrollera om listan är tom
        return; // Avsluta om listan är tom
    }

    Node* temp = *head; // Temporär pekare för att traversera listan
    Node* prev = NULL;  // Pekare för att hålla reda på den föregående noden

    if (temp != NULL && temp->data == data) {
        // Om noden som ska tas bort är huvudnoden
        *head = temp->next; // Sätt listans huvud till nästa nod
        mem_free(temp);      // Frigör minnet för den borttagna noden
        return; // Avsluta funktionen
    }

    while (temp != NULL && temp->data != data) {
        prev = temp; // Uppdatera den föregående noden
        temp = temp->next; // Gå till nästa nod
    }

    if (temp == NULL) {
        printf("Data not found in the list.\n"); // Kontrollera om datavärdet hittades
        return; // Avsluta funktionen om datavärdet inte hittades
    }

    prev->next = temp->next; // Koppla om den föregående nodens nästa pekare
    mem_free(temp); // Frigör minnet för den borttagna noden
}

// Sök efter en nod med ett specifikt datavärde
Node* list_search(Node** head, uint16_t data) {
    Node* temp = *head; // Temporär pekare för att traversera listan
    while (temp != NULL) {
        if (temp->data == data) {
            return temp; // Returnera noden om datavärdet hittas
        }
        temp = temp->next; // Gå till nästa nod
    }
    return NULL; // Returnera NULL om datavärdet inte hittades
}

// Räkna antalet noder i listan
int list_count_nodes(Node** head) {
    int count = 0; // Variabel för att räkna noder
    Node* temp = *head; // Temporär pekare för att traversera listan
    while (temp != NULL) {
        count++; // Öka räknaren
        temp = temp->next; // Gå till nästa nod
    }
    return count; // Returnera antalet noder
}

// Rensa hela listan och frigör minnet
void list_cleanup(Node** head) {
    Node* temp = *head; // Temporär pekare för att traversera listan
    while (temp != NULL) {
        Node* next = temp->next; // Spara pekaren till nästa nod
        mem_free(temp); // Frigör minnet för den aktuella noden
        temp = next; // Gå till nästa nod
    }
    *head = NULL; // Sätt listans huvud till NULL för att indikera att listan är tom
}

// Visa hela listan
void list_display(Node** head) {
    Node* temp = *head; // Temporär pekare för att traversera listan

    if (temp == NULL) {
        printf("[]"); // Om listan är tom, skriv ut tomt array
        return; // Avsluta funktionen
    }

    printf("["); // Skriv ut öppnande hakparentes
    while (temp != NULL) {
        printf("%d", temp->data); // Skriv ut datavärdet för den aktuella noden
        temp = temp->next; // Gå till nästa nod
        if (temp != NULL) {
            printf(", "); // Skriv ut ett kommatecken om det finns fler noder
        }
    }
    printf("]"); // Skriv ut stängande hakparentes
}

// Visa noder inom ett visst intervall
void list_display_range(Node** head, Node* start_node, Node* end_node) {
    Node* temp = (start_node != NULL) ? start_node : *head; // Om startnod är NULL, börja från listans huvud

    if (temp == NULL) {
        printf("[]"); // Om listan är tom, skriv ut tomt array
        return; // Avsluta funktionen
    }

    printf("["); // Skriv ut öppnande hakparentes
    while (temp != NULL && (end_node == NULL || temp != end_node->next)) {
        printf("%d", temp->data); // Skriv ut datavärdet för den aktuella noden
        temp = temp->next; // Gå till nästa nod
        if (temp != NULL && (end_node == NULL || temp != end_node->next)) {
            printf(", "); // Skriv ut ett kommatecken om det finns fler noder och inte har nått slutet
        }
    }
    printf("]"); // Skriv ut stängande hakparentes
}













/*#include "linked_list.h"  // Includes the header file that defines the structure and functions of the linked list
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
}*/
