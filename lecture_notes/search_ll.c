// the second argument is a pointer to a item of node data type.

bool search(int n, node *list)
{
    // define a local pointer variable of type node
    // that saves the list pointer. Note no derefrencing.

    // the arrow syntax is used for variables that hold
    // pointers to structs. It accesses the struct's
    // property and derefrences (follows ptr) at once

    node *ptr = list;
    while(ptr != NULL)
    {
        if (ptr->n == n)
        {
            return true;
        }
        ptr = ptr->next;
    }

    return false;
}

// Define a stack

typedef struct
{
    int numbers[CAPACITY];
    int size;
}
stack;

// Define a queue struct


typedef struct
{
    int front;
    int *numbers; // allocate more with malloc
    int size;
}
queue;

// Binary search tree node
// note that since this struct refers to itself within its definition
// you have to write the name 'node' twice.
// its necessary for the inner implementation detail.

typedef struct node;
{
    int n;
    struct node *left;
    struct node *right;
}
node;

// searching a binary search tree can be done effectively with recursion.

bool search(int n, node *tree) // accepts a pointer to the tree
{
    if (tree == NULL)
    {
        return false;
    }
    else if (n < tree->n) // dereference and access the field at once with the arrow operator.
    {                       // tree in this context refers to the current node. n is the actual number
        return search(n, tree->left); // this passes in the pointer to the left child
    }
    else if (n > tree->n)
    {
        return serch(n, tree->right);
    }
    else
    {
        return true;
    }
}

// struct for a huffman tree algorithm
typedef struct node
{
    char symbol;
    float frequency; // could also use an int and just conceptually consider it a percentage
    struct node *left;
    struct node *right;
}
node;