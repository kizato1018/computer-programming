#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <getopt.h>

struct option long_options[] = 
{  
     { "all",  0, NULL, 'a' },  
     { "break", 0, NULL, 'b' },  
     { "cancel", 1, NULL, 'c' },  
     {  0, 0, 0, 0},  
};  

int main( int argc, char *argv[] )
{
    printf( "argc: %d\n", argc );
    
    for( int32_t i = 0 ; i < argc ; i++ )
    {
        printf( "argv[%d]: %s\n", i, argv[i] );
    }
    
    puts( "---" );
    
    // getopt_long
    
    int32_t c = 0;
    int32_t index = 0;
    
    while ( ( c = getopt_long( argc, argv, "abc:", long_options, &index ) ) != -1 )
    {
        printf( "index: %d\n", index );
        switch( c )
        {
            case 'a':
                printf( "option: -a\n" );
                break;
            case 'b':
                printf( "option: -b\n" );
                break;
            case 'c':
                printf( "option: -c, %s\n", optarg );
                break;
            case '?':
                printf( "option: ?\n" );
                break;
            default:
                printf( "option: unknown\n" ); 
                break;
        }
    }
    
    return 0;
}