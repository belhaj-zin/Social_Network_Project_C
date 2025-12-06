#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H
#include <relations_ll.h>
#include "structures.h"

// Helper function for menu display
void add_separator();

// Core UI functions
void generate_timeline(int user_id);
void display_friendships(int user_id);
void display_subscriptions(int user_id);

// Main menu function
void main_menu(int user_id);

#endif // USER_INTERFACE_H
