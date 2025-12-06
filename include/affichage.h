#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include "structures.h"

// Helper function for menu display
void add_separator();

// Core UI functions
void generate_timeline(int user_id);
void display_friendships(int user_id);
void display_subscriptions(int user_id);

// Relationship removal functions (from relations_ll.c)
void remove_friend(node *user1, node *user2);
void remove_subscription(node *follower, node *followed_user);

// UI wrappers for relationship removal
void remove_friendship_ui(int user_id);
void remove_subscription_ui(int user_id);

// Main menu function
void main_menu(int user_id);

#endif // USER_INTERFACE_H
