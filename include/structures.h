//Define the linked list that will be inside the node as the friend and follower lists 
typedef struct LLnode {
    int id;
    struct LLnode* next;
} LLnode;


//Define the stack structure that will hold the posts
typedef struct {
    int id_post;
    char content[256];
    long timestamp; // the time the post was created
    struct post* previous;
}post ;

//Define the node structure that will hold the user information
typedef struct node {
    //user information
    int id;
    char name[50];
    //binary search tree pointers
    struct node* left;
    struct node* right;
    //linked lists for friends and followers
    LLnode* friends; //linked list of friends
    LLnode* followers; //linked list of followers
    //pointer to the first post
    post* posts; //pointer to the stack of posts
} node;

//Define the binary search tree structure that will hold all the users
typedef struct {
    node* root; //root of the binary search tree
} BST;

// NOTE !! : we didn't create a structure for the timeline because 
// it is only generated when the user wants to see it, 
// so we can create it as a local variable in the function that generates it.
// no need to store it permanently.