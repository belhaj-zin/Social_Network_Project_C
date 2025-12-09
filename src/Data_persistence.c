#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/structures.h"
#include "../include/Data_persistence.h"
#include "../include/abr_management.h"
#include "../include/relations_ll.h"
#include "../include/messages_stack.h"

// function to save all the nodes to the binary file
void save_user_recursive(node* node , FILE *file) {
    //FILE* file = fopen(filename, "wb");  //! i should not open the file inside a recursive function
    if (node == NULL) {
        return;
    }
    // write the node data
    //PART 1: SAVE NODE PRIMITIVE DATA
    fwrite(&(node->id), sizeof(int), 1, file);
    fwrite(node->name, sizeof(char), 50, file);

    //PART 2: SAVE FRIENDS LINKED LIST
    int friend_count = count_ll_nodes(node->friends);
    fwrite(&friend_count, sizeof(int), 1, file); // Write count first!
    write_relations_to_file(node->friends, file); // Then write all IDs

    //PART 3: SAVE fOLLOWERS LINKED LIST
    int follower_count = count_ll_nodes(node->followers);
    fwrite(&follower_count, sizeof(int), 1, file); // Write count first!
    write_relations_to_file(node->followers, file); // Then write all IDs   

    //PART 4: SAVE POSTS STACK
    int post_count = count_posts(node->posts);
    fwrite(&post_count, sizeof(int), 1, file); // Write count first!
    write_posts_to_file(node->posts, file); // Then write all posts

    // pre-order traversal of the BST (parcour en profendeur)
    save_user_recursive(node->left, file);
    save_user_recursive(node->right, file);
} 

void save_users(BST* tree, const char* filename) {

    if (tree == NULL || tree->root == NULL) {
        printf("Tree is empty, nothing to save.\n");
        return;
    }

    FILE* file = fopen(filename, "wb");
    
    if (file == NULL) {
        perror("Error opening file for reading");
        return;
    }
    
    save_user_recursive(tree->root, file);
    
    fclose(file);
}

// function to load all the nodes from the binary file
void load_users(BST* tree, const char* filename) {
    if (tree == NULL) {
        fprintf(stderr, "Error: BST structure is NULL. Cannot load users.\n");
        return;
    }

    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file for reading");
        return;
    }

    // Temporary variables to hold data read from the file
    int id;
    char name[50];
    int count; // Used for friend_count, follower_count, post_count
    int friend_id;
    char post_content[256]; // Assuming max post content size is 256

    printf("Attempting to load user data from %s...\n", filename);

    // Loop until end-of-file (EOF) is reached while reading the primary ID
    while (fread(&id, sizeof(int), 1, file) == 1) {
        
        // --- PART 1: READ PRIMITIVE DATA AND REBUILD BST STRUCTURE ---
        if (fread(name, sizeof(char), 50, file) != 50) {
            fprintf(stderr, "Error: Failed to read name record for ID %d.\n", id);
            break; 
        }

        // 1. Insert the user: This rebuilds the node structure (tree, id, name are set)
        InsertUser(tree, id, name); 
        
        // After insertion, we need the pointer to the newly created user to attach relations/posts.
        node* current_user_node = searchUser(tree, id); 

        if (current_user_node == NULL) {
             fprintf(stderr, "Error: Failed to find newly inserted user for relation loading.\n");
             break;
        }

        // --- PART 2: READ FRIENDS LIST ---
        if (fread(&count, sizeof(int), 1, file) != 1) break; // Read friend count
        
        for (int i = 0; i < count; i++) {
            if (fread(&friend_id, sizeof(int), 1, file) != 1) {
                fprintf(stderr, "Error reading friend ID for user %d.\n", id);
                break;
            }
            // Note: We only add the ID to the list structure now. The reciprocal relationship
            // must be handled by the application logic later, when all users exist.
            ajouterAmi();
        }

        // --- PART 3: READ FOLLOWERS LIST ---
        if (fread(&count, sizeof(int), 1, file) != 1) break; // Read follower count
        
        for (int i = 0; i < count; i++) {
            if (fread(&friend_id, sizeof(int), 1, file) != 1) {
                fprintf(stderr, "Error reading follower ID for user %d.\n", id);
                break;
            }
            addFollowerToList(current_user_node, friend_id); // Assuming a helper exists
        }   

        // --- PART 4: READ POSTS STACK ---
        if (fread(&count, sizeof(int), 1, file) != 1) break; // Read post count
        
        // Note: Posts are typically loaded bottom-to-top (FIFO) to maintain stack order (LIFO)
        // when pushing, but since we are reading them sequentially, we just push them one by one.
        for (int i = 0; i < count; i++) {
            // Assuming post content is always 256 bytes
            if (fread(post_content, sizeof(char), 256, file) != 256) {
                fprintf(stderr, "Error reading post content for user %d.\n", id);
                break;
            }
            pushPostToStack(current_user_node, post_content); // Assuming a helper exists
        }
    }
    
    // Check if the loop terminated cleanly
    if (feof(file)) {
        printf("Successfully loaded and rebuilt BST and network structure from file.\n");
    } else if (ferror(file)) {
        perror("Error reading file content");
    }

    fclose(file);
}


