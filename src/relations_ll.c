#include <stdio.h>
#include <stdlib.h>
#include "../include/relations_ll.h"
#include "../include/structures.h"
#include "../include/abr_management.h"

// Linked List functions for relationships implementation

// TODO: Implement Add function

// TODO: Implement Remove function

// TODO: Implement Display/Traverse function

// count the number of relationships in the linked list
int count_ll_nodes(LLnode* head) {
    int count = 0;
    LLnode* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

// a function that writes the linked list to a binary file
void write_relations_to_file(LLnode* head, FILE* file) {
    LLnode* current = head;
    while (current != NULL) {
        // Assuming your LLnode holds the friend's ID in current->id
        fwrite(&(current->id), sizeof(int), 1, file);
        current = current->next;
    }
}