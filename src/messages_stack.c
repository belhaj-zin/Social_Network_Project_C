#include <stdio.h>
#include <stdlib.h>
#include "../include/messages_stack.h"

// Stack functions for messages implementation

// TODO: Implement Push function

// TODO: Implement Pop function

// TODO: Implement Peek function

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