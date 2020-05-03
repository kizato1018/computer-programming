#include <stdio.h>
#include <stdint.h>

void status(FILE *pF) {
    int choose = 0;
    long int pos = 12886;
    long int offset;
    int32_t value_32;
    uint8_t value_u8;
    uint16_t value_u16;
    while(1) {
        printf("1) modify contribution -2147483648~10000000\n");
        printf("2) modify command 0~255\n");
        printf("3) modify opperation 0~255\n");
        printf("4) modify information 0~255\n");
        printf("5) modify agility 0~255\n");
        printf("6) modify attack 0~255\n");
        printf("7) modify defend 0~255\n");
        printf("8) modify land 0~255\n");
        printf("9) modify air 0~255\n");
        printf("10) modify political work 0~65535\n");
        printf("11) modify information work 0~65535\n");
        printf("12) modify military work 0~65535\n");
        printf("0) exit\n");
        scanf("%d", &choose);
        switch (choose) {
        case 1:
            offset = pos;
            scanf("%d", &value_32);
            fseek(pF, offset, SEEK_SET);
            fwrite(&value_32, sizeof(int32_t), 1, pF);
            break;
        case 2 ... 9:
            offset = pos + choose + 2;
            scanf("%hhd", &value_u8);
            fseek(pF, offset, SEEK_SET);
            fwrite(&value_u8, sizeof(uint8_t), 1, pF);
            break;
        case 10 ... 12:
            offset = pos + (choose-10) * 2 + 12;
            scanf("%hd", &value_u16);
            fseek(pF, offset, SEEK_SET);
            fwrite(&value_u16, sizeof(uint16_t), 1, pF);
            break;
        case 0:
            return;
        default:
            printf("No this opption\n");
            break;
        }
    }
}

void menu(FILE *pF) {
    int choose = 0;
    while(1) {
        printf("1) modify status\n");
        printf("2) modify budget\n");
        printf("0) exit\n");
        scanf("%d", &choose);
        switch (choose) {
        case 1:
            status(pF);
            break;
        case 0:
            return;
        default:
            printf("No this opption\n");
            break;
        }
    }

}

int main() {
    FILE *pF = NULL;
    char path[256] = "./G4X/G4XUSR00.DAT";
    printf("Please input the path of data: ");
    if((pF = fopen(path, "rb+")) == NULL) {
        printf("file open error\n");
        return 1;
    }
    menu(pF);

}