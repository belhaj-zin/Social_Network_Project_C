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



// GESTION DES AMIS (Bidirectionnel)

// Fonction : Ajouter une relation d'amitié (bidirectionnelle)
void ajouterAmi(BST* abr, int ID1, int ID2) {
    // Vérifier que l'ABR n'est pas vide
    if (abr == NULL || abr->root == NULL) {
        printf("Erreur: L'arbre est vide\n");
        return;
    }
    
    // Vérifier que ID1 et ID2 sont différents
    if (ID1 == ID2) {
        printf("Erreur: Un utilisateur ne peut pas être ami avec lui-même\n");
        return;
    }
    
    // Rechercher les deux utilisateurs dans l'ABR (utilise votre fonction)
    node* utilisateur1 = searchUser(abr, ID1);
    node* utilisateur2 = searchUser(abr, ID2);
    
    // Vérifier que les deux utilisateurs existent
    if (utilisateur1 == NULL || utilisateur2 == NULL) {
        printf("Erreur: Un ou plusieurs utilisateurs introuvables\n");
        return;
    }
    
    // Vérifier si la relation d'amitié existe déjà
    if (estEnRelation(utilisateur1->friends, ID2)) {
        printf("Les utilisateurs %d et %d sont déjà amis\n", ID1, ID2);
        return;
    }
    
    // Ajouter ID2 à la liste d'amis de ID1
    utilisateur1->friends = ajouterRelation(utilisateur1->friends, ID2);
    
    // Ajouter ID1 à la liste d'amis de ID2 (bidirectionnel)
    utilisateur2->friends = ajouterRelation(utilisateur2->friends, ID1);
    
    printf("Amitié établie entre %s (ID: %d) et %s (ID: %d)\n", 
           utilisateur1->name, ID1, utilisateur2->name, ID2);
}


// GESTION DES ABONNEMENTS (Unidirectionnel)

// Fonction : S'abonner à un utilisateur (unidirectionnel)
void sAbonner(BST* abr, int ID_Source, int ID_Cible) {
    // Vérifier que l'ABR n'est pas vide
    if (abr == NULL || abr->root == NULL) {
        printf("Erreur: L'arbre est vide\n");
        return;
    }
    
    // Vérifier que ID_Source et ID_Cible sont différents
    if (ID_Source == ID_Cible) {
        printf("Erreur: Un utilisateur ne peut pas s'abonner à lui-même\n");
        return;
    }
    
    // Rechercher les deux utilisateurs dans l'ABR (utilise votre fonction)
    node* source = searchUser(abr, ID_Source);
    node* cible = searchUser(abr, ID_Cible);
    
    // Vérifier que les deux utilisateurs existent
    if (source == NULL || cible == NULL) {
        printf("Erreur: Un ou plusieurs utilisateurs introuvables\n");
        return;
    }
    
    // Vérifier si l'abonnement existe déjà
    if (estEnRelation(cible->followers, ID_Source)) {
        printf("%s (ID: %d) est déjà abonné à %s (ID: %d)\n", 
               source->name, ID_Source, cible->name, ID_Cible);
        return;
    }
    
    // Ajouter ID_Source à la liste des followers de ID_Cible
    // (ID_Source suit ID_Cible)
    cible->followers = ajouterRelation(cible->followers, ID_Source);
    
    printf("%s (ID: %d) s'est abonné à %s (ID: %d)\n", 
           source->name, ID_Source, cible->name, ID_Cible);
}

