#include <stdio.h>
#include <stdlib.h>
#include "../include/relations_ll.h"

// Linked List functions for relationships implementation


// Function 1: Check if a relationship exists (unchanged)
int estEnRelation(LLnode* liste, int ID_Cible) {
    LLnode* courant = liste;
    
    while (courant != NULL) {
        if (courant->id == ID_Cible) {
            return 1;  // Relationship found
        }
        courant = courant->next;
    }
    
    return 0;  // Relationship not found
}

// Function 2: Add a relationship (friend or follower)
// Returns the new head of the list
LLnode* ajouterRelation(LLnode* liste, int ID_Cible) {
    // Check if the relationship already exists
    if (estEnRelation(liste, ID_Cible)) {
        printf("Relation déjà existante avec l'utilisateur ID %d\n", ID_Cible);
        return liste;
    }
    
    // Create a new node for the relationship
    LLnode* nouveau = (LLnode*)malloc(sizeof(LLnode));
    if (nouveau == NULL) {
        printf("Erreur: Allocation mémoire échouée\n");
        return liste;
    }
    
    nouveau->id = ID_Cible;
    nouveau->next = liste;  // Insert at the beginning of the list
    
    printf("Relation ajoutée avec l'utilisateur ID %d\n", ID_Cible);
    return nouveau;  // Return the new head
}

// Function 3: Remove a relationship (friend or follower)
// Returns the new head of the list
LLnode* supprimerRelation(LLnode* liste, int ID_Cible) {
    if (liste == NULL) {
        printf("Liste vide, aucune relation à supprimer\n");
        return NULL;
    }
    
    // If the node to delete is the first one
    if (liste->id == ID_Cible) {
        LLnode* temp = liste->next;
        free(liste);
        printf("Relation supprimée avec l'utilisateur ID %d\n", ID_Cible);
        return temp;  // Return the new head
    }
    
    // Search for the node with ID_Cible
    LLnode* courant = liste;
    while (courant->next != NULL && courant->next->id != ID_Cible) {
        courant = courant->next;
    }
    
    // If ID_Cible not found
    if (courant->next == NULL) {
        printf("Relation avec l'utilisateur ID %d introuvable\n", ID_Cible);
        return liste;
    }
    
    // Remove the node
    LLnode* aSupprimer = courant->next;
    courant->next = aSupprimer->next;
    free(aSupprimer);
    
    printf("Relation supprimée avec l'utilisateur ID %d\n", ID_Cible);
    return liste;  // Return the original head
}


