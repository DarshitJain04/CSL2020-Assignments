#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Creating a boolean datatype using enum */
enum check
{
    empty = true
};

/* Node structure for BST */
typedef struct NODE
{
    int data;
    struct NODE *left;
    struct NODE *right;
} node;

node *root = NULL;
int total_nodes = 0, internal_nodes = 0;

/* Stack will be used for tree traversal */
typedef struct STACK
{
    node *bst_node;
    struct STACK *next;
} stack;

stack *traversal_stack = NULL;

/* Helper function that checks if the stack is empty or not */
bool isempty(stack *top)
{
    enum check temp;
    temp = empty;
    if (top == NULL)
    {
        return temp;
    }
    else
    {
        return !temp;
    }
}

/* Function to push elements to the stack */
void push(stack **top, node *bst_node)
{
    stack *new_node = (stack *)malloc(sizeof(stack));
    new_node->bst_node = bst_node;
    if (*top == NULL)
    {
        new_node->next = NULL;
    }
    else
    {
        new_node->next = (*top);
    }
    (*top) = new_node;
}

/* Function to pop elements from the top of the stack */
stack *pop(stack **top)
{
    if (isempty(*top) == false)
    {
        stack *temp = *top;
        *top = temp->next;
        return temp;
    }
}

/* Function that returns the topmost element of the stack */
stack *stack_top(stack *top)
{
    if (isempty(top) == false)
    {
        return top;
    }
}

/* Function that creates nodes and links it to the BST */
void create_bst_nodes(node **root, int node_data)
{
    node *new = (node *)malloc(sizeof(node));
    node *temp_ptr = (*root);

    new->data = node_data;
    new->left = NULL;
    new->right = NULL;

    if ((*root) == NULL)
    {
        (*root) = new;
    }
    else
    {
        while (temp_ptr != NULL)
        {
            if ((new->data > temp_ptr->data) && temp_ptr->right != NULL)
            {
                temp_ptr = temp_ptr->right;
            }
            else if ((new->data > temp_ptr->data) && temp_ptr->right == NULL)
            {
                temp_ptr->right = new;
                break;
            }
            else if ((new->data < temp_ptr->data) && temp_ptr->left != NULL)
            {
                temp_ptr = temp_ptr->left;
            }
            else if ((new->data < temp_ptr->data) && temp_ptr->left == NULL)
            {
                temp_ptr->left = new;
                break;
            }
        }
    }
}

/* Helper function that gives the maximum value in the left tree given the root */
int left_max(node *root)
{
    node *temp = root;
    while (temp->right != NULL)
    {
        temp = temp->right;
    }
    return temp->data;
}

/* Helper function which checks if the value given by the user is present in the BST or not */
bool check_presence(node *root, int val)
{
    node *temp = root;
    while (temp != NULL)
    {
        if (val < temp->data)
        {
            temp = temp->left;
        }
        else if (val > temp->data)
        {
            temp = temp->right;
        }
        else if (val == temp->data)
        {
            return true;
        }
    }
    return false;
}

/* Function which deletes the node from the BST */
void delete_node(node **root, int val)
{
    bool present = false;
    node *temp = (*root);
    node *parent = NULL;
    while (temp != NULL)
    {
        if (val < temp->data)
        {
            parent = temp;
            temp = temp->left;
        }
        else if (val > temp->data)
        {
            parent = temp;
            temp = temp->right;
        }
        else if (val == temp->data)
        {
            present = true;
            break;
        }
    }
    if (present == false)
    {
        printf("error\n");
        return;
    }
    else
    {
        if (temp->left == NULL && temp->right == NULL)
        {
            /* Leaf node */
            if (parent != NULL)
            {
                if (parent->left == temp)
                {
                    parent->left = NULL;
                }
                else if (parent->right == temp)
                {
                    parent->right = NULL;
                }
            }
            else if (parent == NULL) /* Root itself is a leaf */
            {
                *root = NULL;
            }
        }
        else if (temp->left == NULL && temp->right != NULL) /* Only right child */
        {
            if (parent != NULL)
            {
                if (parent->left == temp)
                {
                    parent->left = temp->right;
                }
                else if (parent->right == temp)
                {
                    parent->right = temp->right;
                }
            }
            else if (parent == NULL)
            {
                (*root) = temp->right;
            }
        }
        else if (temp->left != NULL && temp->right == NULL) /* Only left child */
        {
            if (parent != NULL)
            {
                if (parent->left == temp)
                {
                    parent->left = temp->left;
                }
                else if (parent->right == temp)
                {
                    parent->right = temp->left;
                }
            }
            else if (parent == NULL)
            {
                int data = left_max(temp->left);
                delete_node(&(*root), data);
                temp->data = data;
            }
        }
        else if (temp->left != NULL && temp->right != NULL) /* Has both left and right child nodes */
        {
            int new_data = left_max(temp->left);
            delete_node(&(*root), new_data);
            temp->data = new_data;
        }
    }
}

