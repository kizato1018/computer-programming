#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

int main( int argc, char *argv[] )
{
    printf( "argc: %d\n", argc );
    
    for( int32_t i = 0 ; i < argc ; i++ )
    {
        printf( "argv[%d]: %s\n", i, argv[i] );
    }
    
    puts( "---" );
    
    // getopt
    
    int32_t c = 0;
    int a = 0;
    while ( 1 )
    {
        if(( c = getopt( argc, argv, "abc" ) ) == -1) break;
        switch( c )
        {
            case 'a':
                printf( "option: -a\n" );
                break;
            case 'b':
                printf( "option: -b\n" );
                break;
            case 'c':
                printf( "option: -c\n" );
                break;
            case '?':
                printf( "option: ?\n" );
                break;
            default:
                printf( "option: unknown\n" ); 
                break;
        }
        printf("%d", ++a);
    }
    
    return 0;
}