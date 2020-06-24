#include "matrix.h"

int main() {
    
    sMatrix M;
    init_matrix(&M, 100, 200);
    
    set_matrix(&M, 0, 0, 1);
    set_matrix(&M, 99, 0, 2);
    set_matrix(&M, 99, 199, 3);
    print_matrix(&M);
    free_matrix(&M);
}
