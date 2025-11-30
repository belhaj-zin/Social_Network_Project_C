#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/abr_management.h"

// Binary Search Tree functions implementation

// TODO: Implement Insert function
node* InsertUser_to_node(node* tree,int id ,char *name) {
    if (tree == NULL){  // if there is no user yet
        node* newNode = (node*)malloc(sizeof(node)); // allocate memory for the new user
        // initialize the new user
        newNode -> id = id;
        strncpy(newNode->name, name, 50);
        newNode -> left = NULL;
        newNode -> right = NULL;
        newNode -> friends = NULL;
        newNode -> followers = NULL;
        newNode -> posts = NULL;

        return newNode;
    }
    // otherwise, we need to find the correct position to insert the new user
    if (id < tree -> id) {
        // insert in the left subtree
        tree->left=InsertUser_to_node(tree->left, id, name);
    } else if (id > tree-> id) {
        // insert in the right subtree
        tree->right=InsertUser_to_node(tree->right, id, name);
    } else {
        printf("User with ID %d already exists. Insertion failed.\n", id);
    }
    return tree ;
}

// Wrapper function to insert a user into the BST
void InsertUser(BST *tree, int id, char *name) {
    if (tree == NULL){ //check if the BST structure is NULL
        fprintf(stderr, "Error: BST structure is NULL.\n");
        return;
    }
    tree->root = InsertUser_to_node(tree->root, id, name);
}

// TODO: Implement Search function
node* searchUser_node(node *tree,int searched_id){
    if (tree == NULL){ // return error if the user is not found
        fprintf(stderr, "User with ID %d not found.\n", searched_id);
        return NULL; //! <--- CRITICAL FIX: Must return NULL here!
    }
    if (tree -> id == searched_id){
        return tree ; // user found
    }
    if (searched_id < tree -> id){
        return searchUser_node(tree -> left , searched_id);
    }
    else{
        return searchUser_node(tree -> right , searched_id);
    }
}

// wrapper function to search a user in the BST
node* searchUser(BST *tree, int searched_id){
    if (tree == NULL || tree->root == NULL){ //check if the BST structure is NULL
        fprintf(stderr, "Error: BST structure is NULL.\n");
        return NULL;
    }
    return searchUser_node(tree -> root , searched_id);
}

// TODO: Implement Delete function
// FIRST : we need a function to give me the id of the maximum node

node* get_max_node(node* tree) {
    if (tree == NULL) {
        fprintf(stderr, "Error: Tree is NULL.\n");
        return NULL; // Indicate error
    }
    if (tree->right == NULL) { // if the node doesn't have a right child, it's the maximum
        return tree;
    }
    return get_max_node(tree->right); // recursively go to the right subtree
}

// SECOND : we need a function to delete the maximum node
node* delete_max(node* tree){
    if (tree == NULL) {
        fprintf(stderr, "Error: Tree is NULL.\n");
        return NULL;
    }
    if (tree->right == NULL) { // if there is no right child, this is the max node
        node* left_subtree = tree->left; // store the left subtree
        free(tree); // free the max node
        return left_subtree; // return the left subtree to be connected to the parent
    }
    tree->right = delete_max(tree->right); // recursively go to the right subtree
    return tree; // return the unchanged tree pointer
}

// Now we can implement the delete function
node* deleteUser_node(node* tree, int deleted_id) {
    if (tree == NULL) {
        fprintf(stderr, "User with ID %d not found. Deletion failed.\n", deleted_id);
        return NULL;
    }
    if (deleted_id < tree->id) {
        tree->left = deleteUser_node(tree->left, deleted_id);
    } else if (deleted_id > tree->id) {
        tree->right = deleteUser_node(tree->right, deleted_id);
    } else {
        // Node to be deleted found
        if (tree->left == NULL) {
            node* right_subtree = tree->right;
            free(tree);
            return right_subtree;
        } else if (tree->right == NULL) {
            node* left_subtree = tree->left;
            free(tree);
            return left_subtree;
        } else {
            // Node with two children
            node* max_node = get_max_node(tree->left);
            // transfer all of max_node's data to tree
            tree->id = max_node->id;
            strncpy(tree->name, max_node->name, 50);
            tree->friends = max_node->friends; 
            tree->followers = max_node->followers;  
            tree->posts = max_node->posts;  
            // Delete the max node
            tree->left = delete_max(tree->left); 
        }
    }
    return tree;
}