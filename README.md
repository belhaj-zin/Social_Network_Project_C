# Social Network Project in C

## Project Description
This is a social network application implemented in C, featuring user management, relationships, and messaging functionality using fundamental data structures.

## Project Structure

```
SocialNetwork_C/
├── src/                  # Contains all function implementations (.c files)
│   ├── main.c            # The main application loop (User Interface logic)
│   ├── abr_management.c  # Binary Search Tree functions (Insert, Search, Delete)
│   ├── relations_ll.c    # Linked List functions for relationships (Add, Remove)
│   └── messages_stack.c  # Stack functions for messages (Push, Pop)
│
├── include/              # Contains all structure definitions and function declarations (.h files)
│   ├── structures.h      # All data structures (User, LLNode, Message...)
│   ├── abr_management.h  # Declarations for 'abr_management.c'
│   ├── relations_ll.h    # Declarations for 'relations_ll.c'
│   └── messages_stack.h  # Declarations for 'messages_stack.c'
│
├── data/                 # To store persistence files (Task 4)
│   └── (empty files: users.bin, relations.txt)
│
├── Makefile              # To simplify compilation
└── README.md             # Project documentation
```

## Data Structures Used

### 1. Binary Search Tree (BST)
- **Purpose**: Manage users efficiently with O(log n) search time
- **Implementation**: `abr_management.c`

### 2. Linked List
- **Purpose**: Store and manage relationships between users
- **Implementation**: `relations_ll.c`

### 3. Stack
- **Purpose**: Handle messages (LIFO - Last In First Out)
- **Implementation**: `messages_stack.c`

## Compilation

### Using Makefile (Recommended)
```bash
# Build the project
make

# Run the application
make run

# Clean build files
make clean

# Rebuild everything
make rebuild
```

### Manual Compilation
```bash
gcc -Wall -Wextra -g -I./include src/*.c -o social_network
./social_network
```

## Features

- [ ] User management (Create, Read, Update, Delete)
- [ ] Binary Search Tree for efficient user lookup
- [ ] Relationship management using Linked Lists
- [ ] Message system using Stack data structure
- [ ] Data persistence (save/load from files)

## Tasks

### Task 1: Data Structures
- Define all necessary structures in `structures.h`

### Task 2: Core Functions
- Implement BST operations
- Implement Linked List operations
- Implement Stack operations

### Task 3: User Interface
- Create interactive menu in `main.c`
- Handle user input and actions

### Task 4: Data Persistence
- Save users to `data/users.bin`
- Save relationships to `data/relations.txt`
- Load data on application start

## Authors
- [Your Name Here]

## License
This project is for educational purposes.
