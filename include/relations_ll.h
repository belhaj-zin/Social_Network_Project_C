#ifndef RELATIONS_LL_H
#define RELATIONS_LL_H

#include "structures.h"

// Linked List function declarations for relationships

// TODO: Add function declarations for:
// - Add relationship (friend, follow, etc.)
// - Remove relationship
// - Display relationships
// - Search for specific relationship
// Function to count the number of relationships in the linked list
int count_ll_nodes(LLnode* head);
// a function that writes the linked list to a binary file
void write_relations_to_file(LLnode* head, FILE* file) ;

#endif // RELATIONS_LL_H
