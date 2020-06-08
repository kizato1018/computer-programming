#include <stdio.h>
#include <stdint.h>
#include <getopt.h>


struct option long_options[] = {
    {"enc", 1, NULL, 'e'},
    {"dec", 1, NULL, 'd'},
    {"output", 1, NULL, 'o'}
};

void bshow(uint32_t n, int b) {
    for(int i = 23; i >= 0; --i) {
        printf("%d", n & (1 << i) ? 1 : 0);
        if(i % b == 0) printf(" ");
    }
}

char b2c(uint8_t b) {
    switch (b) {
    case 0 ... 25:
        return 'A' + b;
    case 26 ... 51:
        return 'a' + b - 26;
    case 52 ... 61:
        return '0' + b - 52;
    case 62:
        return '+';
    case 63:
        return '/';
    default:
        return 0;
    }
}

uint8_t c2b(char c) {
    switch (c){
    case 'A'...'Z':
        return c - 'A';
    case 'a'...'z':
        return c - 'a' + 26;
    case '0'...'9':
        return c - '0' + 52;
    case '+':
        return 62;
    case '/':
        return 63;
    default:
        return 0;
    }
}

void encode(FILE* in, FILE* out) {
    char cbuffer[768] = {};
    uint8_t obuffer[1024] = {};
    size_t count = 0;
    uint32_t temp;
    uint32_t mask = 63 << 18;
    size_t ocnt = 0;
    while(count = fread(cbuffer, 1, 768, in)) {
        for(size_t i = 0; i < count; i += 3) {
            temp = 0;
            mask = 63 << 18;
            for(size_t j = 0; j < 3; ++j) {
                temp <<= 8;
                temp += (i+j < count) ? cbuffer[i+j] : 0;
            }
            bshow(temp, 6);
            for(size_t j = 0; j < 4; ++j, ++ocnt) {
                obuffer[ocnt] = (i+j <= count) ? b2c((temp & mask) >> (18 - 6 * j)) : '=';
                mask >>= 6;
            }
        }
        fwrite(obuffer, 1, ocnt, out);
    }
}

void decode(FILE* in, FILE* out) {
    char ibuffer[1024] = {};
    char obuffer[768] = {};
    size_t count = 0;
    uint32_t temp;
    uint32_t mask = 255 << 16;
    size_t ocnt = 0;
    while(count = fread(ibuffer, 1, 1024, in)) {
        for(size_t i = 0; i < count; i += 4) {
            temp = 0;
            mask = 255 << 16;
            for(size_t j = 0; j < 4; ++j) {
                temp <<= 6;
                printf("%d ", c2b(ibuffer[i+j]));
                temp += c2b(ibuffer[i+j]);
            }
            for(size_t j = 0; j < 3; ++j, ++ocnt) {
                obuffer[ocnt] = ((temp & mask) >> (16 - 8 * j));
                mask >>= 8;
            }
        }
        fwrite(obuffer, 1, ocnt, out);
    }
}

int main(int argc, char* argv[]) {
    FILE *in, *out;
    char opt = 0;
    int mode = 0;
    int index = 0;

    while((opt = getopt_long(argc, argv, "e:d:o:", long_options, &index)) != -1) {
        switch(opt) {
            case 'e':
                printf("encode:%s\n", optarg);
                if((in = fopen(optarg, "rb")) == NULL) {
                    printf("file open error\n");
                    return -1;
                }
                mode = 1;
                break;
            case 'd': //extract
                printf("decode:%s\n", optarg);
                if((in = fopen(optarg, "rb")) == NULL) {
                    printf("file open error\n");
                    return -1;
                }
                mode = 2;
                break;
            case 'o':
                printf("output:%s\n", optarg);
                if((out = fopen(optarg, "wb")) == NULL) {
                    printf("file open error\n");
                    return -1;
                }
                break;
            default:
                printf("no this option\n");
                break;
        }
    }
    if(mode == 1) {
        encode(in, out);
    }
    else if(mode == 2) {
        decode(in, out);
    }
}