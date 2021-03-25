#include <stdio.h>
#include <stdlib.h>

typedef struct POLY{
    int power;
    int coeff;
    struct POLY * next;
}poly;

/* Function to create nodes for the polynomial and link it to create a linked list */
void create_poly_node(poly ** head, int power, int coeff){
    poly * new = (poly *) malloc(sizeof(poly));
    poly * ptr = (*head);

    /* Creating new node */
    new->coeff = coeff;
    new->power = power;
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

/* Function to display the linked list */
void display_poly(poly * head){
    poly * temp = head;
    
    /* If the linked list is empty, print 0 */
    if (head == NULL)
    {
        printf("0");
    }else{
        while (temp != NULL)
        {
            if(temp->coeff != 0){
                if (temp != NULL && temp->coeff < 0)
                {   
                    if (temp == head)
                    {
                        printf("-");
                    }else{
                        printf(" -");
                    }
                }
                if (temp->power == 0)
                {
                    printf("%d", abs(temp->coeff));
                }else
                {
                    printf("%dx^%d", abs(temp->coeff), temp->power);
                }
                if (temp->next != NULL && temp->next->coeff > 0)
                {
                    printf(" + ");
                }
            }
            temp = temp->next;
        }
    }
}

/* Utility function */
int expo_value(int num, int expo){
    int value = 1;
    for (int i = 0; i < expo; i++)
    {
        value = value * num;
    }
    return value;
}

/* Function to calculate the resultant value */
void resultant_value(poly * head, int x){
    poly * temp = head;
    int count = 0;
    while (temp != NULL)
    {
        count = count + ((temp->coeff)*(expo_value(x, temp->power)));
        temp = temp->next;
    }
    printf("%d", count);
}

/* Function to add both the polynomials */
void add_poly(poly * poly1, poly * poly2, poly ** poly3){
    poly * temp1 = poly1;
    poly * temp2 = poly2;

    while (temp1 && temp2)
    {
        if(temp2->power == temp1->power){
            /* Creating node only if the resultant coefficient is not 0 */
            if((temp1->coeff + temp2->coeff) != 0){
                create_poly_node(&(*poly3), temp2->power, (temp1->coeff + temp2->coeff));
            }
            temp1 = temp1->next;
            temp2 = temp2->next;
        }else if (temp1->power > temp2->power)
        {
            create_poly_node(&(*poly3), temp1->power, temp1->coeff);
            temp1 = temp1->next;
        }else
        {
            create_poly_node(&(*poly3), temp2->power, temp2->coeff);
            temp2 = temp2->next;
        }
    }
    
    /* Adding leftover terms if any */
    while (temp1)
    {
        create_poly_node(&(*poly3), temp1->power, temp1->coeff);
        temp1 = temp1->next;
    }
    while (temp2)
    {
        create_poly_node(&(*poly3), temp2->power, temp2->coeff);
        temp2 = temp2->next;
    }
}

/* Function to subtract both the polynomials */
void subtract_poly(poly * poly1, poly * poly2, poly ** poly4){
    poly * temp1 = poly1;
    poly * temp2 = poly2;

    while (temp1 && temp2)
    {
        if(temp2->power == temp1->power){
            /* Creating node only if the resultant coefficient is not 0 */
            if((temp1->coeff - temp2->coeff) != 0){
                create_poly_node(&(*poly4), temp2->power, (temp1->coeff - temp2->coeff));
            }
            temp1 = temp1->next;
            temp2 = temp2->next;
        }else if (temp1->power > temp2->power)
        {
            create_poly_node(&(*poly4), temp1->power, temp1->coeff);
            temp1 = temp1->next;
        }else
        {
            create_poly_node(&(*poly4), temp2->power, -(temp2->coeff));
            temp2 = temp2->next;
        }
    }
    
    /* Adding leftover terms if any */
    while (temp1)
    {
        create_poly_node(&(*poly4), temp1->power, temp1->coeff);
        temp1 = temp1->next;
    }
    while (temp2)
    {
        create_poly_node(&(*poly4), temp2->power, -(temp2->coeff));
        temp2 = temp2->next;
    }
}

/* Function to free nodes */
void free_nodes(poly ** head){
    poly * temp = (*head);
    poly * next_node;
    while (temp != NULL)
    {
        next_node = temp->next;
        free(temp);
        temp = next_node;
    }
    (*head) = NULL;
}

int main(){
    int k;
    scanf("%d", &k);
    while (k--)
    {
        poly * poly1 = NULL;
        poly * poly2 = NULL;
        poly * poly3 = NULL;
        poly * poly4 = NULL;

        int n1, n2, x;

        scanf("%d", &n1);
        for (int i = n1; i >= 0; i--)
        {   
            int coeff1;
            scanf("%d", &coeff1);
            if (coeff1 != 0)
            {
                /* Not creating nodes when input coefficient is 0 */
                create_poly_node(&poly1, i, coeff1); 
            }  
        }

        scanf("%d", &n2);
        for (int i = n2; i >= 0; i--)
        {   
            int coeff2;
            scanf("%d", &coeff2);
            if (coeff2 != 0)
            {
                /* Not creating nodes when input coefficient is 0 */
                create_poly_node(&poly2, i, coeff2);
            }   
        }

        scanf("%d", &x);

        add_poly(poly1, poly2, &poly3);

        subtract_poly(poly1, poly2, &poly4);

        /* Displaying polynomial */
        printf("P1(x) : ");
        display_poly(poly1);
        printf("\n");
        printf("P2(x) : ");
        display_poly(poly2);
        printf("\n");
        printf("P3(x) = P1(x) + P2(x) : ");
        display_poly(poly3);
        printf("\n");
        printf("P4(x) = P1(x) - P2(x) : ");
        display_poly(poly4);
        printf("\n");

        /* Displaying value of polynomial for given value of x */
        printf("P1(%d) = ", x);
        resultant_value(poly1, x);
        printf("\n");
        printf("P2(%d) = ", x);
        resultant_value(poly2, x);
        printf("\n");
        printf("P3(%d) = ", x);
        resultant_value(poly3, x);
        printf("\n");
        printf("P4(%d) = ", x);
        resultant_value(poly4, x);
        printf("\n");

        /* Freeing nodes of linked list*/
        free_nodes(&poly1);
        free_nodes(&poly2);
        free_nodes(&poly3);
        free_nodes(&poly4);
    }
    return 0;
}