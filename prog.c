#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "linked_list.h"

int main(void) {
    List l = new_list();
    push(l, new_node(1));
    push(l, new_node(2));
    push(l, new_node(3));

    int res = pop(l);
    printf("res: %d\n", res);

    print_list(l);
    free_list(l);

    return 0;
}