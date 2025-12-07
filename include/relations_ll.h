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

//*S'abonner à un utilisateur (unidirectionnel)
void sAbonner(BST* abr, int ID_Source, int ID_Cible);

#endif // RELATIONS_LL_H


