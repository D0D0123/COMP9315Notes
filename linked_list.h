struct node {
    int data;
    struct node* next;
};

typedef struct node* Node;

struct list {
    Node head;
    Node tail;
    int size;
};

typedef struct list* List;

List new_list();
Node new_node(int data);
void push(List l, Node n);
int pop(List l);
void free_list(List l);
void print_list(List l);
