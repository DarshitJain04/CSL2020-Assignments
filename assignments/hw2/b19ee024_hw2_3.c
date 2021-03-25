#include <stdio.h>
#include <stdlib.h>

typedef struct NODE{
    int value;
    struct NODE * next;
}node;

/* Function to create nodes and link it to create a linked list */
void create_node(node ** head, int data){
    node * new = (node *) malloc(sizeof(node));
    node * ptr = (*head);

    /* Creating new node */
    new->value = data;
    new->next = NULL;

    /* Linking the new node */
    if((*head) == NULL){
        (*head) = new;
    }else{
        while (ptr->next != NULL)
        {
            ptr = ptr->next;
        }
        ptr->next = new;
    }
}

/* Function that returns modified head after reversing the linked list */
node * reverse_linked_list(node * head, int size){

    if(head == NULL || head->next == NULL){
        return head;
    }
    node * current_node = head;
    node * temp;
    node * previous_node = NULL;

    while (current_node)
    {
        temp = current_node->next;
        current_node->next = previous_node;
        previous_node = current_node;
        current_node = temp;
    }

    head = previous_node;
    return head;
}

/* Function to display the linked list */
void display_linked_list(node * head, int n){
    node * temp = head;

    /* If the linked list is empty(when input n is 0), print 0 */
    if (head == NULL)
    {
        printf("NULL");
    }else{
        for (int i = 0; i < n; i++)
        {   
            /* Checking if it is the last node to prevent trailing space */
            if (temp->next ==NULL)
            {
                printf("%d", temp->value);
            }else{
                printf("%d ", temp->value);
            }
            temp = temp->next;
        }
    }
}

/* Function to free nodes */
void free_nodes(node ** head){
    node * temp = (*head);
    node * next_node;
    while (temp != NULL)
    {
        next_node = temp->next;
        free(temp);
        temp = next_node;
    }
    (*head) = NULL;
}

int main(){

    node * head = NULL;
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        int data;
        scanf("%d",&data);
        create_node(&head, data);
    }
    display_linked_list(head, n);
    printf("\n");
    head = reverse_linked_list(head, n);
    display_linked_list(head, n);
    free_nodes(&head);

    return 0;
}