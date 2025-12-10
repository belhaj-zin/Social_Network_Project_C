#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/affichage.h"
#include "../include/structures.h"
#include "../include/abr_management.h"
#include "../include/relations_ll.h"
#include "../include/messages_stack.h"



void add_separator() {
    printf("╠════════════════════════════════════════════╣\n");
}

// Helper function to display all users (in-order traversal)
void display_all_users_helper(node* tree) {
    if (tree == NULL) return;
    
    display_all_users_helper(tree->left);
    printf("  ID: %-5d nom: %s\n",
           tree->id,tree->name);
    display_all_users_helper(tree->right);
}

void display_all_users(BST *users_tree) {
    printf("\n╔════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                       LISTE DE TOUS LES UTILISATEURS                   ║\n");
    printf("╚════════════════════════════════════════════════════════════════════════╝\n\n");
    
    if (users_tree == NULL || users_tree->root == NULL) {
        printf("Aucun utilisateur dans le système.\n");
        return;
    }
    
    display_all_users_helper(users_tree->root);
    printf("\n");
}


// Comparison function for qsort (descending by time - newest first)
int compare_posts_by_time(const void* a, const void* b) {
    timeline_post* post_a = (timeline_post*)a;
    timeline_post* post_b = (timeline_post*)b;
    
    if (post_a->timestamp > post_b->timestamp) return -1;
    if (post_a->timestamp < post_b->timestamp) return 1;
    return 0;
}

// ============== GENERATE TIMELINE ==============
void generate_timeline(BST *users_tree, int user_id) {
    node* current_user = searchUser(users_tree, user_id);
    
    if (current_user == NULL) {
        printf("❌ Erreur: Utilisateur non trouvé!\n");
        return;
    }
    
    printf("\n");
    add_separator();
    printf("║         MON TIMELINE (FIL D'ACTUALITE)        ║\n");
    add_separator();
    printf("\n");
    
    // Allocate array for timeline posts
    int max_posts = 100;  // Maximum posts to display
    timeline_post* timeline = (timeline_post*)malloc(sizeof(timeline_post) * max_posts);
    int post_count = 0;
    
    // 1. Add most recent post from current user
    if (current_user->posts != NULL && post_count < max_posts) {
        timeline[post_count].user_id = current_user->id;
        strncpy(timeline[post_count].user_name, current_user->name, 49);
        timeline[post_count].user_name[49] = '\0';
        timeline[post_count].post_id = current_user->posts->id_post;
        strncpy(timeline[post_count].content, current_user->posts->content, 255);
        timeline[post_count].content[255] = '\0';
        timeline[post_count].timestamp = current_user->posts->timestamp;
        post_count++;
    }
    
    // 2. Add one post from each friend
    LLnode* friend = current_user->friends;
    while (friend != NULL && post_count < max_posts) {
        node* friend_user = searchUser(users_tree, friend->id);
        if (friend_user != NULL && friend_user->posts != NULL) {
            timeline[post_count].user_id = friend_user->id;
            strncpy(timeline[post_count].user_name, friend_user->name, 49);
            timeline[post_count].user_name[49] = '\0';
            timeline[post_count].post_id = friend_user->posts->id_post;
            strncpy(timeline[post_count].content, friend_user->posts->content, 255);
            timeline[post_count].content[255] = '\0';
            timeline[post_count].timestamp = friend_user->posts->timestamp;
            post_count++;
        }
        friend = friend->next;
    }
    
    // 3. Add one post from each follower
    LLnode* follower = current_user->followers;
    while (follower != NULL && post_count < max_posts) {
        node* follower_user = searchUser(users_tree, follower->id);
        if (follower_user != NULL && follower_user->posts != NULL) {
            timeline[post_count].user_id = follower_user->id;
            strncpy(timeline[post_count].user_name, follower_user->name, 49);
            timeline[post_count].user_name[49] = '\0';
            timeline[post_count].post_id = follower_user->posts->id_post;
            strncpy(timeline[post_count].content, follower_user->posts->content, 255);
            timeline[post_count].content[255] = '\0';
            timeline[post_count].timestamp = follower_user->posts->timestamp;
            post_count++;
        }
        follower = follower->next;
    }
    
    // 4. Sort posts by timestamp (newest first)
    if (post_count > 0) {
        qsort(timeline, post_count, sizeof(timeline_post), compare_posts_by_time);
        
        // 5. Display sorted timeline
        for (int i = 0; i < post_count; i++) {
            printf("┌─────────────────────────────────────────────┐\n");
            printf("│ Post de: %s (ID: %d)\n", timeline[i].user_name, timeline[i].user_id);
            printf("│ Date: %s", ctime(&timeline[i].timestamp));
            printf("├─────────────────────────────────────────────┤\n");
            printf("│ %s\n", timeline[i].content);
            printf("└─────────────────────────────────────────────┘\n\n");
        }
    } else {
        printf("Aucun post disponible dans votre timeline.\n");
    }
    
    free(timeline);
}
// ============== DISPLAY FRIENDSHIPS ==============
void display_friendships(BST *users_tree,int user_id) {
    node* current_user = searchUser(users_tree, user_id);
    LLnode* friend = NULL;
    int count = 0;
    
    if (current_user == NULL) {
        printf("❌ Erreur: Utilisateur non trouvé!\n");
        return;
    }
    
    printf("\n");
    add_separator();
    printf("║         MES AMIS (FRIENDSHIPS)                ║\n");
    add_separator();
    
    friend = current_user->friends;
    
    if (friend == NULL) {
        printf("\nVous n'avez pas encore d'amis.\n");
        return;
    }
    
    printf("\n");
    while (friend != NULL) {
        count++;
        node* friend_user = searchUser(users_tree, friend->id);
        
        if (friend_user != NULL) {
            printf("%d. ID: %d | Nom: %s\n", count, friend->id, friend_user->name);
        } else {
            printf("%d. ID: %d | Nom: [Utilisateur supprimé]\n", count, friend->id);
        }
        
        friend = friend->next;
    }
    
    printf("\nTotal d'amis: %d\n", count);
}

