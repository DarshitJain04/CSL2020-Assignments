#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

/* stack used for postfix purpose */
char stack[100][100];
int top = -1;

/* stack used for postfix evluation purpose */
float eval_stack[100];
int eval_top = -1;

/* helper function which gives precedence order of the operator */
int check_precedence(char * z){
    if (*z == '^' ||  z[0] == '>' || z[0] == '<')
    {
        return 3;
    }else if(*z == '/' || *z == '*'){
        return 2;
    }else if(*z == '+' || *z == '-'){
        return 1;
    }else{
        return 0;
    }
}

/* helper function which checks if the object passed is an operator or not */
bool check_operator(char * z){
    if (*z == '^' || *z == '/' || *z == '*' || *z == '+' || *z == '-' || z[0] == '>' || z[0] == '<')
    {
        return true;
    }else{
        return false;
    }  
}

/* function that checks if the stack used for postfix expression is full or not */
bool isfull(){
    if(top == 99){
        return true;
    }else{
        return false;
    }
}

/* function that tells us if the stack used for postfix expression is empty or not */
bool isempty(){
    if(top == -1){
        return true;
    }else{
        return false;
    }
}

/* function used to push operators to the stack */
void push(char * operator){
    if(isfull())
    {
        printf("Stack is full\n");
    }else{
        top++;
        strcpy(stack[top], operator);
    }
}

/* function used to pop the elements from the top of the stack used for postfix expression */
char * pop(){
    if (isempty())
    {
        printf("Stack is empty\n");
    }else
    {
        char * temp = stack[top];
        top--;
        return temp;
    }
}

/* function that returns the topmost element of the stack used for postfix expression */
char * stackTop(){
    if (isempty() == false)
    {
        return stack[top];
    }
}

/* function used to push elements to the stack used for postfix evaluation */
void eval_push(float num){
    eval_top++;
    eval_stack[eval_top] = num;
}

/* function that pops the topmost element of the stack used for postfix evalution */
float eval_pop(){
    float temp = eval_stack[eval_top];
    eval_top--;
    return temp;
}

/* function that returns the topmost element of the stack used for postfix evaluation */
float eval_stackTop(){
    return eval_stack[eval_top];
}

/* helper function used to evaluate */
float evaluation(float n, float m, char * operator){

    int b = (int) n;
    int c = (int) m;

    if (*operator == '*')
    {
        return (float)(n*m);
    }else if(*operator == '/'){
        return (float)(m/n);
    }else if(*operator == '+'){
        return (float)(n+m);
    }else if(*operator == '-'){
        return (float)(m-n);
    }else if(operator[0] == '<'){
        return (float)(c<<b);
    }else if(operator[0] == '>'){
        return (float)(c>>b);
    }   
}

