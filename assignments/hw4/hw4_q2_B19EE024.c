#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Node structure for AVL tree */
typedef struct AVL
{
    int data;
    struct AVL *left;
    struct AVL *right;
    int node_height;
    int balanceFactor;
} avl;

avl *root = NULL;

/* Creating an array to store different widths and finding th maximum from it */
int width_avl[100];
int width_avl_index = 0;

/* Function that returns height of a tree given the node */
int height(avl *root)
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

/* Helper function to find the width of the avl tree */
int height_width(avl *root)
{
    if (root != NULL)
    {
        int temp_right = height_width(root->right);
        int temp_left = height_width(root->left);
        width_avl[width_avl_index] = 1 + temp_left + temp_right;
        width_avl_index++;
        if (temp_left >= temp_right)
        {
            return (temp_left + 1);
        }
        else
        {
            return (temp_right + 1);
        }
    }
    else
    {
        return 0;
    }
}

/* A function which gives the balance factor for a given node */
/* I have considered balance factor = height of right subTree - height of left subTree */
int balanceFactor(avl *root)
{
    if (root == NULL)
    {
        return 0;
    }

    int bf;
    bf = height(root->right) - height(root->left);
    return bf;
}

/* A function which performs left rotation */
avl *leftRotate(avl *node)
{
    avl *temp_right_sub = node->right;
    avl *left_sub = temp_right_sub->left;

    node->right = left_sub;
    temp_right_sub->left = node;

    return temp_right_sub;
}

/* A function that performs right rotation */
avl *rightRotate(avl *node)
{
    avl *temp_left_sub = node->left;
    avl *right_sub = temp_left_sub->right;

    temp_left_sub->right = node;
    node->left = right_sub;

    return temp_left_sub;
}

/* Function which creates returns a node for AVL tree */
avl *create_avl_node(int node_data)
{
    avl *new = (avl *)malloc(sizeof(avl));

    new->data = node_data;
    new->left = NULL;
    new->right = NULL;

    return new;
}

/* Function which creates AVL tree */
avl *create_avl_tree(avl **root, int node_data)
{
    avl *temp_ptr = (*root);
    avl *temp_returned_node = NULL;
    if (temp_ptr == NULL)
    {
        temp_ptr = create_avl_node(node_data);
    }
    else
    {
        if (node_data > temp_ptr->data)
        {
            temp_ptr->right = create_avl_tree(&(temp_ptr->right), node_data);
        }
        else
        {
            temp_ptr->left = create_avl_tree(&(temp_ptr->left), node_data);
        }
    }

    temp_ptr->balanceFactor = balanceFactor(temp_ptr);

    if (temp_ptr->balanceFactor < -1 && temp_ptr->left->data > node_data)
    {
        /* left left */
        temp_returned_node = rightRotate(temp_ptr);
        return temp_returned_node;
    }
    else if (temp_ptr->balanceFactor < -1 && temp_ptr->left->data < node_data)
    {
        /* left right */
        temp_ptr->left = leftRotate(temp_ptr->left);
        temp_returned_node = rightRotate(temp_ptr);
        return temp_returned_node;
    }
    else if (temp_ptr->balanceFactor > 1 && temp_ptr->right->data < node_data)
    {
        /* right right */
        temp_returned_node = leftRotate(temp_ptr);
        return temp_returned_node;
    }
    else if (temp_ptr->balanceFactor > 1 && temp_ptr->right->data > node_data)
    {
        /* right left */
        temp_ptr->right = rightRotate(temp_ptr->right);
        temp_returned_node = leftRotate(temp_ptr);
        return temp_returned_node;
    }
    return temp_ptr;
}

/* Helper function to give the minimum value from right tree */
int right_min(avl *root)
{
    avl *temp = root;
    while (temp->left != NULL)
    {
        temp = temp->left;
    }
    return temp->data;
}

