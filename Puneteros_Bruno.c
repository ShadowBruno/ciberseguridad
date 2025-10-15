#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node *antes;
    struct Node *despues;
} Node;

Node* create_node(int value) {
    Node *n = (Node*)malloc(sizeof(Node));
    if (!n) {
        fprintf(stderr, "Error: malloc falló\n");
        exit(EXIT_FAILURE);
    }
    n->data = value;
    n->antes = n->despues = NULL;
    return n;
}

void push_front(Node **head, int value) {
    Node *n = create_node(value);
    if (*head == NULL) {
        *head = n;
        return;
    }
    n->despues = *head;
    (*head)->antes = n;
    *head = n;
}

void push_back(Node **head, int value) {
    Node *n = create_node(value);
    if (*head == NULL) {
        *head = n;
        return;
    }
    Node *cur = *head;
    while (cur->despues) cur = cur->despues;
    cur->despues = n;
    n->antes = cur;
}

Node* find(Node *head, int value) {
    Node *cur = head;
    while (cur) {
        if (cur->data == value) return cur;
        cur = cur->despues;
    }
    return NULL;
}

void insert_after(Node *target, int value) {
    if (!target) return;
    Node *n = create_node(value);
    n->despues = target->despues;
    n->antes = target;
    target->despues = n;
    if (n->despues) n->despues->antes = n;
}

bool delete_value(Node **head, int value) {
    Node *to_delete = find(*head, value);
    if (!to_delete) return false;
    if (to_delete->antes) to_delete->antes->despues = to_delete->despues;
    else *head = to_delete->despues; 
    if (to_delete->despues) to_delete->despues->antes = to_delete->antes;
    free(to_delete);
    return true;
}

void print_forward(Node *head) {
    Node *cur = head;
    printf("Forward: ");
    while (cur) {
        printf("%d", cur->data);
        if (cur->despues) printf(" -> ");
        cur = cur->despues;
    }
    printf("\n");
}

void print_backward(Node *head) {
    if (!head) {
        printf("Backward: (empty)\n");
        return;
    }
    Node *cur = head;
    while (cur->despues) cur = cur->despues;
    printf("Backward: ");
    while (cur) {
        printf("%d", cur->data);
        if (cur->antes) printf(" -> ");
        cur = cur->antes;
    }
    printf("\n");
}

void free_list(Node **head) {
    Node *cur = *head;
    while (cur) {
        Node *next = cur->despues;
        free(cur);
        cur = next;
    }
    *head = NULL;
}


int main(void) {
    Node *head = NULL;


    push_back(&head, 10);
    push_back(&head, 20);
    push_front(&head, 5);
    push_back(&head, 30);
    print_forward(head);  
    print_backward(head);  

    Node *n10 = find(head, 10);
    insert_after(n10, 15);
    print_forward(head); 

    if (delete_value(&head, 20)) {
        printf("Se eliminó 20\n");
    } else {
        printf("20 no encontrado\n");
    }
    print_forward(head);   

    // Buscar
    if (find(head, 15)) printf("15 encontrado\n");
    else printf("15 no encontrado\n");

    free_list(&head);
    return 0;
}