#ifndef ABR_MANAGEMENT_H
#define ABR_MANAGEMENT_H

#include "structures.h"

// Binary Search Tree function declarations

//! Add function declarations :
//? - Insert user into BST :

node* InsertUser_to_node(node* tree,int id ,char *name);
void InsertUser(BST *tree, int id, char *name);

//? - Search user in BST :

node* searchUser_node(node *tree,int searched_id);
node* searchUser(BST *tree, int searched_id);

//? - Delete user from BST :

//? - Traverse BST (in-order, pre-order, post-order) :

#endif // ABR_MANAGEMENT_H
