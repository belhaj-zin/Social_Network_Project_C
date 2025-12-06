#ifndef MESSAGES_STACK_H
#define MESSAGES_STACK_H

#include "structures.h"

// Stack function declarations for messages

// TODO: Add function declarations for:
// - Push message to stack
post* empiler(post *pile, int id_post, char *contenu) {
    // Valider les entrées
    if (contenu == NULL) {
        fprintf(stderr, "Erreur: Le contenu est NULL.\n");
        return pile;
    }
    
    if (strlen(contenu) == 0) {
        fprintf(stderr, "Erreur: Le contenu ne peut pas être vide.\n");
        return pile;
    }
    
    if (strlen(contenu) > 256) {
        fprintf(stderr, "Erreur: Le contenu dépasse la longueur maximale (256 caractères).\n");
        return pile;
    }
    
    // Créer un nouveau nœud de publication
    post *nouveau_post = (post *)malloc(sizeof(post));
    
    if (nouveau_post == NULL) {
        fprintf(stderr, "Erreur: Allocation mémoire échouée.\n");
        return pile;
    }
    
    // Initialiser le nouveau post
    nouveau_post->id_post = id_post;
    strncpy(nouveau_post->contenu, contenu, 256);
    nouveau_post->timestamp = time(NULL);  // Obtenir l'heure actuelle
    
    // Lier le nouveau post au sommet de la pile
    nouveau_post->previous = pile;
    
    printf("Publication avec ID %d a été ajoutée à la pile.\n", id_post);
    return nouveau_post;  // Retourner la nouvelle tête
}

// - Pop message from stack
post* depiler(post *pile) {
    // Vérifier si la pile est vide
    if (pile == NULL) {
        fprintf(stderr, "Erreur: La pile est vide. Impossible de dépiler.\n");
        return NULL;
    }
    
    // Stocker le post au sommet (ce qu'on va retirer)
    post *post_retire = pile;
    
    // Sauvegarder la nouvelle tête AVANT de libérer
    post *nouvelle_tete = pile->previous;
    
    printf("Publication avec ID %d a été retirée de la pile.\n", post_retire->id_post);
    
    // Libérer la mémoire du post retiré
    free(post_retire);
    
    return nouvelle_tete;  // Retourner la nouvelle tête (ne pointe pas vers de la mémoire libérée)
}
// - Peek at top message
post* consulter(post *pile) {
    // Vérifier si la pile est vide
    if (pile == NULL) {
        fprintf(stderr, "Erreur: La pile est vide. Impossible de consulter.\n");
        return NULL;
    }
    
    printf("Consultation du post au sommet (ID: %d).\n", pile->id_post);
    return pile;  // Retourne SANS libérer (safe to use)
}
// - Check if stack is empty
int estVide(post *pile) {
    return pile == NULL;
}
// - Display all messages
void afficherTousLesPosts(post *pile) {
    // Verifier si la pile est vide
    if (pile == NULL) {
        fprintf(stderr, "Erreur: La pile est vide. Aucun post a afficher.\n");
        return;
    }

    printf("\n===== Affichage de tous les posts =====\n\n");

    post *courant = pile;  // Pointer temporaire pour traverser la pile

    // Parcourir la pile du sommet vers le bas
    while (courant != NULL) {
        printf("Auteur: %s\n", courant->nom);
        printf("Contenu: %s\n", courant->contenu);
        printf("----------------------------------------\n");

        courant = courant->previous;  // Avancer au post suivant
    }

    printf("\n");
}
#endif // MESSAGES_STACK_H
