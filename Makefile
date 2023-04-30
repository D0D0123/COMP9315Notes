CC=gcc

app: linked_list.c linked_list.h hash_table.c
	$(CC) linked_list.c linked_list.h hash_table.c -o app -lm -g