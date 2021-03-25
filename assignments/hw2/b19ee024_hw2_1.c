#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/* Creating a boolean datatype using enum */
enum check
{
    empty = true
};

int len_check = 0;

/* For stack */
typedef struct stackNode
{
    int data;
    struct stackNode *next;
} node;

/* Generating a linked list which can be used to display the required sequence */
typedef struct RESULT
{
    char *command;
    int val;
    struct RESULT *next;
} res;

/* Function to check if the stack is empty or not */
bool isempty(node *top)
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
void push(node **top, int val)
{
    node *new_node = (node *)malloc(sizeof(node));
    new_node->data = val;
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
void pop(node **top)
{
    if (isempty(*top) == false)
    {
        node *temp = *top;
        *top = temp->next;
        free(temp);
        len_check--;
    }
}

/* Just a helper function used to pop elements from the stack created using input sequence */
void popinput(node **top)
{
    if (isempty(*top))
    {
        printf("Stack is empty\n");
    }
    else
    {
        node *temp = *top;
        *top = temp->next;
        free(temp);
    }
}

/* Function that returns the top element of the stack */
int stackTop(node *top)
{
    if (!isempty(top))
    {
        return top->data;
    }
}

/* Function to generate nodes and linking it (for the linked list to be used for output) */
void create_res_node(res **head, char *command, int data)
{
    res *new = (res *)malloc(sizeof(res));
    res *ptr = (*head);

    /* Creating new node */
    new->command = command;
    new->val = data;
    new->next = NULL;

    /* Linking the new node */
    if ((*head) == NULL)
    {
        (*head) = new;
    }
    else
    {
        while (ptr->next != NULL)
        {
            ptr = ptr->next;
        }
        ptr->next = new;
    }
}

/* A helper function that pops elements from the stack if it matches with the top of input stack */
void removeElements(node **top1, node **top2, res **head)
{
    while (stackTop(*top1) == stackTop((*top2)) && (*top1) != NULL && (*top2) != NULL)
    {
        popinput(&(*top1));
        create_res_node(&(*head), "pop", (*top2)->data);
        pop(&(*top2));
    }
}

/* Function that acutally displays the sequence of operation */
void display_res_linked_list(res *head)
{
    res *temp_head = head;
    while (temp_head != NULL)
    {
        if (temp_head->command == "pop")
        {
            if (temp_head->next == NULL)
            {
                printf("%s().", temp_head->command);
            }
            else
            {
                printf("%s(), ", temp_head->command);
            }
        }
        else
        {
            if (temp_head->next == NULL)
            {
                printf("%s(%d).", temp_head->command, temp_head->val);
            }
            else
            {
                printf("%s(%d), ", temp_head->command, temp_head->val);
            }
        }
        temp_head = temp_head->next;
    }
    free(temp_head);
}

/* Function to free nodes of the linked list created */
void free_nodes(res **head)
{
    res *temp = (*head);
    res *next_node;
    while (temp != NULL)
    {
        next_node = temp->next;
        free(temp);
        temp = next_node;
    }
    (*head) = NULL;
}

int main()
{
    /* Creating a stack for input values */
    node *top1 = NULL;
    /* Creating a stack for the purpose of computing the operations */
    node *top2 = NULL;
    /* Creating the linked list for output purpose */
    res *head = NULL;

    int n;
    scanf("%d", &n);
    int arr[n];

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &(arr[i]));
    }

    /* Creating a stack for the input values */
    for (int i = n - 1; i >= 0; i--)
    {
        push(&top1, arr[i]);
    }

    for (int i = 1; i <= n; i++)
    {
        if (i == stackTop(top1))
        {
            push(&top2, i);
            len_check++;
            ;
            create_res_node(&head, "push", i);

            pop(&top2);
            create_res_node(&head, "pop", i);
            popinput(&top1);

            removeElements(&top1, &top2, &head);
        }
        else
        {
            push(&top2, i);
            len_check++;
            create_res_node(&head, "push", i);
        }
    }

    /* If the length/size of the stack at the end of all the operations is zero,
    then it is possible to print such sequence */
    if (len_check == 0 && n != 0)
    {
        printf("Yes. It is possible by the following sequence of operations:\n");
        display_res_linked_list(head);
        printf("\n");
    }
    else
    {
        printf("Not possible.\n");
    }

    free_nodes(&head);

    return 0;
}