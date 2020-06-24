#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "linuxlist.h"

typedef struct _sMatrix{
    int x;
    int y;
    int row_num;
    int col_num;
    int value;
    struct list_head Clist;
    struct list_head Rlist;
} sMatrix;

sMatrix *newNode(int a, int b, int val);
void free_matrix(sMatrix *m);
void set_matrix(sMatrix *m, int a, int b, int val);
void init_matrix(sMatrix *m, int row_num, int col_num);
void print_matrix(sMatrix *m);
int add_matrix(sMatrix *output, sMatrix a, sMatrix b);