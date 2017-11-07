#include <stdio.h>
#include <stdlib.h>
#include "linkedstack.h"
#include <string.h>
#include <stdbool.h>
#define flag '#'

bool is_operator(char c) {
    return (c=='+' || c=='-' || c=='*' || c=='/' || c=='^' || c=='$');
}

int main(){

    struct node *head = NULL;

    char prefix[30], nada;
    
    char postfix[] = "44+";

	int j=0;
    
    init_stack( head );

	for(int i = strlen(postfix) - 1 ; i>=0 ; i-- ) {
		if(is_operator(postfix[i]))
            head = push_in_stack( head, postfix[i] );
        else {
            
            printf( "-->%c<---\n", postfix[i]);
    
            prefix[j++] = postfix[i];
            
            printf( "-->%s<---\n", prefix);

    
			while( is_stack_empty(head) == 0 && get_value(head) == flag){
				head = pop_stack( head, &nada);
				prefix[j++] = get_value( head ) ; 
				head = pop_stack( head, &nada);
			}
			head = push_in_stack( head, flag);
		
		}
	}
	// prefix[j] = 0;
	// reverse(prefix, prefix + len);
    // cout<<"The prefix expression is: "<<prefix;
    
    printf( "%s\n", prefix);

	return 0;
}