// ============== DISPLAY SUBSCRIPTIONS ==============
void display_subscriptions(BST *users_tree,int user_id) {
    node* current_user = searchUser(users_tree, user_id);
    LLnode* follower = NULL;
    int count = 0;
    
    if (current_user == NULL) {
        printf("❌ Erreur: Utilisateur non trouvé!\n");
        return;
    }
    
    printf("\n");
    add_separator();
    printf("║         MES ABONNES (SUBSCRIPTIONS)           ║\n");
    add_separator();
    
    follower = current_user->followers;
    
    if (follower == NULL) {
        printf("\nVous n'avez pas d'abonnés pour le moment.\n");
        return;
    }
    
    printf("\n");
    while (follower != NULL) {
        count++;
        node* follower_user = searchUser(users_tree, follower->id);
        
        if (follower_user != NULL) {
            printf("%d. ID: %d | Nom: %s\n", count, follower->id, follower_user->name);
        } else {
            printf("%d. ID: %d | Nom: [Utilisateur supprimé]\n", count, follower->id);
        }
        
        follower = follower->next;
    }
    
    printf("\nTotal d'abonnés: %d\n", count);
}


// TODO: Implement main menu and user interface
    void main_menu(BST *users_tree,int user_id) {
    int choice;
    node* current_user = searchUser(users_tree, user_id);
    
    if (current_user == NULL) {
        printf("Erreur: Utilisateur non trouvé!\n");
        return;
    }
    
    while (1) {
        printf("\n");
        add_separator();
        printf("║         MENU PRINCIPAL - %s                ║\n", current_user->name);
        add_separator();
        printf("║  1. Publier un Post                         ║\n");
        printf("║  2. Voir Mes Posts                          ║\n");
        printf("║  3. Supprimer Mon Dernier Post              ║\n");
        printf("║  4. Générer Timeline (Fil d'Actualité)      ║\n");
        printf("║  5. Voir Mes Amis                           ║\n");
        printf("║  6. Voir Mes Abonnés                        ║\n");
        printf("║  7. Ajouter un Ami                          ║\n");
        printf("║  8. S'abonner à un Utilisateur              ║\n");
        printf("║  9. Supprimer une Amitié                    ║\n");
        printf("║  10. Supprimer un Abonné                    ║\n");
        printf("║  11. Rechercher un Utilisateur              ║\n");
        printf("║  12. Supprimer Mon Compte                   ║\n");
        printf("║  13. Se Déconnecter                         ║\n");
        add_separator();
        printf("Choisissez une option (1-13): ");
        scanf("%d", &choice);
        getchar(); // Clear newline
        
        printf("\n");
        
        switch (choice) {
            case 1: {
                // Publish a post
                char content[256];
                printf("Entrez votre message (max 255 caractères): ");
                fgets(content, 256, stdin);
                content[strcspn(content, "\n")] = '\0';
                
                int post_id = count_posts(current_user->posts) + 1;
                current_user->posts = empiler(current_user->posts, post_id, content);
                printf("✓ Post publié avec succès!\n");
                break;
            }
            
            case 2: {
                // View all my posts
                printf("\n=== MES POSTS ===\n");
                if (current_user->posts == NULL) {
                    printf("Vous n'avez pas encore publié de posts.\n");
                } else {
                    afficherTousLesPosts(current_user->posts);
                }
                break;
            }
            
            case 3: {
                // Delete last post
                if (current_user->posts == NULL) {
                    printf("❌ Vous n'avez aucun post à supprimer.\n");
                } else {
                    current_user->posts = depiler(current_user->posts);
                    printf("✓ Dernier post supprimé avec succès!\n");
                }
                break;
            }
            
            case 4:
                generate_timeline(users_tree,user_id);
                break;
                
            case 5:
                display_friendships(users_tree,user_id);
                break;
                
            case 6:
                display_subscriptions(users_tree,user_id);
                break;
                
            case 7: {
                printf("Entrez l'ID de l'ami à ajouter: ");
                int friend_id;
                scanf("%d", &friend_id);
                getchar();
                ajouterAmi(users_tree, user_id, friend_id);
                break;
            }
            
            case 8: {
                printf("Entrez l'ID de l'utilisateur à suivre: ");
                int subscriber_id;
                scanf("%d", &subscriber_id);
                getchar();
                sAbonner(users_tree, user_id, subscriber_id);
                break;
            }
            
            case 9: {
                printf("Entrez l'ID de l'ami à supprimer: ");
                int ID_Cible;
                scanf("%d", &ID_Cible);
                getchar();
                current_user->friends = supprimerRelation(current_user->friends, ID_Cible);
                // Also remove from the other user's friend list (bidirectional)
                node* other_user = searchUser(users_tree, ID_Cible);
                if (other_user != NULL) {
                    other_user->friends = supprimerRelation(other_user->friends, user_id);
                }
                break;
            }
            
            case 10: {
                printf("Entrez l'ID de l'abonné à supprimer: ");
                int follower_id;
                scanf("%d", &follower_id);
                getchar();
                current_user->followers = supprimerRelation(current_user->followers, follower_id);
                break;
            }
            
            case 11: {
                printf("Entrez l'ID de l'utilisateur à rechercher: ");
                int search_id;
                scanf("%d", &search_id);
                getchar();
                
                node* found_user = searchUser(users_tree, search_id);
                if (found_user != NULL) {
                    printf("\n✓ Utilisateur trouvé!\n");
                    printf("ID: %d\n", found_user->id);
                    printf("Nom: %s\n", found_user->name);
                    printf("Nombre d'amis: %d\n", count_ll_nodes(found_user->friends));
                    printf("Nombre d'abonnés: %d\n", count_ll_nodes(found_user->followers));
                    printf("Nombre de posts: %d\n", count_posts(found_user->posts));
                } else {
                    printf("❌ Utilisateur avec ID %d non trouvé.\n", search_id);
                }
                break;
            }
            
            case 12: {
                printf("\n⚠️  ATTENTION: Cette action est irréversible!\n");
                printf("Voulez-vous vraiment supprimer votre compte? (o/n): ");
                char confirm;
                scanf(" %c", &confirm);
                getchar();
                
                if (confirm == 'o' || confirm == 'O') {
                    deleteUser(users_tree, user_id);
                    printf("✓ Compte supprimé. Au revoir!\n");
                    return;
                } else {
                    printf("Suppression annulée.\n");
                }
                break;
            }
            
            case 13:
                printf("Déconnexion réussie. À bientôt, %s!\n", current_user->name);
                return;
                
            default:
                printf("❌ Erreur: Option invalide. Veuillez choisir entre 1 et 13.\n");
        }
        
        printf("\nAppuyez sur Entrée pour continuer...");
        getchar();
    }
}

void login_menu(BST *users_tree) {
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
        user = searchUser(users_tree, user_id);
        
        if (user == NULL) {
            printf("\n Erreur: Utilisateur avec ID %d non trouvé!\n", user_id);
            printf("Appuyez sur Entrée pour réessayer...");
            getchar();
            return;
        }
        
        printf("\n✓ Connexion réussie!\n");
        printf("Bienvenue, %s!\n", user->name);
        printf("Appuyez sur Entrée pour continuer...");
        getchar();
        
        // Show main menu for this user
        main_menu(users_tree, user_id);
}
