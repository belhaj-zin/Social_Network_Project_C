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
    // TODO: Implement main menu and user interface
    void main_menu(int user_id) {
    int choice;
    node* current_user = searchUser(&users_tree, user_id);
    
    if (current_user == NULL) {
        printf("Erreur: Utilisateur non trouvé!\n");
        return;
    }
    
    while (1) {
        printf("\n");
        add_separator();
        printf("║         MENU PRINCIPAL - %s                ║\n", current_user->name);
        add_separator();
        printf("║  1. Générer Timeline (Fil d'Actualité)      ║\n");
        printf("║  2. Voir mes Amis (Friendships)             ║\n");
        printf("║  3. Voir mes Abonnés (Subscriptions)        ║\n");
        printf("║  4. Ajouter un Ami                          ║\n");
        printf("║  5. Ajouter un Abonnement                   ║\n");
        printf("║  6. Se Déconnecter                          ║\n");
        add_separator();
        printf("Choisissez une option (1-6): ");
        scanf("%d", &choice);
        getchar(); // Clear newline
        
        printf("\n");
        
        switch (choice) {
            case 1:
                generate_timeline(user_id);
                break;
            case 2:
                display_friendships(user_id);
                break;
            case 3:
                display_subscriptions(user_id);
                break;
            case 4:
                printf("Entrez l'ID de l'ami à ajouter:");
                int friend_id;
                scanf("%d", &friend_id);
                getchar(); // Clear newline
                ajouterAmi(&users_tree, user_id, friend_id);
                break;
            case 5:
                printf("Entrez l'ID de l'abonné à ajouter:");
                int subscriber_id;
                scanf("%d", &subscriber_id);
                getchar(); // Clear newline
                sAbonner(&users_tree, user_id, subscriber_id);
                break;
            case 6:
                printf("Déconnexion réussie. À bientôt, %s!\n", current_user->name);
                return;
            default:
                printf("❌ Erreur: Option invalide. Veuillez choisir entre 1 et 6.\n");
        }
        
        printf("\nAppuyez sur Entrée pour continuer...");
        getchar();
    }
}

    
    return 0;
}
