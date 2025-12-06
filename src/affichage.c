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
        printf("║  7. Se Déconnecter                          ║\n");
        add_separator();
        printf("Choisissez une option (1-7): ");
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
                printf("Entrez l'ID de la relation à supprimer:");
                int ID_Cible
                scanf("%d", &ID_Cible);
                getchar(); // Clear newline
                LLnode* supprimerRelation(LLnode* liste, int ID_Cible)
                break;
            case 7:
                printf("Déconnexion réussie. À bientôt, %s!\n", current_user->name);
                return;
            default:
                printf("❌ Erreur: Option invalide. Veuillez choisir entre 1 et 7.\n");
        }
        
        printf("\nAppuyez sur Entrée pour continuer...");
        getchar();
    }
}
