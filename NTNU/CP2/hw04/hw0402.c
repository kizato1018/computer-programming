#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <getopt.h>

struct _sJpgHeader
{
    uint16_t	SOI;
    uint16_t	APP0;
    uint16_t	length;
    char	    JFIF[5];
    uint8_t	    version[2];
    uint8_t	    unit;
    uint16_t	Xdensity;
    uint16_t	Ydensity;
    uint8_t	    Xthumbnail;
    uint8_t	    Ythumbnail;
}__attribute__((__packed__));

struct _sBmpHeader
{
    char		bm[2];
    uint32_t	size;
    uint32_t	reserve;
    uint32_t	offset;
    uint32_t	header_size;
    int32_t	    width;
    int32_t	    height;
    uint16_t	planes;
    uint16_t	bpp;
    uint32_t	compression;
    uint32_t	bitmap_size;
    uint32_t	hres;
    uint32_t	vres;
    uint32_t	used;
    uint32_t	important;
}__attribute__((__packed__));

typedef struct _sJpgHeader sJpgHeader;
typedef struct _sBmpHeader sBmpHeader;

void BmpHeaderSetup(sBmpHeader *header, const uint32_t width, const uint32_t height) {
    (*header).bm[0] = 'B', (*header).bm[1] = 'M';
    (*header).reserve = 0;
    (*header).offset = 54;
    (*header).header_size = 40;
    (*header).width = width;
    (*header).height = height;
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

void JpgHeaderSetup(sJpgHeader *header, const uint8_t width, const uint8_t height) {
    uint16_t tmp;
    (*header).length = width * height * 3 + 16;
    (*header).Xthumbnail = width;
    (*header).Ythumbnail = height;
    tmp = (*header).length % 256;
    (*header).length >>= 8;
    tmp <<= 8;
    (*header).length |= tmp;

}

struct option long_options[] = 
{  
     { "write",  0, NULL, 'w' },  
     { "extract", 0, NULL, 'e' }, 
     {  0, 0, 0, 0},  
};


int main(int argc, char *argv[]) {
    FILE *jpg = NULL;
    FILE *bmp = NULL;
    FILE *temp = NULL;
    char *jpg_name = NULL;
    char *bmp_name = NULL;
    sJpgHeader jpg_header;
    sBmpHeader bmp_header;
    uint8_t *buffer = NULL;
    int index = 0;
    char opt;
    int8_t mode = 0;

    if(argc != 4) {
        printf("error argument\n");
        return 0;
    }
    opt = getopt_long(argc, argv, "we", long_options, &index);
    switch(opt) {
        case 'w': // write
            printf("write\n");
            mode = 1;
            break;
        case 'e': //extract
            printf("extract\n");
            mode = 2;
            break;
        default:
            printf("no this option\n");
            break;
    }
    jpg_name = argv[2];
    bmp_name = argv[3];
    
    if(mode == 1) {
        if((jpg = fopen(jpg_name, "rb")) == NULL) {
        printf("jpg file opened error\n");
        return 1;
        }
        if((bmp = fopen(bmp_name, "rb")) == NULL) {
            printf("bmp file opened error\n");
            return 1;
        }
        if((temp = fopen("temp.jpg", "wb")) == NULL) {
            printf("temp file opened error\n");
            return 1;
        }

        uint64_t cur = 0 ,size = 0;
        fread(&jpg_header, sizeof(sJpgHeader), 1, jpg);
        fread(&bmp_header, sizeof(sBmpHeader), 1, bmp);
        fseek(jpg, jpg_header.Xthumbnail*jpg_header.Ythumbnail*3, SEEK_CUR);
        cur = ftell(jpg);
        fseek(jpg, 0, SEEK_END);
        size = ftell(jpg) - cur;
        printf("%d %d\n", cur, size);
        buffer = calloc(bmp_header.bitmap_size, sizeof(uint8_t));
        if(buffer == NULL) {
            printf("error\n");
            return 1;
        }
        else printf("ok");
        fread(buffer, bmp_header.bitmap_size, 1, bmp);
        JpgHeaderSetup(&jpg_header, bmp_header.width, bmp_header.height);
        fwrite(&jpg_header, sizeof(sJpgHeader), 1, temp);
        uint8_t t;
        uint32_t X = bmp_header.width * 3;
        uint32_t Y = bmp_header.height;
        for(uint64_t y = 0; y < Y/2; ++y)
            for(uint64_t x = 0; x < X; x += 3) {
                for(uint32_t z = 0; z < 3; ++z) {
                    t = buffer[x+y*X+z];
                    buffer[x+y*X+z] = buffer[x+(Y-y-1)*X+2-z];
                    buffer[x+(Y-y-1)*X+2-z] = t;
                }
            }
        fwrite(buffer, bmp_header.bitmap_size, 1, temp);
        free(buffer);
        buffer = calloc(size, sizeof(uint8_t));
        fseek(jpg, cur, SEEK_SET);
        fread(buffer, size, 1, jpg);
        fwrite(buffer, size, 1, temp);
        if(remove(jpg_name) != 0) {
            printf("replace error\n");
            return 1;
        }
        if(rename("temp.jpg", jpg_name) != 0) {
            printf("replace error\n");
            return 1;
        }

    }
    else if(mode == 2) {
        if((jpg = fopen(jpg_name, "rb")) == NULL) {
        printf("jpg file opened error\n");
        return 1;
        }
        if((bmp = fopen(bmp_name, "wb")) == NULL) {
            printf("bmp file opened error\n");
            return 1;
        }
        uint64_t size = 0;
        fread(&jpg_header, sizeof(sJpgHeader), 1, jpg);
        BmpHeaderSetup(&bmp_header, jpg_header.Xthumbnail, jpg_header.Ythumbnail);
        fwrite(&bmp_header, sizeof(bmp_header), 1, bmp);
        size = jpg_header.Xthumbnail*jpg_header.Ythumbnail*3;
        buffer = calloc(size, sizeof(uint8_t));
        fread(buffer, size, 1, jpg);
        uint8_t t;
        uint32_t X = jpg_header.Xthumbnail * 3;
        uint32_t Y = jpg_header.Ythumbnail;
        for(uint64_t y = 0; y < Y/2; ++y)
            for(uint64_t x = 0; x < X; x += 3) {
                for(uint32_t z = 0; z < 3; ++z) {
                    t = buffer[x+y*X+z];
                    buffer[x+y*X+z] = buffer[x+(Y-y-1)*X+2-z];
                    buffer[x+(Y-y-1)*X+2-z] = t;
                }
            }
        fwrite(buffer, size, 1, bmp);
        free(buffer);
    }


    fclose(jpg);
    fclose(bmp);
    
}