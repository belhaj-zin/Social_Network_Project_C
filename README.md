# Social Network Simulator (C Programming language)
### Using BST (Binary Search Tree), Linked Lists, and Stacks for Core Management

This application is a command-line console simulator designed to model the fundamental data structures and logic of a simplified social networking platform. It provides a robust demonstration of how relationships (Friends, Subscriptions) and content distribution (Timeline) are managed using classic data structures.

## ✨ Features

The application supports the following core functionalities:

* **User Management (ABR):** Efficient insertion, searching, and deletion of user profiles based on a unique Integer ID.
* **Relationship Management (Linked Lists):**
    * **Friendship:** Bidirectional relationship management (mutual acceptance).
    * **Subscription:** Unidirectional following model (follower sees posts of the followed).
* **Content Distribution (Stack & Sort):**
    * Publication history managed using a **Stack (LIFO)** for each user.
    * **Timeline Generation:** Dynamic creation of the "fil d'actualité" by merging and sorting the latest posts from all Friends and Subscriptions by timestamp.
* **Data Persistence:**
    * Saving and loading the complete ABR structure to a **binary file** (`users.bin`).
    * Saving and loading relationships to a **structured text file** (`relations.txt`).


## 🏗️ Data Structures & Architecture
##### Why using these Data structures ?

| **User Directory** | **Binary Search Tree (ABR)** | Provides $O(\log n)$ efficiency for searching, inserting, and deleting users based on the unique User ID. |

| **Friends/Subscriptions** | **Singly Linked Lists** | Allows flexible addition/removal of relations without predefining a maximum capacity. Optimal for dynamic, variable-length relationship sets. |

| **User Publications** | **Stack (LIFO)** | Ensures the most recent post is always easily accessible (Top of Stack) for quick timeline generation. |

| **Timeline** | **Temporary Sorted Array/List** | The Timeline is built dynamically by fetching data from various Stacks and applying a sorting algorithm to display chronologically. |

* **File Structure:** The project adheres to standard C practices, separating definitions (`.h` in `include/`) from implementations (`.c` in `src/`). represented below -->

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
├── Makefile             
└── README.md             # Project documentation