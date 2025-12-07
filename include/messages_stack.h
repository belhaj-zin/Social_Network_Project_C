#ifndef MESSAGES_STACK_H
#define MESSAGES_STACK_H

#include "structures.h"

// Stack function declarations for messages

// TODO: Add function declarations for:
// - Push message to stack
// - Pop message from stack
// - Peek at top message
// - Check if stack is empty
// - Display all messages
// Function to count the number of posts in the stack
int count_posts(post* top);
//function to write the posts stack to a binary file
void write_posts_to_file(post* top, FILE* file);

#endif // MESSAGES_STACK_H
