
#ifndef DATA_PERSISTENCE_H
#define DATA_PERSISTENCE_H

#include "structures.h"

// Users persistence (binary file)
void save_users(BST* tree, const char* filename);
void load_users(BST* tree, const char* filename);

// Relations persistence (text file)
void save_relations_to_file(BST* tree, const char* filename);
void load_relations_from_file(BST* tree, const char* filename);

#endif // DATA_PERSISTENCE_H
