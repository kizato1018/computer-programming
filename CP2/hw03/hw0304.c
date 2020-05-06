#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

struct _Character {
    uint8_t ID;
    uint8_t unknow1[11];
    int32_t contrubution;
    uint8_t command;
    uint8_t opperation;
    uint8_t information;
    uint8_t agility;
    uint8_t attack;
    uint8_t defend;
    uint8_t land;
    uint8_t air;
    uint16_t political_work;
    uint16_t information_work;
    uint16_t military_work;
    uint8_t unknow2[4];
}__attribute__((__packed__));

typedef struct _Character Character;

void status(FILE *pF) {
    int choose = 0;
    uint8_t id;
    long int pos = 0x1d92;
    long int offset = 12;
    Character ch;
    int32_t value_32;
    uint8_t value_u8;
    uint16_t value_u16;
    bool isExit = false;
    
    while(!isExit) {
        printf("input character id you want to modify 00~b4(ff = current character): ");
        scanf("%hhx", &id);
        if(0 <= id && 180 >= id) {
            pos += id * sizeof(Character);
            isExit = true;
        }
        else if(0xff == id) {
            fseek(pF, 0x003a, SEEK_SET);
            fread(&id, sizeof(id), 1, pF);
            pos += id * sizeof(Character);
            isExit = true;
        }
        else {
            printf("Wrong input\n");
        }
    }
    fseek(pF, pos, SEEK_SET);
    fread(&ch, sizeof(Character), 1, pF);
    fseek(pF, -1*sizeof(Character), SEEK_CUR);
    isExit = false;
    while(!isExit) {
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
            offset += 0;
            printf("current contribution: %d\n", ch.contrubution);
            printf("set value: ");
            scanf("%d", &value_32);
            ch.contrubution = value_32;
            fseek(pF, pos+offset, SEEK_SET);
            fwrite(&value_32, sizeof(int32_t), 1, pF);
            break;
        case 2:
            printf("current command: %d\n", ch.command);
            printf("set value: ");
            offset += choose + 2;
            scanf("%hhd", &value_u8);
            ch.command = value_u8;
            fseek(pF, pos+offset, SEEK_SET);
            fwrite(&value_u8, sizeof(uint8_t), 1, pF);
            break;
        case 3:
            printf("current opperation: %d\n", ch.opperation);
            printf("set value: ");
            offset += choose + 2;
            scanf("%hhd", &value_u8);
            fseek(pF, pos+offset, SEEK_SET);
            fwrite(&value_u8, sizeof(uint8_t), 1, pF);
            break;
        case 4:
            printf("current information: %d\n", ch.information);
            printf("set value: ");
            offset += choose + 2;
            scanf("%hhd", &value_u8);
            fseek(pF, pos+offset, SEEK_SET);
            fwrite(&value_u8, sizeof(uint8_t), 1, pF);
            break;
        case 5:
            printf("current agility: %d\n", ch.agility);
            printf("set value: ");
            offset += choose + 2;
            scanf("%hhd", &value_u8);
            fseek(pF, pos+offset, SEEK_SET);
            fwrite(&value_u8, sizeof(uint8_t), 1, pF);
            break;
        case 6:
            printf("current attack: %d\n", ch.attack);
            printf("set value: ");
            offset += choose + 2;
            scanf("%hhd", &value_u8);
            fseek(pF, pos+offset, SEEK_SET);
            fwrite(&value_u8, sizeof(uint8_t), 1, pF);
            break;
        case 7:
            printf("current defend: %d\n", ch.defend);
            printf("set value: ");
            offset += choose + 2;
            scanf("%hhd", &value_u8);
            fseek(pF, pos+offset, SEEK_SET);
            fwrite(&value_u8, sizeof(uint8_t), 1, pF);
            break;
        case 8:
            printf("current land: %d\n", ch.land);
            printf("set value: ");
            offset += choose + 2;
            scanf("%hhd", &value_u8);
            fseek(pF, pos+offset, SEEK_SET);
            fwrite(&value_u8, sizeof(uint8_t), 1, pF);
            break;
        case 9:
            printf("current air: %d\n", ch.air);
            printf("set value: ");
            offset += choose + 2;
            scanf("%hhd", &value_u8);
            fseek(pF, pos+offset, SEEK_SET);
            fwrite(&value_u8, sizeof(uint8_t), 1, pF);
            break;
        case 10:
            printf("current political work: %d\n", ch.political_work);
            printf("set value: ");
            offset += (choose-10) * 2 + 12;
            scanf("%hd", &value_u16);
            fseek(pF, pos+offset, SEEK_SET);
            fwrite(&value_u16, sizeof(uint16_t), 1, pF);
            break;
        case 11:
            printf("current information work: %d\n", ch.information_work);
            printf("set value: ");
            offset += (choose-10) * 2 + 12;
            scanf("%hd", &value_u16);
            fseek(pF, pos+offset, SEEK_SET);
            fwrite(&value_u16, sizeof(uint16_t), 1, pF);
            break;
        case 12:
            printf("current military work: %d\n", ch.military_work);
            printf("set value: ");
            offset += (choose-10) * 2 + 12;
            scanf("%hd", &value_u16);
            fseek(pF, pos+offset, SEEK_SET);
            fwrite(&value_u16, sizeof(uint16_t), 1, pF);
            break;
        case 0:
            isExit = true;
            break;
        default:
            printf("No this opption\n");
            break;
        }
    }
}

