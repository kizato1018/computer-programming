#include "fin03.h"

// typedef struct _sMatrix{
//     int x;
//     int y;
//     int row_num;
//     int col_num;
//     int value;
//     struct list_head Clist;
//     struct list_head Rlist;
// } sMatrix;


sMatrix *newNode(int a, int b, int val) {
    sMatrix *newN = calloc(1, sizeof(sMatrix));
    newN->x = a;
    newN->y = b;
    newN->value = val;
    newN->Clist.next = &(newN->Clist);
    newN->Clist.prev = &(newN->Clist);
    newN->Rlist.next = &(newN->Rlist);
    newN->Rlist.prev = &(newN->Rlist);

    return newN;
}

void free_matrix(sMatrix *m) {
    if(m == NULL) return;

    struct list_head *Rhead = &(m->Rlist);
    struct list_head *Rindex = NULL;
    struct list_head *Chead = NULL;
    struct list_head *Cindex = NULL;
    list_for_each(Rindex, Rhead) {
        sMatrix *row = list_entry(Rindex, sMatrix, Rlist);
        // printf("y = %d\n", row->y);
        Chead = &(row->Clist);
        list_for_each(Cindex, Chead) {
            sMatrix *node = list_entry(Cindex, sMatrix, Clist);
            if(Cindex->prev != Chead) {
                list_del(Cindex->prev);
                free(node);
            }
        }
        list_del(Chead);
        if(Rindex->prev != Rhead) {
            list_del(Rindex->prev);
            free(row);
        }
    }
    list_del(Rhead);
}

void set_matrix(sMatrix *m, int a, int b, int val) {
    if(m == NULL) return;
    // int row = -1, next_row = -1;
    int flag = 0;
    struct list_head *Rhead = &(m->Rlist);
    struct list_head *Rindex = NULL;
    struct list_head *Chead = NULL;
    struct list_head *Cindex = NULL;
    list_for_each(Rindex, Rhead) {
        sMatrix *row = list_entry(Rindex, sMatrix, Rlist);
        // printf("row.y = %d, b = %d\n", row->y, b);
        if(row->y == b) {
            Chead = &(row->Clist);
            list_for_each(Cindex, Chead) {
                sMatrix *node = list_entry(Cindex, sMatrix, Clist);
                if(node->x == a) {
                    node->value = val;
                    return;
                }
                else if(node->x > a) {
                    sMatrix *newMatrix = newNode(a, b, val);
                    list_add_tail(&(newMatrix->Clist), Cindex);
                    flag = 1;
                    return;
                    // printf("1 y = %d\n", b);
                }
            }
            if(flag == 0) {
                sMatrix *newMatrix = newNode(a, b, val);
                list_add_tail(&(newMatrix->Clist), Cindex);
                flag = 1;
                return;
                // printf("1 y = %d\n", b);
            }
        }
        else if(row->y > b) {
            sMatrix *newRow = newNode(-1, b, -1);
            sMatrix *newMatrix = newNode(a, b, val);
            Cindex = &(newRow->Clist);
            list_add_tail(&(newRow->Rlist), Rindex);
            list_add(&(newMatrix->Clist), Cindex);
            flag = 1;
            return;
        }
    }
    if(flag == 0) {
        sMatrix *newRow = newNode(-1, b, -1);
        sMatrix *newMatrix = newNode(a, b, val);
        Rindex = Rhead;
        Cindex = &(newRow->Clist);
        list_add_tail(&(newRow->Rlist), Rindex);
        list_add_tail(&(newMatrix->Clist), Cindex);
        return;
        // printf("2 y = %d\n", newRow->y);
    }
}

void init_matrix(sMatrix *m, int row_num, int col_num) {
    m->x = -1;
    m->y = -1;
    m->row_num = row_num;
    m->col_num = col_num;
    m->value = -1;
    m->Clist.next = &(m->Clist);
    m->Clist.prev = &(m->Clist);
    m->Rlist.next = &(m->Rlist);
    m->Rlist.prev = &(m->Rlist);

    for(int32_t i = 0; i < row_num; ++i) {
        for(int32_t j = 0; j < col_num; ++j) {
            // printf("cnt: %d, ", cnt);
            set_matrix(m, j, i, 0);
        }
    }
    return;
}

void print_matrix(sMatrix *m) {
    if(m == NULL) {
        printf("m = NULL\n");
        return;
    }
    // int row = -1, next_row = -1;

    struct list_head *Rhead = &(m->Rlist);
    struct list_head *Rindex = NULL;
    struct list_head *Chead = NULL;
    struct list_head *Cindex = NULL;
    if(Rhead->next == NULL) {
        printf("Rhead = NULL\n");
        return;
    }
    list_for_each(Rindex, Rhead) {
        sMatrix *row = list_entry(Rindex, sMatrix, Rlist);
        // printf("y = %d\n", row->y);
        Chead = &(row->Clist);
        list_for_each(Cindex, Chead) {
            sMatrix *node = list_entry(Cindex, sMatrix, Clist);
            printf("(%d,%d,%d)\n", node->x, node->y, node->value);
        }
    }
}

int add_matrix(sMatrix *output, sMatrix a, sMatrix b) {
    // if(output == NULL) return -1;
    // if(a.col_num != b.col_num || a.row_num != b.row_num) return -1;

    // init_matrix(output, a.row_num, a.col_num);
    // struct list_head *aRhead = &(a.Rlist);
    // struct list_head *aRindex = NULL;
    // struct list_head *aChead = NULL;
    // struct list_head *aCindex = NULL;
    // struct list_head *bRhead = &(b.Rlist);
    // struct list_head *bRindex = NULL;
    // struct list_head *bChead = NULL;
    // struct list_head *bCindex = NULL;
    // struct list_head *outCindex = NULL;
    // struct list_head *outCindex = NULL;
    // if(aRhead->next == NULL || bRhead->next == NULL) {
    //     printf("Rhead = NULL\n");
    //     return -1;
    // }
    // list_for_each(aRindex, aRhead) {
    //     sMatrix *arow = list_entry(aRindex, sMatrix, Rlist);
    //     sMatrix *brow = list_entry(bRindex, sMatrix, Rlist);
    //     sMatrix *outrow = list_entry(bRindex, sMatrix, Rlist);
    //     // printf("y = %d\n", row->y);
    //     aChead = &(arow->Clist);
    //     bChead = &(brow->Clist);
    //     list_for_each(aCindex, aChead) {
    //         sMatrix *anode = list_entry(aCindex, sMatrix, Clist);

    //     }
    //     list_for_each(aCindex, aChead) {
    //         sMatrix *bnode = list_entry(bCindex, sMatrix, Clist);
    //         printf("(%d,%d,%d)\n", node->x, node->y, node->value);
    //     }
    // }

}
