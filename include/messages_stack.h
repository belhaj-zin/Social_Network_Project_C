#ifndef MESSAGES_STACK_H
#define MESSAGES_STACK_H

#include "structures.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stack function declarations for messages

// - Push message to stack
post* empiler(post *pile, int id_post, char *contenu);

// - Pop message from stack
post* depiler(post *pile);

// - Peek at top message
post* consulter(post *pile);

// - Check if stack is empty
int estVide(post *pile);

// - Display all messages
// Function to count the number of posts in the stack
int count_posts(post* top);
//function to write the posts stack to a binary file
void write_posts_to_file(post* top, FILE* file);
void afficherTousLesPosts(post *pile);

#endif // MESSAGES_STACK_H
