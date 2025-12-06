#ifndef ABR_MANAGEMENT_H
#define ABR_MANAGEMENT_H

#include "structures.h"

// Binary Search Tree function declarations

//! Add function declarations :
// - Insert user into BST :

node* InsertUser_to_node(node* tree,int id ,char *name);
void InsertUser(BST *tree, int id, char *name);

// - Search user in BST :

node* searchUser_node(node *tree,int searched_id);
node* searchUser(BST *tree, int searched_id);

// - Delete user from BST :

node* deleteUser_node(node* tree, int deleted_id);
void deleteUser(BST *tree, int deleted_id);

// - Get maximum node in BST :

node* get_max_node(node* tree);

// - Delete maximum node in BST :

node* delete_max(node* tree);

// - Free linked list :

void free_linked_list(LLnode* head);

// - Free posts stack :

void free_posts_stack(post* top);   


#endif // ABR_MANAGEMENT_H
