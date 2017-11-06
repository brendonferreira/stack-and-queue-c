/*
* File: stack.c
* Author:  zentut.com
* Purpose: linked stack implementation
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "linkedstack.h"
/*
    init the stack
*/
void init_stack(struct node *head)
{
    head = NULL;
}

/*
    push an element into stack
*/
struct node *push_in_stack(struct node *head, char data)
{

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
struct node *pop_stack(struct node *head, char *element)
{
    struct node *tmp = head;
    *element = head->data;
    head = head->next;
    free(tmp);
    return head;
}


int is_stack_empty(struct node *head){
    return head == NULL ? 1 : 0;
}

/*
    display the stack content
*/
void display_stack(struct node *head)
{
    struct node *current;
    current = head;
    if (current != NULL) {
        do {
            printf("%c ", current->data);
            current = current->next;
        } while (current != NULL);
        printf("\n");
    } else {
        printf("essa porra ta vazia\n");
    }
}


char get_value( struct node *head ) {
    return head->data;
}