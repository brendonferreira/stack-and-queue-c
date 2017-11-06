#include <stdio.h>
#include "linkedstack.h"

int main() {
    struct node* head = NULL;
    int size, element;
    int counter = 0;

    scanf("%d",&size);

    init_stack(head);

    while(counter < size) {
        scanf("%d",&element);
        head = push_in_stack(head,element);
        // display_stack(head);
        counter++;
    }

    while( is_stack_empty(head) == 0 ) {
        head = pop_stack(head,&element);
        display_stack(head);
    }

    return 0;
}
