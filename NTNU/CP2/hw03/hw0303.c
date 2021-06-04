#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

const uint32_t WIDTH = 128;
const uint32_t HEIGHT = 128;

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

void headerSetup(sBmpHeader *header) {
    (*header).bm[0] = 'B', (*header).bm[1] = 'M';
    (*header).reserve = 0;
    (*header).offset = 54;
    (*header).header_size = 40;
    (*header).width = WIDTH;
    (*header).height = HEIGHT;
    (*header).planes = 1;
    (*header).bpp = 24;
    (*header).compression = 0;
    (*header).bitmap_size = ((((*header).width * (*header).bpp + 31) / 32 * 4) * (*header).height);
    (*header).size = (*header).bitmap_size + (*header).offset;
    (*header).hres = 0;
    (*header).vres = 0;
    (*header).used = 0;
    (*header).important = 0;
}

typedef struct _Pixel{
    uint8_t B;
    uint8_t G;
    uint8_t R;
}Pixel;

Pixel pixel[128][128];

Pixel f(size_t x, size_t y) {
    Pixel a = pixel[0][0];
    Pixel b = pixel[HEIGHT-1][0];
    Pixel c = pixel[0][WIDTH-1];
    Pixel d = pixel[HEIGHT-1][WIDTH-1];
    Pixel r;
    r.B = (((a.B * (WIDTH-x) + c.B * x) * (HEIGHT - y) + (b.B * (WIDTH - x) + d.B * x) * y) / (WIDTH * HEIGHT));
    r.G = (((a.G * (WIDTH-x) + c.G * x) * (HEIGHT - y) + (b.G * (WIDTH - x) + d.G * x) * y) / (WIDTH * HEIGHT));
    r.R = (((a.R * (WIDTH-x) + c.R * x) * (HEIGHT - y) + (b.R * (WIDTH - x) + d.R * x) * y) / (WIDTH * HEIGHT));
    return r;
}


int main() {
    FILE *pF = NULL;
    char input[256] = {};
    fgets(input, sizeof(input), stdin);
    if(input[strlen(input)-1] == '\n')
        input[strlen(input)-1] = 0;
    if((pF = fopen(input,"wb")) == NULL) {
        printf( "File could not be opened!\n" );
        return 0;
    }
    sBmpHeader	header;
    headerSetup(&header);
    fwrite(&header, 54, 1, pF);
    printf("Please enter (R,G,B) in the top left pixel:");
    scanf("%hhd,%hhd,%hhd", &(pixel[HEIGHT-1][0].R), &(pixel[HEIGHT-1][0].G), &(pixel[HEIGHT-1][0].B));
    printf("Please enter (R,G,B) in the top right pixel:");
    scanf("%hhd,%hhd,%hhd", &(pixel[HEIGHT-1][WIDTH-1].R), &(pixel[HEIGHT-1][WIDTH-1].G), &(pixel[HEIGHT-1][WIDTH-1].B));
    printf("Please enter (R,G,B) in the bottom left pixel:");
    scanf("%hhd,%hhd,%hhd", &(pixel[0][0].R), &(pixel[0][0].G), &(pixel[0][0].B));
    printf("Please enter (R,G,B) in the bottom right pixel:");
    scanf("%hhd,%hhd,%hhd", &(pixel[0][WIDTH-1].R), &(pixel[0][WIDTH-1].G), &(pixel[0][WIDTH-1].B));
    
    for(size_t y = 0; y < HEIGHT; ++y) {
        for(size_t x = 0; x < WIDTH; ++x) {
            if((x != 0 && x != WIDTH-1) || (y != 0 && y != HEIGHT-1))
                pixel[y][x] = f(x, y);
        }
    }
    fwrite(pixel, sizeof(pixel), 1, pF);
    // fread( &b, 2, 1, pF);
    // printf("%d\n", b);

    // fread( a, 3, 1, pFile);
    // for(int i = 0; i < 3; i++) {
    //     printf("%d\n", a[i]);
    // }
            
    fclose( pF );
    
    
    return 0;
}