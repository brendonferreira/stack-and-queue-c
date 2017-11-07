#include <stdio.h>
#include "linkedstack.h"
#include <stdlib.h>


// A utility function to check if the given character is operand
int is_operator(char ch){
    return (ch >= '0' && ch <= '9');
}
 
// A utility function to return precedence of a given operator
// Higher returned value means higher precedence
int priority(char ch){
    switch (ch)
    {
    case '+':
    case '-':
        return 1;
 
    case '*':
    case '/':
        return 2;
 
    case '^':
        return 3;
    }
    return -1;
}

int main(){
    struct node *head = NULL;

    char exp[20];
    int k, i;
    char x;
    printf("Entre com a expressão:");
    fgets (exp, 20, stdin);

    init_stack(head);

    for (i = 0, k = -1; exp[i] ; ++i) {
        // Debug mto loco
        // printf( "\n--->%c<--\n", exp[i] );
        if( exp[i] == ' ' ) {

        } else if (is_operator(exp[i])){
            exp[++k] = exp[i];
        } else if (exp[i] == '(') {
            head = push_in_stack(head, exp[i]); 
        } else if (exp[i] == ')') {
            while ( is_stack_empty(head) == 0 && get_value(head) != '(') {
                head = pop_stack(head, &x);
                exp[++k] = x; 
            }
            if ( is_stack_empty(head) == 0 && get_value(head) != '(') {
                printf("Expressão inválida!");
                return -1;          
            } else {
                head = pop_stack(head, &x);
            }
        } else {
            while ( is_stack_empty(head) == 0 && priority(exp[i]) <= priority(get_value(head))) {
                exp[++k] = head->data; 
                head = pop_stack(head, &x);
            }
            head = push_in_stack(head, exp[i]);
        }
 
    }

    while ( is_stack_empty(head) == 0 ) {
        head = pop_stack(head, &x);
        exp[++k] = x; 
    }

    exp[++k] = '\0';
    
    printf( "%s\n", exp );

    return 0;
}