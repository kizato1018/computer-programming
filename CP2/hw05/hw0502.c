#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
typedef struct _Net{
    char name[64];
    char inet[16];
    uint64_t RX;
    uint64_t RX_l;
    uint64_t TX;
    uint64_t TX_l;

}Net;

void Bits_convert(uint64_t byte) {
    uint64_t bits = byte * 8;
    uint8_t cnt = 0;
    while(cnt < 2 && bits > 1024) {
        bits /= 1024;
        ++cnt;
    }
    printf("%lu", bits);
    if(cnt == 0) printf("bps");
    else if(cnt == 1) printf("Kbps");
    else if(cnt == 2) printf("Mbps");
}

void Show(Net* n) {
    printf("%s (%s): TX: ", n->name, n->inet);
    Bits_convert(n->TX-n->TX_l);
    printf("; RX: ");
    Bits_convert(n->RX-n->RX_l);
    puts("");
}

void Process(FILE* fp) {
    static Net net[64];
    char buffer[1024] = {};
    size_t cnt = 0;
    uint64_t p;

    while(fscanf(fp, "%s", net[cnt].name) && fgets(buffer, 1024, fp)) {
        // printf("%s\n", buffer);
        net[cnt].name[strlen(net[cnt].name) - 1] = 0;
        fscanf(fp, " inet %s ", net[cnt].inet); fgets(buffer, 1024, fp);
        // printf("%s\n", buffer);
        fscanf(fp, " RX packets %lu bytes %lu ", &p, &net[cnt].RX); fgets(buffer, 1024, fp);
        // printf("%s\n", buffer);
        fscanf(fp, " TX packets %lu bytes %lu ", &p, &net[cnt].TX); fgets(buffer, 1024, fp);
        // printf("%s\n", buffer);
        if(net[cnt].RX_l == 0) { net[cnt].RX_l = net[cnt].RX; }
        if(net[cnt].TX_l == 0) { net[cnt].TX_l = net[cnt].TX; }

        Show(net+cnt);
        net[cnt].RX_l = net[cnt].RX;
        net[cnt].TX_l = net[cnt].TX;
        
        ++cnt;
    }
}

int main() {
    FILE *fp = NULL;
    size_t cnt = 0;

    while(1) {
        if((fp = popen("ifconfig | grep -e 'inet ' -e 'flags' -e 'RX p' -e 'TX p'", "r")) == NULL) {
            printf("Error\n");
            return -1;
        }
        printf("%ld)\n", ++cnt);
        Process(fp);
        fclose(fp);
        sleep(1);
    }
       
    //printf("%s", buffer);
}