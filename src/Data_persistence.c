#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/structures.h"
#include "../include/Data_persistence.h"
#include "../include/abr_management.h"
#include "../include/relations_ll.h"
#include "../include/messages_stack.h"

void save_user_recursive(node* current, FILE *file) {
    if (current == NULL) {
        return;
    }
    
    // --- PART 1: SAVE NODE PRIMITIVE DATA ---
    // ID and Name are essential for rebuilding the BST
    fwrite(&(current->id), sizeof(int), 1, file);
    fwrite(current->name, sizeof(char), 50, file);

    // --- PART 2: SAVE POSTS STACK ---
    int post_count = count_posts(current->posts);
    fwrite(&post_count, sizeof(int), 1, file); // Write count first!
    write_posts_to_file(current->posts, file); // Then write all posts content
    
    // NOTE: FRIENDS and FOLLOWERS ARE SKIPPED here because they go to relations.txt
    
    // Pre-order traversal
    save_user_recursive(current->left, file);
    save_user_recursive(current->right, file);
} 

void save_users(BST* tree, const char* filename) {

    if (tree == NULL || tree->root == NULL) {
        printf("Tree is empty, nothing to save.\n");
        return;
    }

    FILE* file = fopen(filename, "wb");
    
    if (file == NULL) {
        perror("Error opening file for writing");
        return;
    }
    
    save_user_recursive(tree->root, file);
    
    fclose(file);
    printf("User data (ID, Name, Posts) successfully saved to %s.\n", filename);
    //Relations must be saved separately to relations.txt
}

void load_users(BST* tree, const char* filename) {
    if (tree == NULL) {
        fprintf(stderr, "Error: BST structure is NULL. Cannot load users.\n");
        return;
    }

    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening user file for reading");
        return;
    }

    int id;
    char name[50];
    int count; 
    char post_content[256]; 
    
    // --- PASS 1: LOAD PRIMITIVE DATA AND POSTS ---
    while (fread(&id, sizeof(int), 1, file) == 1) {
        
        if (fread(name, sizeof(char), 50, file) != 50) {
            fprintf(stderr, "Error: Failed to read name record for ID %d.\n", id);
            break; 
        }

        // 1. Insert the user (Rebuilds the BST structure)
        InsertUser(tree, id, name); 
        node* current_user_node = searchUser(tree, id); 

        if (current_user_node == NULL) { break; } 

        // 2. READ POSTS STACK
        if (fread(&count, sizeof(int), 1, file) != 1) break; 
        for (int i = 0; i < count; i++) {
            if (fread(post_content, sizeof(char), 256, file) != 256) break;
            current_user_node->posts = empiler(current_user_node->posts,i+1, post_content); 
        }
    }
    
    fclose(file);
    
    // --- PASS 2: LOAD RELATIONS ---
    // After ALL users exist in the BST, call the separate function 
    // to read relations.txt and establish links.
    if (feof(file)) {
        printf("Structural data and posts loaded. Starting relations loading...\n");
        load_relations_from_file(tree, "relations.txt");
        printf("User data fully loaded.\n");
    } else if (ferror(file)) {
        perror("Error reading file content");
    }
}

void load_relations_from_file(BST* tree, const char* relations_filename) {
    if (tree == NULL || tree->root == NULL) {
        fprintf(stderr, "Error: BST is empty. Cannot load relations.\n");
        return;
    }

    // Open the file in read text mode ("r")
    FILE* file = fopen(relations_filename, "r");
    if (file == NULL) {
        perror("Error opening relations file");
        return;
    }

    char relation_type;
    int id_source;
    int id_target;
    int lines_processed = 0;

    printf("Starting to load network relations from %s...\n", relations_filename);

    // Loop until end-of-file (EOF) is reached
    // We expect 3 fields: a character and two integers
    while (fscanf(file, " %c %d %d", &relation_type, &id_source, &id_target) == 3) {
        
        // Skip users being friends/subscribers of themselves (handled by helpers, but safe to check)
        if (id_source == id_target) {
            fprintf(stderr, "Warning: Skipped self-relation found: %c %d %d\n", 
                    relation_type, id_source, id_target);
            continue; 
        }

        // Process the relation based on the type read
        if (relation_type == 'F' || relation_type == 'f') {
            // Friends are bidirectional, call your specific function
            // Note: Your 'ajouterAmi' function handles checking if users exist.
            ajouterAmi(tree, id_source, id_target);
        
        } else if (relation_type == 'S' || relation_type == 's') {
            // Subscription is unidirectional: ID_Source subscribes to ID_Target
            // ID_Source is the follower, ID_Target is the followee.
            sAbonner(tree, id_source, id_target);

        } else {
            fprintf(stderr, "Warning: Unknown relation type '%c' encountered. Skipping line.\n", relation_type);
        }
        lines_processed++;
    }

    if (ferror(file)) {
        perror("Error reading relations file content");
    } else {
        printf("Successfully processed %d relations.\n", lines_processed);
    }
    
    fclose(file);
}

void save_relations_recursive(node* current, FILE* file) {
    if (current == NULL) {
        return;
    }
    
    // --- PART 1: PROCESS CURRENT NODE ---
    int source_id = current->id;
    
    // A. Write Friends (Bidirectional)
    LLnode* friend_current = current->friends;
    while (friend_current != NULL) {
        // Write one direction: F [Source ID] [Target ID]
        // Note: Due to bidirectionality, we must only write the friendship once
        // to avoid redundancy and complexity in loading. A common strategy is to 
        // only write the friendship if the Source ID is SMALLER than the Target ID.
        // This ensures each pair is written exactly once.
        if (source_id < friend_current->id) {
            fprintf(file, "F %d %d\n", source_id, friend_current->id);
        }
        friend_current = friend_current->next;
    }
    
    // B. Write Followers (Unidirectional)
    // The list 'followers' on the node means the IDs in the list FOLLOW the current user.
    LLnode* follower_current = current->followers;
    while (follower_current != NULL) {
        // S [ID Source (The Follower)] [ID Target (The Followee)]
        // Here, the follower ID is inside the list, and the current node is the target.
        fprintf(file, "S %d %d\n", follower_current->id, source_id);
        follower_current = follower_current->next;
    }
    
    // --- PART 2: RECURSE ---
    save_relations_recursive(current->left, file);
    save_relations_recursive(current->right, file);
}

void save_relations_to_file(BST* tree, const char* filename) {
    if (tree == NULL || tree->root == NULL) {
        printf("Tree is empty, no relations to save.\n");
        return;
    }

    // Open the file in WRITE TEXT mode ("w")
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening relations file for writing");
        return;
    }

    // Call the recursive worker
    save_relations_recursive(tree->root, file);

    fclose(file);
    printf("Successfully saved relations data to %s.\n", filename);
}