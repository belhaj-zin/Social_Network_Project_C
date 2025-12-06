#include <stdio.h>
#include <stdlib.h>
#include "affichage.h"
#include "../include/structures.h"
#include "../include/abr_management.h"
#include "../include/relations_ll.h"
#include "../include/messages_stack.h"

BST users_tree = {NULL};

int main() {
    // The main application loop (User Interface logic)
    // ============== LOGIN MENU ==============
    void login_menu() {
        int user_id;
        node* user = NULL;
        
        printf("\n");
        add_separator();
        printf("║         BIENVENUE AU RESEAU SOCIAL            ║\n");
        add_separator();
        
        printf("\nEntrez votre ID utilisateur: ");
        scanf("%d", &user_id);
        getchar(); // Clear newline
        
        // Search for user in BST
        user = searchUser(&users_tree, user_id);
        
        if (user == NULL) {
            printf("\n❌ Erreur: Utilisateur avec ID %d non trouvé!\n", user_id);
            printf("Appuyez sur Entrée pour réessayer...");
            getchar();
            return;
        }
        
        printf("\n✓ Connexion réussie!\n");
        printf("Bienvenue, %s!\n", user->name);
        printf("Appuyez sur Entrée pour continuer...");
        getchar();
        
        // Show main menu for this user
        main_menu(user_id);


    }
    

    
    return 0;
}
