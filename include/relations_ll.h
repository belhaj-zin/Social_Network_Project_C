#ifndef RELATIONS_LL_H
#define RELATIONS_LL_H

#include "structures.h"
// Linked List function declarations for relationships


//*Check if a relationship exists in a liked list *//
int estEnRelation(LLnode* liste, int ID_Cible);

//*Add a relationship to a linked list (friend or follower)*//
LLnode* ajouterRelation(LLnode* liste, int ID_Cible);

//* Remove a relationship from a liked list (friend or follower)*//
LLnode* supprimerRelation(LLnode* liste, int ID_Cible);

//*Ajouter une relation d'amitié (bidirectionnelle)*//
void ajouterAmi(BST* abr, int ID1, int ID2);

//*S'abonner à un utilisateur (unidirectionnel)*//
void sAbonner(BST* abr, int ID_Source, int ID_Cible);
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


