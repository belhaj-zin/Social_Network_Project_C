#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H
#include <relations_ll.h>
#include "structures.h"

// Helper function for menu display
void add_separator();

// Core UI functions
void generate_timeline(BST *users_tree,int user_id);
void display_friendships(BST *users_tree,int user_id);
void display_subscriptions(BST *users_tree,int user_id);
void display_all_users(BST *users_tree);

// Main menu function
void main_menu(BST *users_tree, int user_id);
void login_menu(BST *users_tree);

#endif // USER_INTERFACE_H
