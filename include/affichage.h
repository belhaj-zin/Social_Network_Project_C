#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include "structures.h"

// Function declarations for user interface operations

// - Generate and display user's timeline
void generate_timeline(int user_id);

// - Display user's friends list
void display_friendships(int user_id);

// - Display user's followers/subscriptions
void display_subscriptions(int user_id);

#endif // USER_INTERFACE_H