/* A function which checks if the given value is present in the tree or not */
bool check_presence(avl *root, int val)
{
    avl *temp = root;
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

/* Function which deletes node fromt he AVL tree */
avl *delete_node(avl *avl_root_node, int val)
{
    if (avl_root_node == NULL)
    {
        return avl_root_node;
    }
    bool present = false;
    avl *temp = avl_root_node;
    avl *parent = NULL;
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
    if (present == true)
    {
        if (val > avl_root_node->data)
        {
            avl_root_node->right = delete_node(avl_root_node->right, val);
        }
        else if (val < avl_root_node->data)
        {
            avl_root_node->left = delete_node(avl_root_node->left, val);
        }
        else
        {
            if ((avl_root_node->right == NULL) || (avl_root_node->left == NULL))
            {
                avl *new = NULL;
                if (avl_root_node->left != NULL)
                {
                    new = avl_root_node->left;
                }
                else
                {
                    new = avl_root_node->right;
                }

                if (new != NULL)
                {
                    *avl_root_node = *new;
                }
                else if (new == NULL)
                {
                    new = avl_root_node;
                    avl_root_node = NULL;
                }
                free(new);
            }
            else
            {
                int right_min_val = right_min(avl_root_node->right);
                avl_root_node->data = right_min_val;
                avl_root_node->right = delete_node(avl_root_node->right, right_min_val);
            }
        }

        if (avl_root_node == NULL)
            return avl_root_node;

        avl_root_node->balanceFactor = balanceFactor(avl_root_node);

        avl *temp_returned_node = NULL;

        if (avl_root_node->balanceFactor < -1 && balanceFactor(avl_root_node->left) <= 0)
        {
            /* left left */
            temp_returned_node = rightRotate(avl_root_node);
            return (temp_returned_node);
        }
        else if (avl_root_node->balanceFactor < -1 && balanceFactor(avl_root_node->left) > 0)
        {
            /* left right */
            avl_root_node->left = leftRotate(avl_root_node->left);
            temp_returned_node = rightRotate(avl_root_node);
            return (temp_returned_node);
        }
        else if (avl_root_node->balanceFactor > 1 && balanceFactor(avl_root_node->right) >= 0)
        {
            /* right right */
            temp_returned_node = leftRotate(avl_root_node);
            return (temp_returned_node);
        }
        else if (avl_root_node->balanceFactor > 1 && balanceFactor(avl_root_node->right) < 0)
        {
            /* right left */
            avl_root_node->right = rightRotate(avl_root_node->right);
            temp_returned_node = leftRotate(avl_root_node);
            return (temp_returned_node);
        }
        return avl_root_node;
    }
}

/* Function which performs inorder traversal */
void inorder(avl *node)
{
    if (node == NULL)
        return;
    inorder(node->left);
    node->node_height = height(node);
    node->balanceFactor = balanceFactor(node);
    printf("(%d, %d, %d) ", node->data, node->node_height, node->balanceFactor);
    inorder(node->right);
}

/* Helper function to print nodes on left periphery of the tree (except the leaf) */
void perimeterLeft(avl *root)
{
    printf("%d ", root->data);
    root = root->left;
    while (root != NULL)
    {
        if (root->left == NULL && root->right == NULL)
        {
            break;
        }
        else
        {
            printf("%d ", root->data);
            if (root->left)
            {
                root = root->left;
            }
            else if (root->right)
            {
                root = root->right;
            }
        }
    }
}

/* Helper function to print all the leaves */
void perimeterLeaf(avl *root)
{
    if (root == NULL)
    {
        return;
    }
    else
    {
        perimeterLeaf(root->left);
        perimeterLeaf(root->right);
        if (root->left == NULL && root->right == NULL)
        {
            printf("%d ", root->data);
        }
    }
}

/* Helper function to print nodes on right periphery of the tree */
/* Since I have considered anti-clock wise direction for perimeter, 
we need to print these nodes in opposite order
*/
void perimeterRight(avl *root)
{
    int arr[100];
    int temp = 0;
    while (root != NULL)
    {
        if (root->left == NULL && root->right == NULL)
        {
            break;
        }
        else
        {
            arr[temp] = root->data;
            temp++;
            if (root->right)
            {
                root = root->right;
            }
            else if (root->left)
            {
                root = root->left;
            }
        }
    }
    for (int i = temp - 1; i >= 0; i--)
    {
        printf("%d ", arr[i]);
    }
}

/* Function to print the perimeter of the tree in anti-clock wise direction */
void perimeter(avl *root)
{
    if (root != NULL)
    {
        perimeterLeft(root);
        perimeterLeaf(root->left);
        perimeterLeaf(root->right);
        if (root->right != NULL)
        {
            perimeterRight(root->right);
        }
        printf("\n");
    }
}

/* Function to print the width of the AVL Tree */
void width(avl *root)
{
    if (root == NULL)
    {
        return;
    }
    else
    {
        height_width(root);
        int max = width_avl[0];
        for (int i = 0; i < width_avl_index; i++)
        {
            if (max <= width_avl[i])
            {
                max = width_avl[i];
            }
        }
        printf("Width = %d\n", max);
    }
}

/* Function to print the lowest common ancestor of two given nodes */
void lowest_common_ancestor(avl *root, int a, int b)
{

    if (check_presence(root, a) && check_presence(root, b))
    {
        if (root != NULL)
        {
            while (root != NULL)
            {
                if (a == root->data && b == root->data)
                {
                    break;
                }
                else if (a > root->data && b > root->data)
                {
                    root = root->right;
                }
                else if (a < root->data && b < root->data)
                {
                    root = root->left;
                }
                else
                {
                    break;
                }
            }
            printf("%d\n", root->data);
        }
    }
    else
    {
        printf("error\n");
    }
}

/* Function to print route between two given nodes */
void route(avl *root, int a, int b)
{
    if (check_presence(root, a) && check_presence(root, b))
    {
        if (a == b)
        {
            printf("%d\n", a);
        }
        else if ((a <= root->data && b < root->data) || (a >= root->data && b > root->data))
        {
            while (root != NULL)
            {
                if (root->data == a)
                {
                    break;
                }
                else if (root->data > a)
                {
                    root = root->left;
                }
                else if (root->data < a)
                {
                    root = root->right;
                }
            }
            if ((a > b && check_presence(root->left, b)) || (b > a && check_presence(root->right, b)))
            {
                printf("%d ", a);
                while (root != NULL)
                {
                    if (root->data > b)
                    {
                        root = root->left;
                    }
                    else if (b > root->data)
                    {
                        root = root->right;
                    }
                    if (root->data == b)
                    {
                        printf("%d\n", b);
                        break;
                    }
                    else
                    {
                        printf("%d ", root->data);
                    }
                }
            }
            else
            {
                printf("-1\n");
            }
        }
        else
        {
            printf("-1\n");
        }
    }
    else
    {
        printf("-1\n");
    }
}

int main()
{
    int menuInput, n, data, delete_node_val, a, b;

    do
    {
        printf("Enter 0 to exit the program\n");
        printf("Enter 1 to create AVL tree\n");
        printf("Enter 2 to add data to existing AVL tree\n");
        printf("Enter 3 to delete data from AVL tree\n");
        printf("Enter 4 to display in-order traversal expression\n");
        printf("Enter 5 to print the width and the perimeter of the tree\n");
        printf("Enter 6 to print the lowest common ancestor\n");
        printf("Enter 7 to print the route\n");

        scanf("%d", &menuInput);

        switch (menuInput)
        {
        case 0:
            break;
        case 1:
            scanf("%d", &n);
            for (int i = 0; i < n; i++)
            {
                scanf("%d", &data);
                root = create_avl_tree(&root, data);
            }
            break;
        case 2:
            scanf("%d", &data);
            root = create_avl_tree(&root, data);
            break;
        case 3:
            scanf("%d", &data);
            if (check_presence(root, data))
            {
                root = delete_node(root, data);
            }
            break;
        case 4:
            inorder(root);
            printf("\n");
            break;
        case 5:
            width_avl_index = 0;
            width(root);
            printf("Perimeter = ");
            perimeter(root);
            break;
        case 6:
            scanf("%d", &a);
            scanf("%d", &b);
            lowest_common_ancestor(root, a, b);
            break;
        case 7:
            scanf("%d", &a);
            scanf("%d", &b);
            route(root, a, b);
            break;
        default:
            break;
        }
    } while (menuInput != 0);
    return 0;
}