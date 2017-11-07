/*
* File: stack.h
* Author:  zentut.com
* Purpose: linked stack header file
*/
#ifndef LINKEDSTACK_H_INCLUDED
#define LINKEDSTACK_H_INCLUDED

struct node
{
    char data;
    struct node *next;
};

int is_stack_empty(struct node *s);

struct node* push_in_stack(struct node *s,char data);

struct node* pop_stack(struct node *s,char * data);

void init_stack(struct node* s);

void display_stack(struct node* head);

char get_value(struct node* head);

#endif // LINKEDSTACK_H_INCLUDED
