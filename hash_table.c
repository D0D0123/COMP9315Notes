#include "linked_list.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>

#define MAX_TABLE_SIZE 20

struct hash_table {
    List* table;
    int sp;
    int d;
    uint32_t (*hash_func)(int);
};

typedef struct hash_table* HashTable;

uint32_t my_hash_func(int value) {
    return value % MAX_TABLE_SIZE;
}

int bits(uint32_t hash, int d) {
    uint32_t mask = 4294967295;
    mask = mask >> (32 - d);
    return hash & mask;
}

HashTable new_hash_table() {
    HashTable new = malloc(sizeof(struct hash_table));
    new->table = malloc(sizeof(List) * MAX_TABLE_SIZE);
    for (int i = 0; i < MAX_TABLE_SIZE; i++) {
        new->table[i] = new_list();
    }
    new->hash_func = &my_hash_func;
    new->sp = 0;
    new->d = 1;
}

void add(HashTable h, int value) {
    uint32_t hashres = h->hash_func(value);
    int index = bits(hashres, h->d);
    assert(index < MAX_TABLE_SIZE);
    push(h->table[index], new_node(value));
}

void print_hash_table(HashTable h) {
    printf("sp: %d\n", h->sp);
    printf("d: %d\n", h->d);
    for (int i = 0; i < MAX_TABLE_SIZE; i++) {
        printf("[%d]: ", i);
        print_list(h->table[i]);
    }
}

void free_hash_table(HashTable h) {
    for (int i = 0; i < MAX_TABLE_SIZE; i++) {
        free_list(h->table[i]);
    }
    free(h->table);
    free(h);
}

void split(HashTable h) {
    int newsp = h->sp + pow(2, h->d);
    int oldsp = h->sp;

    List list_to_split = h->table[oldsp];
    int original_size = list_to_split->size;
    int i = 0;
    while (i < original_size) {
        int val = pop(list_to_split);
        int index = bits(h->hash_func(val), h->d + 1);
        if (index == newsp) {
            push(h->table[newsp], new_node(val));
        } else {
            push(h->table[oldsp], new_node(val));
        }
        i++;
    }

    h->sp += 1;
    if (h->sp == pow(2, h->d)) {
        h->d += 1;
        h->sp = 0;
    };

    if (h->sp >= MAX_TABLE_SIZE) {
        h->sp = 0;
    }
}

int main(void) {

    HashTable h = new_hash_table();
    add(h,87);
    add(h,38);
    add(h,81);
    add(h,91);
    add(h,67);
    add(h,42);
    add(h,90);
    add(h,57);
    add(h,76);
    add(h,55);
    add(h,94);
    add(h,81);
    add(h,6);
    add(h,44);
    add(h,31);
    add(h,1);
    add(h,17);
    add(h,55);
    add(h,75);
    add(h,20);
    add(h,80);
    add(h,99);
    add(h,33);
    add(h,78);
    add(h,9);
    add(h,68);
    add(h,23);
    add(h,74);
    add(h,10);
    add(h,86);
    add(h,92);
    add(h,65);
    add(h,11);

    print_hash_table(h);

    // uint32_t h = 29;
    
    // printf("bits: %d\n", bits(h, 3));
    for (int j = 0; j < 5; j++) {
        split(h);
    }
    print_hash_table(h);

    return 0;
}