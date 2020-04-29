#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

struct _sBmpHeader
{
    char		bm[2];
    uint32_t	size;
    uint32_t	reserve;
    uint32_t	offset;
    uint32_t	header_size;
    uint32_t	width;
    uint32_t	height;
    uint16_t	planes;
    uint16_t	bpp;
    uint32_t	compression;
    uint32_t	bitmap_size;
    uint32_t	hres;
    uint32_t	vres;
    uint32_t	used;
    uint32_t	important;
}__attribute__ ((__packed__));

typedef struct _sBmpHeader sBmpHeader;




int main()
{
    FILE	*pFile = NULL;
    FILE	*pFile2 = NULL;
    
    if( ( pFile = fopen( "maldives.bmp", "rb" ) ) == NULL )
    {
        printf( "File could not be opened!\n" );
        return 0;
    }
    
    if( ( pFile2 = fopen( "maldives_x2.bmp", "wb" ) ) == NULL )
    {
        printf( "File could not be opened!\n" );
        return 0;
    }
    
    sBmpHeader	header;
    fread( &header, sizeof( header ), 1, pFile );
     header.width *= 2;
     header.height *= 2;
     header.bitmap_size *= 4;
     header.size = header.bitmap_size + header.offset;
    fwrite( &header, sizeof( header ), 1, pFile2 );

    while( !feof( pFile ) )
    {
        uint8_t	original[6000] = {0};
        uint8_t modified[12000] = {0};
        
        size_t count = fread( original, 1, header.width/2*3, pFile );
        for( size_t i = 0; i < count ; i += 3)
        {
            for(size_t j = 0; j < 3; j++) {
                modified[i*2+j] = original[i+j];
                modified[i*2+j+3] = original[i+j];
            }  
        }
        fwrite( modified, header.width*3, 1, pFile2 );
        fwrite( modified, header.width*3, 1, pFile2 );
    }
    
                
    fclose( pFile );
    fclose( pFile2 );
    
    return 0;
}