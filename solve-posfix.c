// C program to evaluate value of a postfix expression
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "linkedstack.h"



char solve_expression(char value_a, char value_b, char operation)
{

    int val1 = value_a - '0';
    int val2 = value_b - '0';
    switch (operation)
    {
    case '+':
        return val2 + val1 + '0';
        break;
    case '-':
        return val2 - val1 + '0';
        break;
    case '*':
        return val2 * val1 + '0';
        break;
    case '/':
        return val2 / val1 + '0';
        break;
    }
    return '0';
}

char solvePostfixStack(struct node *head)
{
    char out;
    while (is_stack_empty(head) == 0)
    {
        head = pop_stack(head, &out);
        if (!isdigit(out) && out != '(' && out != ')' && out != ' ')
        {
            char val1, val2;
            head = pop_stack(head, &val1);
            head = pop_stack(head, &val2);
            head = push_in_stack(head, solve_expression( val1, val2, out ) );
            display_stack( head );
        }
    }
    printf( "%c\n", out );
    return out;
}

// The main function that returns value of a given postfix expression
struct node * evaluatePostfix(char *exp, struct node *head)
{
    int i;

    // // Scan all characters one by one
    for (i = 0; exp[i]; ++i)
    {
        // If the scanned character is an operand (number here),
        // push it to the stack.
        if (exp[i] == ' '){
        }
        else {
            head = push_in_stack(head, exp[i]); // Transforma a string no numero
        }
    }
    return head;
}

// Driver program to test above functions
int main()
{

    struct node *head = NULL;

    init_stack(head);

    char exp[] = "1 3 3 + +";

    head = evaluatePostfix(exp, head);
    display_stack(head);

    // printf("Value of %s is %d\n", exp, solvePostfixStack(head));
    solvePostfixStack(head);
    // char test = solve_expression( '2', '4', '*' );


    return 0;
}