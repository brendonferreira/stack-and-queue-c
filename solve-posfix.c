#include <stdio.h>
#include "linkedstack.h"

char solve_expression(char value_a, char value_b, char operation) {

    int val1 = (int) value_a - '0'; //- '0';
	int val2 = (int) value_b - '0'; //- '0';
	
    switch (operation)
    {
    case '+':
        return (char) ( val2 + val1 ) + 48;
        break;
    case '-':
        return (char) ( val2 - val1 ) + 48;
        break;
    case '*':
        return (char) ( val2 * val1 ) + 48;
        break;
    case '/':
        return (char) ( val2 / val1 ) + 48;
        break;
	default:
		return '0';
		break;
	}

    return '0';
}

int main() {
	struct node *head = NULL;
	char exp[20];
	char n1, n2, n3;
	printf("Entre com a expressão pós fixa:");
	scanf("%s", exp);

	init_stack(head);

	for (int i = 0; exp[i] != '\0' ; ++i) {
	
		if (isdigit(exp[i])){
			head = push_in_stack( head, exp[i] );
		} else {
			head = pop_stack( head, &n1 );
			head = pop_stack( head, &n2 );
			n3 = solve_expression( n1, n2, exp[i] );
			head = push_in_stack( head, n3);
		} 
	}

	printf("\nThe result of expression %s  =  %c\n\n", exp, head->data);
	
	return 0;
}