int main(){

    /* array used to store the input */
    char infix_input[100];
    gets(infix_input);

    /* array use to store postfix expression */
    char postfix_expression[100][100];
    postfix_expression[0][0] = '\0';

    /* array for splitting the input string into numbers and operators */
    char arr_infix[100][100];
    arr_infix[0][0] = '\0';

    int k = 0;
    int len = 0;
    int bracket_count = 0;
    int num_before_opening_parentheses = 0;
    int num_after_closing_parentheses = 0;

    /* here array arr_infix is created */
    for (int i = 0; i < strlen(infix_input); i++){
        int temp = i;
        int count = 0;
        if (isdigit(infix_input[i]))
        {
            while (isdigit(infix_input[temp]))
            {
                strncat(arr_infix[k], &(infix_input[temp]), 1);
                temp++;
                count++;
            }
            i = i + count - 1;
            if ((temp != strlen(infix_input)) && infix_input[temp] == '('){
                num_before_opening_parentheses++;
            }
        }else if(infix_input[i] == '<' && infix_input[temp+1] == '<'){
            strcat(arr_infix[k], "<<");
            i++;
        }else if(infix_input[i] == '>' && infix_input[temp+1] == '>'){
            strcat(arr_infix[k], ">>");
            i++;
        }else{
            if (infix_input[i] == '('){
                bracket_count++;
            }else if (infix_input[i] == ')'){
                bracket_count--;
                if ((temp != strlen(infix_input) - 1) && isdigit(infix_input[temp+1])){
                    num_after_closing_parentheses++;
                }
            }
            strncat(arr_infix[k], &(infix_input[i]), 1);
        }
        len++;
        k++;
    }

    int post_len = 0;
    int j = 0;

    /* if the parentheses are balanced, then the variable bracket_count would be 0  */

    if (bracket_count == 0 && (check_operator(arr_infix[0]) == false) && num_after_closing_parentheses == 0 && num_before_opening_parentheses == 0){

        /* logic to generate the postfix expression */

        for (int i = 0; i < len; i++)
        {
            if (isdigit(*(arr_infix[i])))
            {
                strcat(postfix_expression[j], arr_infix[i]);
                j++;
                post_len++;

            }else if (*arr_infix[i] == '('){

                push(arr_infix[i]);

            }else if(*arr_infix[i] == ')'){

                /* We will have to pop the elements until we find "(" */
                while ((*(stackTop()) != '('))
                {
                    char * top1 = pop();
                    strcat(postfix_expression[j], top1);
                    post_len++;
                    j++;
                }
                pop();

            }else if(check_operator(arr_infix[i])){
                if(top == -1){
                    
                    push(arr_infix[i]);

                }else{
                    if (check_precedence(arr_infix[i]) > check_precedence(stackTop())){
                        if(*arr_infix[i] == '^'){
                            strcat(postfix_expression[j], arr_infix[i]);
                            j++;
                        }else{
                            push(arr_infix[i]);
                        }
                    }else if((check_precedence(arr_infix[i]) == check_precedence(stackTop())) && check_precedence(arr_infix[i]) == 3){
                        if(*arr_infix[i] == '^'){
                            strcat(postfix_expression[j], arr_infix[i]);
                            j++;
                        }else{
                            push(arr_infix[i]);
                        }
                    }else{
                        char * temp_char = stackTop();
                        while ((check_precedence(arr_infix[i]) <= check_precedence(temp_char)) && (isempty() == false))
                        {
                            char * top2 = pop();
                            strcat(postfix_expression[j], top2);
                            post_len++;
                            j++;
                            if (isempty() == false){
                                temp_char = stackTop();
                            }
                        }
                        push(arr_infix[i]);
                    }
                }
            }
            
        }
        while ((isempty() == false) && *(stackTop()) != '(')
        {
            char * top3 = pop();
            strcat(postfix_expression[j], top3);
            post_len++;
            j++;
        }

        float a,b,c,res;

        /* evaluation */

        for (int i = 0; i < j; i++)
        {
            if (isdigit(*(postfix_expression[i])))
            {
                eval_push((float)atoi(postfix_expression[i]));
            }else if(*(postfix_expression[i]) == '^'){
                a = eval_pop();
                eval_push(a*a);
            }else{
                b = eval_stackTop();
                eval_pop();
                c = eval_stackTop();
                eval_pop();

                res = evaluation(b, c, postfix_expression[i]);
                eval_push(res);
            }
        }
        
        float eval_value = eval_stackTop();

        /* displaying the postfix expression */

        for (int i = 0; i < j; i++)
        {
            int temp = i;
            if (i == j - 1)
                {
                    printf("%s", postfix_expression[i]);
                }else if(((postfix_expression[i][0])== '<') || ((postfix_expression[i][0]) == '>')){
                    printf("%s, ", postfix_expression[i]);
                }
                else{
                    printf("%s, ", postfix_expression[i]);
                }
        }
        printf("\n");
        if (j!=0)
        {
            printf("%.3f\n", eval_value);
        }

    }else{
        printf("error");
    }
        
    return 0;
}