#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "linked_list.h"

List new_list() {
    List new_l = malloc(sizeof(struct list));
    new_l->head = NULL;
    new_l->tail = NULL;
    new_l->size = 0;

    return new_l;
}

Node new_node(int data) {
    Node new = malloc(sizeof(struct node));
    new->data = data;
    new->next = NULL;

    return new;
}

void push(List l, Node n) {
    if (l->head == NULL) {
        l->head = n;
    } else {
        l->tail->next = n;
    }
    l->tail = n;
    l->size++;

}

int pop(List l) {
    assert(l->head != NULL);
    int head_data = l->head->data;
    Node tmp = l->head->next;
    free(l->head);
    l->head = tmp;
    l->size--;
    assert(l->size >= 0);
    if (l->size == 0) {
        l->tail = NULL;
    }

    return head_data;
}

void free_list(List l) {
    for (Node curr = l->head; curr != NULL;) {
        Node tmp = curr->next;
        free(curr);
        curr = tmp;
    }
    free(l);
}

void print_list(List l) {
    for (Node curr = l->head; curr != NULL; curr = curr->next) {
        printf("%d -> ", curr->data);
    }
    printf("X\n");
}

