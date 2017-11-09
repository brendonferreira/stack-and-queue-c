#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "linkedstack.h"
#include <ctype.h>
#define flag '#'

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

char * infix_to_posfix( char exp[] ){
    struct node *head = NULL;

    int k, i;
    char x;

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
                printf("Expressao invalida!");
                // return -1;          
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
	
	return exp;
}

/*
    init the stack
*/
void init_stack(struct node *head) {
    head = NULL;
}

/*
    push an element into stack
*/
struct node *push_in_stack(struct node *head, char data) {

    struct node *tmp = (struct node *)malloc(sizeof(struct node));
    if (tmp == NULL)
    {
        exit(0);
    }
    tmp->data = data;
    tmp->next = head;
    head = tmp;
    return head;
}
/*
    pop an element from the stack
*/
struct node *pop_stack(struct node *head, char *element) {
    struct node *tmp = head;
    *element = head->data;
    head = head->next;
    free(tmp);
    return head;
}

int is_stack_empty(struct node *head) {
    return head == NULL ? 1 : 0;
}

/*
    display the stack content
*/
void display_stack(struct node *head) {
    struct node *current;
    current = head;
    if (current != NULL)
    {
        do
        {
            printf("%c ", current->data);
            current = current->next;
        } while (current != NULL);
        printf("\n");
    }
    else
    {
        printf("pilha vazia\n");
    }
}

char get_value(struct node *head) {
    return head->data;
}

bool is_an_operator(char c) {
    return (c=='+' || c=='-' || c=='*' || c=='/' || c=='^' || c=='$');
}

char * posfix_to_prefix( char postfix[] ){

    struct node *head = NULL;

	char * prefix = malloc (sizeof (char) * 30);
	char nada;
 
	int i, j=0;
    
    init_stack( head );

	for( i = strlen(postfix) - 1 ; i>=0 ; i-- ) {
		if(is_operator(postfix[i]))
            head = push_in_stack( head, postfix[i] );
        else {
        
            prefix[j++] = postfix[i];
        
			while( is_stack_empty(head) == 0 && get_value(head) == flag){
				head = pop_stack( head, &nada);
				prefix[j++] = get_value( head ) ; 
				head = pop_stack( head, &nada);
			}
			head = push_in_stack( head, flag);
		
		}
	}

    return prefix;
}

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

int solve_posfix() {
	struct node *head = NULL;
	int i;
	char exp[50];
	char n1, n2, n3;
	printf("Entre com a expressao pos fixa:");
	fgets(exp, 50, stdin);

	init_stack(head);

	for ( i = 0; exp[i] != '\0' ; ++i) {
	
		if (isdigit(exp[i])){
			head = push_in_stack( head, exp[i] );
		} else {
			head = pop_stack( head, &n1 );
			head = pop_stack( head, &n2 );
			n3 = solve_expression( n1, n2, exp[i] );
			head = push_in_stack( head, n3);
		} 
	}

	printf("\nResultado da expressao %s  =  %c\n\n", exp, head->data);
	
	return 0;
}

bool have_parentesis( char * string ){
	int i;
	for( i = 0; i <= strlen(string) ; i++){
	  if( string[i] == '(' ) {
		return true;
	  }
	}
	return false;
  }
  
  char * subString(char *string, int position, int length) {
	 char * pointer;
	 int c;
   
	 pointer = malloc(length+1);
	 if (pointer == NULL){
		printf("Nao foi possivel alocar a memoria necessaria.\n");
		exit(1);
	 }
	 for (c = 0 ; c < length ; c++){
		*(pointer+c) = *(string+position-1);      
		string++;   
	 }
	 *(pointer+c) = '\0';
	 return pointer;
  }
  
  char * separate_parent_parentesis( char * equation ){
	int open_parentesis_position = -1 ;
	int closures_counter = 0;
	int count;
	for( count = 0; count < strlen( equation ); count++ ){
	  if( equation[count] != '\040' ){
		if( equation[count] == '(' ){
		  closures_counter++;
		  if( open_parentesis_position < 0 ){
			open_parentesis_position = count + 2;
		  }
		} else if( equation[count] == ')' ){
		  closures_counter--;
		  if( closures_counter == 0 && open_parentesis_position > -1 ){
			char * part = subString( equation, open_parentesis_position, (count + 1) - open_parentesis_position );
			return part;
		  }
		}
	  }
	}
	return equation;
  }
  
  int indexOf ( char * str, char * toFind ){
	char *result = strstr(str, toFind);
	int position = result - str;
	return position;
  }
  
  char * classify_equation ( char * equation , char * classification, int position, int * index ) {
	  
	if( have_parentesis( equation ) ){
	  char * separated_parentesis = separate_parent_parentesis( equation ); 
	  classify_equation( separated_parentesis, classification, position + indexOf( equation, separated_parentesis ), index );
	} 
	
	int i;
	// find multi/division
	for( i = 0; i < strlen(equation); i++){	
	  if( classification[ i + position] == '\040' ){
		if(equation[i] == '*'|| equation[i] == '/'){
			*index = *index + 1;
		  classification[i + position] = *index + 48;
		}
	  }
	}
  
	// find add/sub
	for( i = 0; i < strlen(equation) ; i++){	
	  if( classification[i + position] == '\040' ){
		if(equation[i] == '-'|| equation[i] == '+'){
		  *index = *index + 1;
			classification[i + position] = *index + 48;
		}
	  }
	}
  
  }
  
  
  
  int classify(){
	int index = 0;
	int i;
	char * equation;
  
	printf("Digite uma expressao matematica valida:\n");
	scanf("%m[^\n]", &equation);
  
	char * classification = (char *) malloc( strlen( equation ) * sizeof("a") );
  
	for( i = 0; i < strlen( equation ) * sizeof("a") ; i++){	
		classification[i] = '\040';
	}
  
	classify_equation( equation , classification, 0 , &index);
	printf( "%s\n", classification );
  }
  

int main() {
	int menu = 0;
	char expression[64];
	do{
		printf("\n1.Infixa para Posfixa \n");
		printf("\n2.Posfixa para Prefixa \n");
		printf("\n3.Resolve Posfixa \n");
		printf("\n4.Sair \n");
		scanf("%d%*c", &menu);
		switch( menu ){
			case 1:
				printf("Digite uma expressão:");
				fgets( expression, 64, stdin );
				strcpy( expression, infix_to_posfix(expression) );
				printf( "%s", expression );
				break;
			case 2:
				printf("Digite uma expressão:");
				fgets( expression, 64, stdin );
				strcpy( expression, infix_to_posfix(expression) );
				char sp[64];
				strcpy( sp, posfix_to_prefix(expression) );
				break;
			case 3:
				solve_posfix();
				break;
			case 4:
				printf("\n\nSaindo\n\n");
				exit(0);
			default:
				printf("escolha uma acao valida");
		}
	}while( menu != 5 );
}
