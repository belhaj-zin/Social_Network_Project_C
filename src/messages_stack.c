#include <stdio.h>
#include <stdlib.h>
#include "../include/messages_stack.h"

// Stack functions for messages implementation

// TODO: Implement Push function
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
    strncpy(nouveau_post->content, contenu, 256);
    nouveau_post->timestamp = time(NULL);  // Obtenir l'heure actuelle
    
    // Lier le nouveau post au sommet de la pile
    nouveau_post->previous = pile;
    
    printf("Publication avec ID %d a été ajoutée à la pile.\n", id_post);
    return nouveau_post;  // Retourner la nouvelle tête
}

// TODO: Implement Pop function
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

// TODO: Implement Peek function
post* consulter(post *pile) {
    // Vérifier si la pile est vide
    if (pile == NULL) {
        fprintf(stderr, "Erreur: La pile est vide. Impossible de consulter.\n");
        return NULL;
    }
    
    printf("Consultation du post au sommet (ID: %d).\n", pile->id_post);
    return pile;  // Retourne SANS libérer (safe to use)
}

// TODO: Implement isEmpty function

//function to count the number of posts in the stack
int count_posts(post* top) {
    int count = 0;
    post* current = top;
    while (current != NULL) {
        // Assuming your stack links via a 'previous' or 'next' pointer
        count++; 
        current = current->previous; 
    }
    return count;
}

//function to write the posts stack to a binary file
void write_posts_to_file(post* top, FILE* file) {
    post* current = top;
    while (current != NULL) {
        // Write the post content
        fwrite(current->content, sizeof(char), 256, file); 
        current = current->previous; 
    }
}
int estVide(post *pile) {
    return pile == NULL;
}