void budget(FILE *pF) {
    int choose = 0;
    int32_t militery;
    int32_t headquarter;
    int32_t alliance;
    int32_t vlaue_32;
    bool isExit = false;
    fseek(pF, 0x0092, SEEK_SET);
    fread(&militery, sizeof(int32_t), 1, pF);
    fread(&headquarter, sizeof(int32_t), 1, pF);
    fseek(pF, 0x00cc, SEEK_CUR);
    fread(&alliance, sizeof(int32_t), 1, pF);

    while(!isExit) {
        printf("1) modify militery's budget -2147483648~2147483647: ");
        printf("2) modify headquarter's budget -2147483648~2147483647: ");
        printf("3) modify alliance's budget -2147483648~2147483647: ");
        printf("0) exit");
        scanf("%d", &choose);
        switch (choose) {
        case 1:
            printf("current militery's budget: %d\n", militery);
            printf("set value: ");
            scanf("%d", &vlaue_32);
            fseek(pF, 0x0092, SEEK_SET);
            fwrite(&vlaue_32, sizeof(int32_t), 1, pF);
            break;
        case 2:
            printf("current headquarter's budget: %d\n", headquarter);
            printf("set value: ");
            scanf("%d", &vlaue_32);
            fseek(pF, 0x0096, SEEK_SET);
            fwrite(&vlaue_32, sizeof(int32_t), 1, pF);
            break;
        case 3:
            printf("current alliance's budget: %d\n", alliance);
            printf("set value: ");
            scanf("%d", &vlaue_32);
            fseek(pF, 0x00cc, SEEK_SET);
            fwrite(&vlaue_32, sizeof(int32_t), 1, pF);
            break;
        case 0:
            isExit = true;
            break;
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
        printf("2) modify budget -2147483648~2147483647\n");
        printf("0) exit\n");
        scanf("%d", &choose);
        switch (choose) {
        case 1:
            status(pF);
            break;
		case 2:
			budget(pF);
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
    char path[256] = {};
    printf("Please input the path of data: ");
	fgets(path, sizeof(path), stdin);
    if(path[strlen(path)-1] == '\n')
        path[strlen(path)-1] = 0;
    if((pF = fopen(path, "rb+")) == NULL) {
        printf("file open error\n");
        return 1;
    }
    menu(pF);

}
