#include <stdio.h>

int main( int argc, char *argv[] ) {
    FILE *pF = NULL;
    char context[1024];

    if((pF = fopen(argv[argc-1], "rb")) == NULL) {
        perror("open file error.\n");
        return 1;
    }
    
    fgets(context, sizeof(context), pF);
    if()
    
}