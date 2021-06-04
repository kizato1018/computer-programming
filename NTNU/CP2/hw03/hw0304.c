#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

struct _Character {
    uint8_t ID;
    uint8_t belong;
    uint8_t suffix;
    uint8_t condition;
    uint8_t location;
    uint8_t unknow1[7];
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
    static Character ch;
    int64_t input;
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
        printf("1) 功績 %d\n", ch.contrubution);
        printf("2) 統率 %u\n", ch.command);
        printf("3) 營運 %u\n", ch.opperation);
        printf("4) 情報 %u\n", ch.information);
        printf("5) 機動 %u\n", ch.agility);
        printf("6) 攻擊 %u\n", ch.attack);
        printf("7) 防禦 %u\n", ch.defend);
        printf("8) 陸戰 %u\n", ch.land);
        printf("9) 空戰 %u\n", ch.air);
        printf("10) 政治工作 %u\n", ch.political_work);
        printf("11) 情報工作 %u\n", ch.information_work);
        printf("12) 軍事工作 %u\n", ch.military_work);
        printf("13) 歸屬 ");
        if(ch.belong == 0) printf("帝國\n");
        else if(ch.belong == 1) printf("同盟\n");
        else printf("其他\n");
        printf("0) 結束\n");
        scanf("%d", &choose);
        switch (choose) {
        case 1:
            offset = 12;
            do {
                printf("set value (-2147483648~10000000): ");
                scanf("%ld", &input);
                if(!(-2147483648 <= input && 10000000 >= input))
                    printf("out of range!\n");
                else break;
            } while(1);
            value_32 = input;
            ch.contrubution = value_32;
            fseek(pF, pos+offset, SEEK_SET);
            fwrite(&value_32, sizeof(int32_t), 1, pF);
            break;
        case 2:
            offset = 16;
            do {
                printf("set value (0~255): ");
                scanf("%ld", &input);
                if(!(0 <= input && 255 >= input))
                    printf("out of rangr!\n");
                else break;
            } while(1);
            value_u8 = input;
            ch.command = value_u8;
            fseek(pF, pos+offset, SEEK_SET);
            fwrite(&value_u8, sizeof(uint8_t), 1, pF);
            break;
        case 3:
            offset = 17;
            do {
                printf("set value (0~255): ");
                scanf("%ld", &input);
                if(!(0 <= input && 255 >= input))
                    printf("out of rangr!\n");
                else break;
            } while(1);
            value_u8 = input;
            ch.opperation = value_u8;
            fseek(pF, pos+offset, SEEK_SET);
            fwrite(&value_u8, sizeof(uint8_t), 1, pF);
            break;
        case 4:
            offset = 18;
            do {
                printf("set value (0~255): ");
                scanf("%ld", &input);
                if(!(0 <= input && 255 >= input))
                    printf("out of rangr!\n");
                else break;
            } while(1);
            value_u8 = input;
            ch.information = value_u8;
            fseek(pF, pos+offset, SEEK_SET);
            fwrite(&value_u8, sizeof(uint8_t), 1, pF);
            break;
        case 5:
            offset = 19;
            do {
                printf("set value (0~255): ");
                scanf("%ld", &input);
                if(!(0 <= input && 255 >= input))
                    printf("out of rangr!\n");
                else break;
            } while(1);
            value_u8 = input;
            ch.agility = value_u8;
            fseek(pF, pos+offset, SEEK_SET);
            fwrite(&value_u8, sizeof(uint8_t), 1, pF);
            break;
        case 6:
            offset = 20;
            do {
                printf("set value (0~255): ");
                scanf("%ld", &input);
                if(!(0 <= input && 255 >= input))
                    printf("out of rangr!\n");
                else break;
            } while(1);
            value_u8 = input;
            ch.attack = value_u8;
            fseek(pF, pos+offset, SEEK_SET);
            fwrite(&value_u8, sizeof(uint8_t), 1, pF);
            break;
        case 7:
            offset = 21;
            do {
                printf("set value (0~255): ");
                scanf("%ld", &input);
                if(!(0 <= input && 255 >= input))
                    printf("out of rangr!\n");
                else break;
            } while(1);
            value_u8 = input;
            ch.defend = value_u8;
            fseek(pF, pos+offset, SEEK_SET);
            fwrite(&value_u8, sizeof(uint8_t), 1, pF);
            break;
        case 8:
            offset = 22;
            do {
                printf("set value (0~255): ");
                scanf("%ld", &input);
                if(!(0 <= input && 255 >= input))
                    printf("out of rangr!\n");
                else break;
            } while(1);
            value_u8 = input;
            ch.land = value_u8;
            fseek(pF, pos+offset, SEEK_SET);
            fwrite(&value_u8, sizeof(uint8_t), 1, pF);
            break;
        case 9:
            offset = 23;
            do {
                printf("set value (0~255): ");
                scanf("%ld", &input);
                if(!(0 <= input && 255 >= input))
                    printf("out of rangr!\n");
                else break;
            } while(1);
            value_u8 = input;
            ch.air = value_u8;
            fseek(pF, pos+offset, SEEK_SET);
            fwrite(&value_u8, sizeof(uint8_t), 1, pF);
            break;
        case 10:
            offset = 24;
            do {
                printf("set value (0~65535): ");
                scanf("%ld", &input);
                if(!(0 <= input && 65535 >= input))
                    printf("out of rangr!\n");
                else break;
            } while(1);
            value_u16 = input;
            ch.political_work = value_u16;
            fseek(pF, pos+offset, SEEK_SET);
            fwrite(&value_u16, sizeof(uint16_t), 1, pF);
            break;
        case 11:
            offset = 26;
            do {
                printf("set value (0~65535): ");
                scanf("%ld", &input);
                if(!(0 <= input && 65535 >= input))
                    printf("out of rangr!\n");
                else break;
            } while(1);
            value_u16 = input;
            ch.information_work = value_u16;
            fseek(pF, pos+offset, SEEK_SET);
            fwrite(&value_u16, sizeof(uint16_t), 1, pF);
            break;
        case 12:
            offset = 28;
            do {
                printf("set value (0~65535): ");
                scanf("%ld", &input);
                if(!(0 <= input && 65535 >= input))
                    printf("out of rangr!\n");
                else break;
            } while(1);
            value_u16 = input;
            ch.military_work = value_u16;
            fseek(pF, pos+offset, SEEK_SET);
            fwrite(&value_u16, sizeof(uint16_t), 1, pF);
            break;
        case 13:
            offset = 1;
            do {
                printf("set value (0:帝國, 1:同盟): ");
                scanf("%ld", &input);
                if(!(0 <= input && 1 >= input))
                    printf("out of rangr!\n");
                else break;
            } while(1);
            value_u8 = input;
            ch.belong = value_u8;
            fseek(pF, pos+offset, SEEK_SET);
            fwrite(&value_u8, sizeof(uint8_t), 1, pF);
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
    static int32_t militery;
    static int32_t headquarter;
    static int32_t alliance;
    int64_t input;
    bool isExit = false;
    fseek(pF, 0x008e, SEEK_SET);
    fread(&militery, sizeof(int32_t), 1, pF);
    fread(&headquarter, sizeof(int32_t), 1, pF);
    fseek(pF, 0x00cc, SEEK_SET);
    fread(&alliance, sizeof(int32_t), 1, pF);

    while(!isExit) {
        printf("1) 軍務省預算 %d\n", militery);
        printf("2) 統帥本部預算 %d\n", headquarter);
        printf("3) 國防預算 %d\n", alliance);
        printf("0) exit\n");
        scanf("%d", &choose);
        switch (choose) {
        case 1:
            do {
                printf("set value (-2147483648~2147483647): ");
                scanf("%ld", &input);
                if(!(-2147483648 <= input && 2147483647 >= input))
                    printf("out of rangr!\n");
                else break;
            } while(1);
            militery = input;
            fseek(pF, 0x008e, SEEK_SET);
            fwrite(&militery, sizeof(int32_t), 1, pF);
            break;
        case 2:
            do {
                printf("set value (-2147483648~2147483647): ");
                scanf("%ld", &input);
                if(!(-2147483648 <= input && 2147483647 >= input))
                    printf("out of rangr!\n");
                else break;
            } while(1);
            headquarter = input;
            fseek(pF, 0x0092, SEEK_SET);
            fwrite(&headquarter, sizeof(int32_t), 1, pF);
            break;
        case 3:
            do {
                printf("set value (-2147483648~2147483647): ");
                scanf("%ld", &input);
                if(!(-2147483648 <= input && 2147483647 >= input))
                    printf("out of rangr!\n");
                else break;
            } while(1);
            alliance = input;
            fseek(pF, 0x00cc, SEEK_SET);
            fwrite(&alliance, sizeof(int32_t), 1, pF);
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
        printf("2) modify budget\n");
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
    char path[256] = {0};
    printf("Please input the path of data (e.g. G4X/G4XUSR00.DAT): ");
	fgets(path, sizeof(path), stdin);
    if(path[strlen(path)-1] == '\n')
        path[strlen(path)-1] = 0;
    if((pF = fopen(path, "rb+")) == NULL) {
        printf("file open error\n");
        return 1;
    }
    menu(pF);
    fclose(pF);
}
