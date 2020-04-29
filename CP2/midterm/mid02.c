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
}__attribute__((__packed__));

typedef struct _sBmpHeader sBmpHeader;


int main()
{
    FILE *pFile = NULL;
    FILE *pFile2 = NULL;
    char inputName[256];
    char outputName[256];
    
    printf("Please enter the input image name: ");
    scanf("%s", inputName);

    if( ( pFile = fopen( inputName, "rb" ) ) == NULL )
    {
        printf( "File could not be opened!\n" );
        return 0;
    }
    
    printf("Please enter the output image name: ");
    scanf("%s", outputName);

    if( ( pFile2 = fopen( outputName, "wb" ) ) == NULL )
    {
        printf( "File could not be opened!\n" );
        return 0;
    }
    sBmpHeader	header;
    fread( &header, sizeof( header ), 1, pFile );
    if(header.bm[0] != 'B' || header.bm[1] != 'M') {
        printf("Warning: This might not be a BMP file.");
    }
    header.bitmap_size = header.bitmap_size / 3 * 2;
    header.bpp = 16;
    fwrite( &header, sizeof( header ), 1, pFile2 );

    while( !feof( pFile ) )
    {
        uint8_t original[999] = {0};
        uint16_t modified[999] = {0};
        uint16_t tmp = 0;
        size_t count = fread( original, 1, 999, pFile );
        // if(abc > 0)
        //     for(int i = 0; i < 3; i++) {
        //         printf("%d\n", original[i]);
        //     }

        for( size_t i = 0 ; i < count ; i++)
        {
            if(i % 3 == 0) {
                // tmp = original[i];
                // tmp = ((tmp >> 3) << 11);
				modified[i/3] += (((uint16_t)original[i] >> 3));
                // if(abc > 0) {
                //     printf("|%d|\n", modified[0]);
                // }
			}
			else if(i % 3 == 1) {
				modified[i/3] += (((uint16_t)original[i] >> 3) << 5);
                // if(abc > 0) {
                //     printf("|%d|\n", modified[0]);
                // }
			}
			else if(i % 3 == 2) {
				modified[i/3] += (((uint16_t)original[i] >> 4) << 11);
                // if(abc > 0) {
                //     abc = 0;
                //     printf("|%d|\n", modified[0]);
                // }
			}
        }
        
        fwrite( modified, count * 2 / 3, 1, pFile2 );
        
    }
    
                
    fclose( pFile );
    fclose( pFile2 );
    
    return 0;
}
// 11010001
//
// 00011010
// 01010011
// 00011001
// 0001101010000011
// 00110100
// 11010110
// 00110011
// 1101011000110100


// 01010 011000 11010
// 11010001
// 11000110
// 10100000