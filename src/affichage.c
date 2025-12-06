void add_separator() {
    printf("╠════════════════════════════════════════════╣\n");
}


// ============== GENERATE TIMELINE ==============
void generate_timeline(int user_id) {
    node* current_user = searchUser(&users_tree, user_id);
    
    if (current_user == NULL) {
        printf("❌ Erreur: Utilisateur non trouvé!\n");
        return;
    }
    
    printf("\n");
    add_separator();
    printf("║         MON TIMELINE (FIL D'ACTUALITE)        ║\n");
    add_separator();
    
    if (current_user->posts == NULL) {
        printf("Aucun post trouvé. Soyez le premier à publier!\n");
    } else {
        printf("\n--- Mes Publications ---\n\n");
        afficherTousLesPosts(current_user->posts);
    }
}
//============= DISPLAY FRIENDSHIPS ==============
void display_friendships(int user_id) {
    node* current_user = searchUser(&users_tree, user_id);
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
        node* friend_user = searchUser(&users_tree, friend->id);
        
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
void display_subscriptions(int user_id) {
    node* current_user = searchUser(&users_tree, user_id);
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
        node* follower_user = searchUser(&users_tree, follower->id);
        
        if (follower_user != NULL) {
            printf("%d. ID: %d | Nom: %s\n", count, follower->id, follower_user->name);
        } else {
            printf("%d. ID: %d | Nom: [Utilisateur supprimé]\n", count, follower->id);
        }
        
        follower = follower->next;
    }
    
    printf("\nTotal d'abonnés: %d\n", count);
}
// Internal helper: remove an id from a singly linked list (by reference)
static void remove_id_from_list(LLnode **head_ref, int id) {
    LLnode *current = *head_ref;
    LLnode *previous = NULL;

    while (current != NULL) {
        if (current->id == id) {
            if (previous == NULL) {
                // Remove first element
                *head_ref = current->next;
            } else {
                previous->next = current->next;
            }
            free(current);
            return;  // Done
        }
        previous = current;
        current = current->next;
    }
    // If not found, list stays unchanged
}
//to help remove friendship 
void remove_friend(node *user1, node *user2) {
    if (user1 == NULL || user2 == NULL) return;

    remove_id_from_list(&user1->friends, user2->id);
    remove_id_from_list(&user2->friends, user1->id);

    printf("Friendship removed between %s (ID %d) and %s (ID %d).\n",
           user1->name, user1->id,
           user2->name, user2->id);
}
//to help remove subscription
void remove_subscription(node *follower, node *followed_user) {
    if (follower == NULL || followed_user == NULL) return;

    remove_id_from_list(&followed_user->followers, follower->id);

    printf("%s (ID %d) no longer follows %s (ID %d).\n",
           follower->name, follower->id,
           followed_user->name, followed_user->id);
}
//to remove friendship 
void remove_friendship_ui(int user_id) {
    int other_id;
    node *user1 = searchUser(&users_tree, user_id);
    node *user2;

    if (user1 == NULL) {
        printf("Error: user not found.\n");
        return;
    }

    printf("Enter the ID of the friend to remove: ");
    scanf("%d", &other_id);
    getchar();

    if (other_id == user_id) {
        printf("You cannot remove yourself.\n");
        return;
    }

    user2 = searchUser(&users_tree, other_id);
    if (user2 == NULL) {
        printf("Error: user with ID %d not found.\n", other_id);
        return;
    }

    remove_friend(user1, user2);
}

//to remove subscription
void remove_subscription_ui(int user_id) {
    int other_id;
    node *follower = searchUser(&users_tree, user_id);
    node *followed;

    if (follower == NULL) {
        printf("Error: user not found.\n");
        return;
    }

    printf("Enter the ID of the user you want to unfollow: ");
    scanf("%d", &other_id);
    getchar();

    if (other_id == user_id) {
        printf("You cannot unfollow yourself.\n");
        return;
    }

    followed = searchUser(&users_tree, other_id);
    if (followed == NULL) {
        printf("Error: user with ID %d not found.\n", other_id);
        return;
    }

  
    remove_subscription(follower, followed);
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
        printf("║  6. supprimer une amitié                   ║\n");
        printf("║  7. supprimer un Abonnement                   ║\n");
        printf("║  8. Se Déconnecter                          ║\n");
        add_separator();
        printf("Choisissez une option (1-8): ");
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
                remove_friendship_ui(user_id);
                break;
            case 7:
                remove_subscription_ui(user_id);
                break;
            case 8:
                printf("Déconnexion réussie. À bientôt, %s!\n", current_user->name);
                return;
            default:
                printf("❌ Erreur: Option invalide. Veuillez choisir entre 1 et 8.\n");
        }
        
        printf("\nAppuyez sur Entrée pour continuer...");
        getchar();
    }
}
