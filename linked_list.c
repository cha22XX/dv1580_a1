#include "linked_list.h"  // Inkluderar header-filen som definierar strukturen och funktionerna för den länkade listan.
#include "memory_manager.h" // Inkluderar minneshanterarens funktioner som används för allokering och frigöring av minne.


void list_init(Node** head, size_t size) {
    mem_init(size); // Initierar minneshanteraren med den specificerade storleken.
    *head = NULL;  // Sätter listans huvudpekare till NULL (vilket betyder att listan är tom).
}

// Funktion för att lägga till en ny nod i slutet av listan.
void list_insert(Node** head, uint16_t data) {
    Node* new_node = (Node*)mem_alloc(sizeof(Node)); // Allokerar minne för en ny nod.
    if (new_node == NULL) {
        printf("Memory allocation failed.\n"); // Kontrollerar om minnesallokeringen misslyckades och skriver ett felmeddelande.
        return;  // Avslutar funktionen om allokeringen misslyckades.
    }
    new_node->data = data;  // Sätter datavärdet för den nya noden.
    new_node->next = NULL; // Noden pekar initialt på NULL (inget efterföljande element).

    if (*head == NULL) {
        *head = new_node; // Om listan är tom, sätts den nya noden som listans huvud.
    } else {
        Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next; // Går till sista noden i listan.
        }
        temp->next = new_node; // Lägger till den nya noden i slutet av listan.
    }
}

// Funktion för att lägga till en nod efter en given nod.
void list_insert_after(Node* prev_node, uint16_t data) {
    if (prev_node == NULL) {
        printf("Previous node cannot be NULL.\n"); // Kontrollerar om föregående nod är NULL och skriver ett felmeddelande.
        return;
    }
    Node* new_node = (Node*)mem_alloc(sizeof(Node)); // Allokerar minne för den nya noden.
    if (new_node == NULL) {
        printf("Memory allocation failed.\n"); // Kontroll om minnesallokeringen misslyckas.
        return;
    }
    new_node->data = data;
    new_node->next = prev_node->next; // Sätter den nya nodens nästa pekare till föregående nods nästa nod.
    prev_node->next = new_node; // Uppdaterar föregående nod så att den pekar på den nya noden.
}

// Funktion för att lägga till en nod innan en given nod.
void list_insert_before(Node** head, Node* next_node, uint16_t data) {
    if (*head == NULL || next_node == NULL) { 
        printf("Cannot insert before NULL node.\n"); // Kontroll om listan är tom eller om nästa nod är NULL.
        return;
    }

    Node* new_node = (Node*)mem_alloc(sizeof(Node));  // Allokerar minne för den nya noden.
    if (new_node == NULL) {
        printf("Memory allocation failed.\n"); // Kontroll om minnesallokeringen misslyckas.
        return;
    }
    new_node->data = data;

    if (*head == next_node) { // Kontroll om nästa nod är huvudnoden i listan.
        new_node->next = *head;  // Sätter den nya nodens nästa pekare till huvudnoden.
        *head = new_node;   // Gör den nya noden till listans nya huvud.
    } else {
        Node* temp = *head;
        while (temp != NULL && temp->next != next_node) {
            temp = temp->next; // Loopar igenom listan för att hitta föregående nod.
        }
        if (temp == NULL) {
            printf("Node not found in the list.\n"); // Felmeddelande om nästa nod inte hittas.
            mem_free(new_node); // Frigör minnet för den nya noden om den inte kan infogas.
            return;
        }
        new_node->next = temp->next;  // Länkar den nya noden till nästa nod.
        temp->next = new_node;  // Lägger in den nya noden i listan före nästa nod.
    }
}

// Funktion för att ta bort en nod med ett specifikt datavärde.
void list_delete(Node** head, uint16_t data) {
    if (*head == NULL) {
        printf("List is empty.\n"); // Kontroll om listan är tom.
        return;
    }

    Node* temp = *head;  // Temporär pekare för att gå igenom listan.
    Node* prev = NULL; // Pekare för att hålla föregående nod.

    if (temp != NULL && temp->data == data) {
        *head = temp->next; // Om noden som ska tas bort är huvudnoden, uppdatera huvudet.
        mem_free(temp);  // Frigör minnet för den borttagna noden.
        return;
    }

    while (temp != NULL && temp->data != data) {
        prev = temp; // Uppdatera föregående nod.
        temp = temp->next; // Gå till nästa nod.
    }

    if (temp == NULL) {
        printf("Data not found in the list.\n"); // Felmeddelande om datavärdet inte hittas.
        return;
    }

    prev->next = temp->next;  // Ändrar föregående nods nästa pekare.
    mem_free(temp);  // Frigör minnet för den borttagna noden.
}  

// Funktion för att söka efter en nod med ett specifikt datavärde.
Node* list_search(Node** head, uint16_t data) {
    Node* temp = *head;
    while (temp != NULL) {
        if (temp->data == data) {
            return temp; // Returnerar noden om datavärdet hittas.
        }
        temp = temp->next;  // Gå till nästa nod.
    }
    return NULL;  // Returnerar NULL om datavärdet inte hittas.
}

// Funktion för att räkna antalet noder i listan.
int list_count_nodes(Node** head) {
    int count = 0;
    Node* temp = *head;
    while (temp != NULL) {
        count++; // Ökar räknaren.
        temp = temp->next; // Gå till nästa nod.
    }
    return count;  // Returnerar antalet noder.
}

// Funktion för att rensa hela listan och frigöra minnet.
void list_cleanup(Node** head) {
    Node* temp = *head;
    while (temp != NULL) {
        Node* next = temp->next;  // Sparar pekaren till nästa nod.
        mem_free(temp);  // Frigör minnet för den aktuella noden.
        temp = next;  // Gå till nästa nod.
    }
    *head = NULL;  // Sätter huvudpekaren till NULL för att indikera att listan är tom.
}

// Funktion för att skriva ut hela listan.
void list_display(Node** head) {
    Node* temp = *head;

    if (temp == NULL) {
        printf("[]");  // Om listan är tom, skrivs tomma hakparenteser ut.
        return;
    }

    printf("[");
    while (temp != NULL) {
        printf("%d", temp->data);  // Skriv ut datavärdet för varje nod.
        temp = temp->next;
        if (temp != NULL) {
            printf(", ");  // Om det finns fler noder, skriv ett komma efter datavärdet.
        }
    }
    printf("]");  // Avsluta utskriften med en hakparentes.
}

// Funktion för att skriva ut noder inom ett visst intervall.
void list_display_range(Node** head, Node* start_node, Node* end_node) {
    Node* temp = (start_node != NULL) ? start_node : *head; // Om startnoden är NULL, starta från listans huvud.

    if (temp == NULL) {
        printf("[]");  // Om listan är tom, skrivs tomma hakparenteser ut.
        return;
    }

    printf("[");
    while (temp != NULL && (end_node == NULL || temp != end_node->next)) {
        printf("%d", temp->data);  // Skriv ut datavärdet för varje nod inom intervallet.
        temp = temp->next;
        if (temp != NULL && (end_node == NULL || temp != end_node->next)) {
            printf(", ");  // Om det finns fler noder inom intervallet, skriv ett komma efter datavärdet.
        }
    }
    printf("]");
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
}
*/
