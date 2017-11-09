#include <stdio.h>
#include <stdlib.h>
#include "linkedstack.h"
#include <string.h>
#include <stdbool.h>
#define flag '#'

bool is_an_operator(char c)
{
	return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '$');
}

void reverse(char *string)
{
	int length, c;
	char *begin, *end, temp;

	length = strlen(string);
	begin = string;
	end = string;

	for (c = 0; c < length - 1; c++)
		end++;

	for (c = 0; c < length / 2; c++)
	{
		temp = *end;
		*end = *begin;
		*begin = temp;

		begin++;
		end--;
	}
}

int string_length(char *pointer)
{
	int c = 0;

	while (*(pointer + c) != '\0')
		c++;

	return c;
}

int main()
{

	struct node *head = NULL;

	char prefix[30], nada;

	char postfix[50];
	printf("Digite uma expressão:");
	scanf("%s%*c", postfix);

	int i, j = 0;

	init_stack(head);

	for (i = strlen(postfix) - 1; i >= 0; i--)
	{
		if (is_an_operator(postfix[i]))
			head = push_in_stack(head, postfix[i]);
		else
		{

			// printf("-->%c<---\n", postfix[i]);

			prefix[j++] = postfix[i];

			// printf("-->%s<---\n", prefix);

			while (is_stack_empty(head) == 0 && get_value(head) == flag)
			{
				head = pop_stack(head, &nada);
				prefix[j++] = get_value(head);
				head = pop_stack(head, &nada);
			}
			head = push_in_stack(head, flag);
		}
	}
	// prefix[j] = 0;
	// reverse(prefix, prefix + len);
	// cout<<"The prefix expression is: "<<prefix;
	reverse( prefix);
	printf("%s\n", prefix );

	return 0;
}
