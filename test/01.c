#include <stdio.h>

int main() {
    FILE *pF1 = NULL, *pF2 = NULL;
    char fileName[32] = {};

    printf( "Please enter the file name: " );	
    
    if( fgets( fileName, sizeof( fileName ), stdin ) == NULL )
    {
        printf( "Error!\n" );
        return 0;
    }

    pF1 = fopen(fileName, "w");
    pF2 = fopen(fileName, "w");
    fprintf(pF1, "Hello World\n");
    fprintf(pF2, "Nothing Happen?\n");

    printf("%p, %p\n", pF1, *pF1);

    fclose(pF1);
    fclose(pF2);   
}