#include <stdio.h>
#include <stdlib.h>


typedef struct _Node {
    int value;
    struct _Node* next;
}Node;

typedef struct _List {
    int size;
    Node* head;
    Node* tail;
}List;


void add(List* Head, int new) {
    if(Head == NULL) return;
    Node *n = calloc(1, sizeof(List));
    n->value = new;
    n->next = NULL;
    if(Head->size == 0) {
        Head->head = n;
        Head->tail = n;
        ++Head->size;
    }
    else{
        Node *cur = Head->tail;
        cur->next = n;
        Head->tail = n;
        ++Head->size;
    }
    // if(L == NULL) 
    //     L = n;
    // else
    // while(cur->next != NULL)
    //     cur = cur->next;
    // cur->next = n;
    return;
}

void delete(List* Head, int val) {
    if(Head == NULL || Head->size == 0) return;
    Node* cur = Head->head;
    Node* next = cur->next;
    while(cur->value == val) {
        Head->head = next;
        free(cur);
        --Head->size;
        if(Head->head == NULL) return;
        cur = Head->head;
        next = cur->next;
    }  
    while(next != NULL) {
        if(next->value == val) {
            --Head->size;
            if(next == Head->tail) {
                Head->tail = cur;
                cur->next = NULL;
                free(next);
                return;
            }
            cur->next = next->next;
            free(next);
            next = cur->next;
        }
        else {
            cur = next;
            next = next->next;
        }
    }

}

void clear(List* Head) {
    Node* cur = Head->head;
    while(cur != NULL) {
        Head->head = cur->next;
        free(cur);
        cur = Head->head;
        --Head->size;   
    }
    Head->tail = NULL;
}

void Print(List *Head) {
    if(Head == NULL) return;
    Node* cur = Head->head;
    while(cur != NULL) {
        printf("%d --> ", cur->value);
        cur = cur->next;
    }
    printf("NULL\n");
}

int main() {
    List Head = {0, NULL};
    add(&Head, 10);
    add(&Head, 10);
    add(&Head, 20);
    add(&Head, 30);
    add(&Head, 30);
    add(&Head, 15);
    Print(&Head);
    delete(&Head, 10);
    Print(&Head);
    clear(&Head);
    Print(&Head);
}