/* Function which gives the leaf count in the BST */
int num_leaves(node *root)
{
    int leaves = 0;
    if (root == NULL)
    {
        return 0;
    }
    else if (root->left == NULL && root->right == NULL)
    {
        return 1;
    }
    else
    {
        if (root->left != NULL)
        {
            leaves = leaves + num_leaves(root->left);
        }
        if (root->right != NULL)
        {
            leaves = leaves + num_leaves(root->right);
        }
    }
    return leaves;
}

/* Function which gives the number of internal nodes */
int num_internal_nodes(int leaves)
{
    printf("Number of internal nodes : %d\n", total_nodes - leaves);
}

/* Function which returns the height of the BST */
int height(node *root)
{
    int tree_height, temp1, temp2;
    if (root == NULL)
    {
        return -1;
    }
    else
    {
        temp1 = 1 + height(root->left);
        temp2 = 1 + height(root->right);
        tree_height = (temp1 >= temp2) ? temp1 : temp2;
        return tree_height;
    }
}

/* A function which calls the num_leaves, num_internal_nodes and height function
    and displays the number of leaves, internal node and the height of the BST
*/
int get_stats(node *root)
{
    node *temp = root;
    int leaves, tree_height;
    leaves = num_leaves(temp);
    printf("Number of leaves : %d\n", leaves);
    num_internal_nodes(leaves);
    tree_height = height(root);
    printf("Height of the tree : %d\n", tree_height);
}

/* Iterative function for in-order traversal */
void inorder_traversal(node *root)
{
    if (root == NULL)
    {
        return;
    }
    node *curr = root;
    stack *temp = NULL;
    while (true)
    {
        while (curr != NULL)
        {
            push(&traversal_stack, curr);
            curr = curr->left;
        }
        if (curr == NULL && (isempty(traversal_stack) == false))
        {
            temp = pop(&traversal_stack);
            printf("%d ", temp->bst_node->data);
            curr = temp->bst_node->right;
        }
        if (curr == NULL && (isempty(traversal_stack) == true))
        {
            break;
        }
    }
}

/* Iterative function for pre-order traversal */
void preorder_traversal(node *root)
{
    if (root == NULL)
    {
        return;
    }
    node *curr = root;
    stack *temp = NULL;
    while (true)
    {
        while (curr != NULL)
        {
            printf("%d ", curr->data);
            push(&traversal_stack, curr);
            curr = curr->left;
        }
        if (curr == NULL && (isempty(traversal_stack) == false))
        {
            temp = pop(&traversal_stack);
            curr = temp->bst_node->right;
        }
        if (curr == NULL && (isempty(traversal_stack) == true))
        {
            break;
        }
    }
}

/* Iterative function for post-order traversal */
void postorder_traversal(node *root)
{
    if (root == NULL)
    {
        return;
    }
    node *curr = root;
    stack *temp = NULL;
    stack *popped = NULL;
    while (true)
    {
        while (curr != NULL)
        {
            push(&traversal_stack, curr);
            curr = curr->left;
        }
        if (curr == NULL && (isempty(traversal_stack) == false))
        {
            temp = stack_top(traversal_stack);
            curr = temp->bst_node->right;
            if (curr == NULL)
            {
                popped = pop(&traversal_stack);
                printf("%d ", popped->bst_node->data);

                while ((isempty(traversal_stack) == false) && (stack_top(traversal_stack)->bst_node->right == popped->bst_node))
                {
                    popped = pop(&traversal_stack);
                    printf("%d ", popped->bst_node->data);
                }
            }
        }
        if (curr == NULL && (isempty(traversal_stack) == true))
        {
            break;
        }
    }
}

/* Function which frees the nodes of the BST before exit */
void free_nodes(node **root)
{
    if (*root == NULL)
    {
        return;
    }
    else
    {
        free_nodes(&((*root)->left));
        free_nodes(&((*root)->right));
        free(*root);
    }
}

int main()
{
    int menuInput, n, data, delete_node_val;

    do
    {
        printf("Enter 0 to exit the program\n");
        printf("Enter 1 to add data to BST\n");
        printf("Enter 2 to delete data from BST\n");
        printf("Enter 3 to display the number of leaves, internal nodes and height of BST\n");
        printf("Enter 4 to display in-order traversal expression\n");
        printf("Enter 5 to display pre-order traversal expression\n");
        printf("Enter 6 to display post-order traversal expression\n");

        scanf("%d", &menuInput);

        switch (menuInput)
        {
        case 0:
            free_nodes(&root);
            break;
        case 1:
            scanf("%d", &n);
            total_nodes = total_nodes + n;
            for (int i = 0; i < n; i++)
            {
                scanf("%d", &data);
                create_bst_nodes(&root, data);
            }
            break;
        case 2:
            scanf("%d", &delete_node_val);
            if (check_presence(root, delete_node_val))
            {
                delete_node(&root, delete_node_val);
                total_nodes--;
            }
            else
            {
                printf("error\n");
            }
            break;
        case 3:
            get_stats(root);
            break;
        case 4:
            inorder_traversal(root);
            printf("\n");
            break;
        case 5:
            preorder_traversal(root);
            printf("\n");
            break;
        case 6:
            postorder_traversal(root);
            printf("\n");
            break;
        default:
            break;
        }
    } while (menuInput != 0);
    return 0;
}