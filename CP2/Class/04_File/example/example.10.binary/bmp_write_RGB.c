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

void print_bmp_header( sBmpHeader *pHeader )
{
    printf( "ID: %c%c\n", pHeader -> bm[0], pHeader -> bm[1] );
    printf( "Size: %u\n", pHeader -> size );
    printf( "Reserve: %u\n", pHeader -> reserve );
    printf( "Offset: %u\n", pHeader -> offset );
    printf( "Header Size: %u\n", pHeader -> header_size );
    printf( "Width: %u\n", pHeader -> width );
    printf( "Height: %u\n", pHeader -> height );
    printf( "Planes: %u\n", pHeader -> planes );
    printf( "Bits Per Pixel: %u\n", pHeader -> bpp );
    printf( "Compression: %u\n", pHeader -> compression );
    printf( "Bitmap Data Size: %u\n", pHeader -> bitmap_size );
    printf( "H-Resolution: %u\n", pHeader -> hres );
    printf( "V-Resolution: %u\n", pHeader -> vres );
    printf( "Used Colors: %u\n", pHeader -> used );
    printf( "Important Colors: %u\n", pHeader -> important );
    
    return;
}


int main()
{
    FILE	*pFile = NULL;
    FILE	*pFile2 = NULL;
	FILE	*pFile3 = NULL;
	FILE	*pFile4 = NULL;
    if( ( pFile = fopen( "maldives.bmp", "rb" ) ) == NULL )
    {
        printf( "File could not be opened!\n" );
        return 0;
    }
    
    if( ( pFile2 = fopen( "maldives_Blue.bmp", "wb" ) ) == NULL )
    {
        printf( "File could not be opened!\n" );
        return 0;
    }

    if( ( pFile3 = fopen( "maldives_Green.bmp", "wb" ) ) == NULL )
    {
        printf( "File could not be opened!\n" );
        return 0;
    }

    if( ( pFile4 = fopen( "maldives_Red.bmp", "wb" ) ) == NULL )
    {
        printf( "File could not be opened!\n" );
        return 0;
    }

    
    sBmpHeader	header;
    fread( &header, sizeof( header ), 1, pFile );
    fwrite( &header, sizeof( header ), 1, pFile2 );
    fwrite( &header, sizeof( header ), 1, pFile3 );
    fwrite( &header, sizeof( header ), 1, pFile4 );

    while( !feof( pFile ) )
    {
        uint8_t	original[999] = {0};
        uint8_t R[999] = {0};
		uint8_t G[999] = {0};
		uint8_t B[999] = {0};
        size_t count = fread( original, 1, 999, pFile );
		
		for(int i = 0; i < count; i++) {
			if(i % 3 == 0) {
				B[i] = original[i];
			}
			else if(i % 3 == 1) {
				G[i] = original[i];
			}
			else if(i % 3 == 2) {
				R[i] = original[i];
			}
		}
        
        fwrite( B, count, 1, pFile2 );
       	fwrite( G, count, 1, pFile3 );
        fwrite( R, count, 1, pFile4 );
    }
    
                
    fclose( pFile );
    fclose( pFile2 );
    fclose( pFile3 );
    fclose( pFile4 );
    
    return 0;
}
