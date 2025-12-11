# Social Network Simulator

A command-line social network application in C demonstrating fundamental data structures: Binary Search Trees, Linked Lists, and Stacks.

## 📋 Overview

This project simulates a social network with user profiles, bidirectional friendships, unidirectional subscriptions (followers), post publishing, and a chronological timeline aggregating content from friends and followers.

## ✨ Features

### User Management
- Create new users with unique IDs
- Search users by ID 
- Delete user accounts
- View all registered users

### Social Connections
- **Friendships**: Bidirectional relationships (both users are friends)
- **Subscriptions**: Unidirectional following (followers see your posts)
- Add/remove friends
- Subscribe/unsubscribe to users

### Content & Timeline
- Publish posts (text messages with timestamps)
- View personal posts history
- Delete most recent post
- **Smart Timeline**: Aggregates and sorts posts from:
  - Your own posts
  - All friends' latest posts
  - All followers' latest posts
  - Ordered by timestamp (newest first)

### Data Persistence
- Save/load users to binary file (`data/users.bin`)
- Save/load relationships to text file (`data/relations.txt`)
- All data persists between sessions


## 📁 Project Structure

```
Social_Network_Project_C/
├── src/
│   ├── main.c                  # Main menu and application loop
│   ├── abr_management.c        # BST operations (insert, search, delete)
│   ├── relations_ll.c          # Linked list operations (friends/followers)
│   ├── messages_stack.c        # Stack operations (posts)
│   ├── affichage.c             # UI and display functions
│   └── Data_persistence.c      # Save/load functions
├── include/
│   ├── structures.h            # All data structure definitions
│   ├── abr_management.h        # BST function declarations
│   ├── relations_ll.h          # Linked list function declarations
│   ├── messages_stack.h        # Stack function declarations
│   ├── affichage.h             # UI function declarations
│   └── Data_persistence.h      # Persistence function declarations
└── data/
    ├── users.bin               # Binary user data (auto-created)
    └── relations.txt           # Text relations data (auto-created)
```

## 🚀 Build & Run

### Compile

```bash
gcc -Wall -Wextra -g -I./include \
    src/abr_management.c \
    src/affichage.c \
    src/Data_persistence.c \
    src/main.c \
    src/messages_stack.c \
    src/relations_ll.c \
    -o social_network
```

### Run

```bash
./social_network
```

### Clean Build

```bash
rm -f social_network
```

## 🎮 Usage Example

1. **Start the program**: `./social_network`
2. **Create users**: Option 2 from main menu
3. **Login**: Option 1 with your user ID
4. **Add friends**: Option 7 from user menu
5. **Publish posts**: Option 1 from user menu
6. **View timeline**: Option 4 to see aggregated posts
7. **Exit and save**: Option 6 from main menu

## 📝 Data File Formats

### users.bin (Binary)
- User ID (int)
- User name (char[50])
- Post count (int)
- Posts data (id, content, timestamp)

### relations.txt (Text)
```
F 1 2    # Friendship between user 1 and 2
S 3 1    # User 3 subscribes to user 1
```

## 🔧 Functions Implemented

### BST Management (`abr_management.c`)
- `InsertUser()` - Add new user
- `searchUser()` - Find user by ID
- `deleteUser()` - Remove user and cleanup
- `get_max_node()` - Find maximum node
- `delete_max()` - Delete maximum node

### Relationships (`relations_ll.c`)
- `ajouterAmi()` - Create bidirectional friendship
- `sAbonner()` - Create subscription
- `supprimerRelation()` - Remove relationship
- `estEnRelation()` - Check if relation exists

### Posts (`messages_stack.c`)
- `empiler()` - Push new post
- `depiler()` - Pop most recent post
- `consulter()` - Peek at top post
- `afficherTousLesPosts()` - Display all posts

### Timeline (`affichage.c`)
- `generate_timeline()` - Aggregate and sort posts from friends/followers
- `display_friendships()` - Show friend list
- `display_subscriptions()` - Show follower list

## 💾 Memory Management

All dynamic memory allocations are properly freed:
- User nodes in BST
- Linked list nodes (friends/followers)
- Post stack nodes
- Timeline temporary array

## ⚙️ Compiler Flags

- `-Wall -Wextra`: Enable all warnings
- `-g`: Include debugging symbols
- `-I./include`: Specify include directory
          
└── README.md             # Project documentation