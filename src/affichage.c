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

