#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "linkedstack.h"
#include "infix2posfix.c"
#include "infix2prefix.c"
#include "classify_equation.c"
#include "solve-posfix.c"
#include "linkedstack.c"

int main() {
	int menu = 0;
	do{
		printf("\n1.Infixa para Posfixa \n");
		printf("\n2.Infixa para Prefixa \n");
		printf("\n3.Validar Posfixa \n");
		printf("\n4.Resolve Posfixa \n");
		printf("\n5.Sair \n");
		scanf("\n%d\n", menu);
		switch( menu ){
			case 1:
				infix_to_posfix();
				break;
			case 2:
				infix_to_prefix();
				break;
			case 3:
				classify();
				break;
			case 4:
				solve_posfix();
				break;
			case 5:
				printf("\n\nSaindo\n\n");
				exit(0);
			default:
				printf("escolha uma acao valida");
		}
	}while( menu != 5 );
//    struct node* head = NULL;
//    int size, element;
//    int counter = 0;
//
//    scanf("%d",&size);
//
//    init_stack(head);
//
//    while(counter < size) {
//        scanf("%d",&element);
//        head = push_in_stack(head,element);
//        // display_stack(head);
//        counter++;
//    }
//
//    while( is_stack_empty(head) == 0 ) {
//        head = pop_stack(head,&element);
//        display_stack(head);
//    }
//
//    is_stack_empty( head );
//
//    return 0;
}
