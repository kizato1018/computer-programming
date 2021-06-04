#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

struct option long_options[] = 
{  
     { "write",  0, NULL, 'w' },  
     { "extract", 0, NULL, 'e' }, 
     { "bits", 1, NULL, 'b'},
     {  0, 0, 0, 0},  
};

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

typedef struct _sBmpHeader sBmpHeader;

uint64_t util_getFdSize(int fd){
    struct stat statbuf;
    
    if( fstat( fd, &statbuf ) < 0 )
    {
        close( fd );
        return -1;
    }
    
    return statbuf.st_size;
}

int main(int argc, char *argv[]) {
    FILE *bmp = NULL;
    int32_t fbmp = 0;
    uint64_t filesize = 0;
    FILE *secret = NULL;
    char *bmp_name = NULL;
    char *secret_name = NULL;
    sBmpHeader bmp_header;
    char opt = 0;
    int32_t index = 0;
    int8_t mode = 0;
    int8_t bits = 1;
    char *map = NULL;
    uint8_t *buffer = NULL;
    if(argc < 4) {
        printf("error argument\n");
        return 0;
    }
    
    while((opt = getopt_long(argc, argv, "web:", long_options, &index)) != -1) {
        switch(opt) {
            case 'w': // write
                printf("write\n");
                mode = 1;
                break;
            case 'e': //extract
                printf("extract\n");
                mode = 2;
                break;
            case 'b':
                printf("bits=%s\n", optarg);
                if(*optarg < '1' || *optarg > '8') {
                    printf("error argument\n");
                    return 1;
                }
                bits = *optarg - '0';
                break;
            default:
                printf("no this option\n");
                break;
        }
    }
    bmp_name = argv[argc-2];
    secret_name = argv[argc-1];
    
    if(mode == 1) {
        uint32_t cnt = 0;
        uint64_t size = 0;
        uint8_t bit = 0;
        uint8_t mask = 0;
        if((bmp = fopen(bmp_name, "rb+")) == NULL) {
            printf("bmp file open error\n");
            return 1;
        }
        if((fbmp = open(bmp_name, O_RDWR)) == -1) {
            printf("bmp file open error\n");
            return 1;
        }
        filesize = util_getFdSize(fbmp);
        if((secret = fopen(secret_name, "rb")) == NULL) {
            printf("secret file open error\n");
            return 1;
        }
        
        fseek(secret, 0, SEEK_END);
        size = ftell(secret);
        rewind(secret);
        fread(&bmp_header, sizeof(sBmpHeader), 1, bmp);
        
        if(bmp_header.bitmap_size * bits < size * 8) {
            printf("secret data is too big\n");
            return 0;
        }
        bmp_header.reserve = size;
        rewind(bmp);
        fwrite(&bmp_header, sizeof(sBmpHeader), 1, bmp);
         
        map = mmap(0, bmp_header.size, PROT_READ | PROT_WRITE, MAP_SHARED, fbmp, 0);
       
        if((buffer = calloc(size, 1)) == NULL) {
            printf("allocate error\n");
            return 1;
        }
        if((fbmp = open(bmp_name, O_RDWR)) == -1) {
            printf("bmp file open error\n");
            return 1;
        }
        fread(buffer, size, 1, secret); 
        
        for(int64_t i = 0; i < size; ++i) {
            
            for(int32_t j = 7; j >= 0; --j) {
                
                mask = 1 << bit;
                if(buffer[i] & (1 << j)) {
                    map[bmp_header.offset+cnt] |= mask;
                }
                else {
                    map[bmp_header.offset+cnt] &= (~mask);
                }
                ++bit;
                if(bit == bits) {
                    bit = 0;
                    ++cnt;
                }
                
            }
        }
        
        free(buffer);
        munmap(map, filesize);
        close(fbmp);
        fclose(bmp);
        fclose(secret);
        
    }
    else if(mode == 2) {
        uint32_t cnt = 0;
        uint64_t size = 0;
        uint8_t bit = 0;
        uint8_t mask = 0;
        if((bmp = fopen(bmp_name, "rb")) == NULL) {
            printf("bmp file open error\n");
            return 1;
        }
        if((fbmp = open(bmp_name, O_RDWR)) == -1) {
            printf("bmp file open error\n");
            return 1;
        }
        filesize = util_getFdSize(fbmp);
        if((secret = fopen(secret_name, "wb")) == NULL) {
            printf("secret file open error\n");
            return 1;
        }
        fread(&bmp_header, sizeof(sBmpHeader), 1, bmp);
        
        map = mmap(0, filesize, PROT_READ | PROT_WRITE, MAP_SHARED, fbmp, 0);
        if((buffer = calloc(bmp_header.reserve, 1)) == NULL) {
            printf("allocate error\n");
            return 1;
        }
        size = bmp_header.reserve;
        for(int64_t i = 0; i < size; ++i) {
            for(int32_t j = 7; j >= 0; --j) {
                mask = 1 << bit;
                buffer[i] |= ((map[bmp_header.offset+cnt] & mask) ? 1 << j : 0);
                // if(map[bmp_header.offset+cnt] & mask) printf("1");
                // else printf("0");
                
                ++bit;
                if(bit == bits) {
                    bit = 0;
                    ++cnt;
                }
            }
            // puts("");
        }
        fwrite(buffer, bmp_header.reserve, 1, secret);
        free(buffer);
        munmap(map, filesize);
        close(fbmp);
        fclose(bmp);
        fclose(secret);
    }


}