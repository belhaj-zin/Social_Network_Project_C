#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "affichage.h"
#include "../include/structures.h"
#include "../include/abr_management.h"
#include "../include/relations_ll.h"
#include "../include/messages_stack.h"
#include "../include/Data_persistence.h"

int main() {
    BST users_tree = {NULL};
    
    printf("╔════════════════════════════════════════════╗\n");
    printf("║   SOCIAL NETWORK SIMULATOR - C PROJECT     ║\n");
    printf("╚════════════════════════════════════════════╝\n\n");
    
    printf("Chargement des données...\n");
    load_users(&users_tree, "data/users.bin");
    printf("✓ Données chargées!\n\n");
    
    int choice;
    while (1) {
        printf("\n╔════════════════════════════════════════════╗\n");
        printf("║            MENU PRINCIPAL                  ║\n");
        printf("╠════════════════════════════════════════════╣\n");
        printf("║  1. Se Connecter                           ║\n");
        printf("║  2. Créer un Nouvel Utilisateur            ║\n");
        printf("║  3. Voir Tous les Utilisateurs             ║\n");
        printf("║  4. Rechercher un Utilisateur              ║\n");
        printf("║  5. Supprimer un Utilisateur               ║\n");
        printf("║  6. Quitter et Sauvegarder                 ║\n");
        printf("╚════════════════════════════════════════════╝\n");
        printf("\nChoix: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("❌ Entrée invalide.\n");
            while(getchar() != '\n');
            continue;
        }
        getchar();
        
        switch (choice) {
            case 1:
                login_menu(&users_tree);
                break;
                
            case 2: {
                int new_id;
                char new_name[50];
                
                printf("\n=== Création d'un Nouvel Utilisateur ===\n");
                printf("Entrez l'ID: ");
                scanf("%d", &new_id);
                getchar();
                
                if (searchUser(&users_tree, new_id) != NULL) {
                    printf("❌ Erreur: Un utilisateur avec cet ID existe déjà!\n");
                    break;
                }
                
                printf("Entrez le nom: ");
                fgets(new_name, 50, stdin);
                new_name[strcspn(new_name, "\n")] = '\0';
                
                InsertUser(&users_tree, new_id, new_name);
                printf("✓ Utilisateur créé avec succès!\n");
                break;
            }
            
            case 3:
                display_all_users(&users_tree);
                break;
                
            case 4: {
                int search_id;
                printf("\nRecherche d'Utilisateur\n");
                printf("Entrez l'ID à rechercher: ");
                scanf("%d", &search_id);
                getchar();
                
                node* found = searchUser(&users_tree, search_id);
                if (found != NULL) {
                    printf("\n✓ Utilisateur trouvé!\n");
                    printf("ID: %d\n", found->id);
                    printf("Nom: %s\n", found->name);
                    printf("Nombre d'amis: %d\n", count_ll_nodes(found->friends));
                    printf("Nombre d'abonnés: %d\n", count_ll_nodes(found->followers));
                    printf("Nombre de posts: %d\n", count_posts(found->posts));
                } else {
                    printf("❌ Utilisateur non trouvé.\n");
                }
                break;
            }
            
            case 5: {
                int delete_id;
                printf("\nSuppression d'Utilisateur\n");
                printf("Entrez l'ID à supprimer: ");
                scanf("%d", &delete_id);
                getchar();
                
                if (searchUser(&users_tree, delete_id) == NULL) {
                    printf("❌ Utilisateur non trouvé.\n");
                    break;
                }
                
                printf("⚠️  Confirmer la suppression? (o/n): ");
                char confirm;
                scanf(" %c", &confirm);
                getchar();
                
                if (confirm == 'o' || confirm == 'O') {
                    deleteUser(&users_tree, delete_id);
                    printf("✓ Utilisateur supprimé.\n");
                } else {
                    printf("Suppression annulée.\n");
                }
                break;
            }
            
            case 6:
                printf("\nSauvegarde des données...\n");
                save_users(&users_tree, "data/users.bin");
                save_relations_to_file(&users_tree, "data/relations.txt");
                printf("✓ Données sauvegardées!\n");
                printf("Au revoir! 👋\n\n");
                return 0;
                
            default:
                printf("❌ Choix invalide.\n");
        }
    }
    
    return 0;
}
