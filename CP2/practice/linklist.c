#include <stdio.h>
#include <stdlib.h>

typedef struct _List {
    int value;
    struct _List* next;
}List;

void add(List* L, int new) {
    List *n = calloc(1, sizeof(List));
    n->value = new;
    n->next = NULL;
    if(L == NULL) 
        L = n;
    else
        L->next = n;
    return;
}

void delete(List* L, int val) {
    List* cur = L;
    if(cur == NULL) return;
    List* next = cur->next;
    if(cur->value == val) {
        L = next;
        free(cur);
        cur = L;
        next = next->next;
    }  

    while(next) {
        if(next->value == val) {
            cur = next->next;
            free(next);
            next = cur->next;
        }
        else {
            cur = next;
            next = next->next;
        }
    }

}

int main() {
    List l;
    int ll[100][2] = {{30,1}, {40, 2}, {50, -1}};

}