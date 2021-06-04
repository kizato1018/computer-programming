#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool end = false;

typedef struct _Player{
	char name[10];
	int lv;
	int exp;
	int money;
	int maxhp;
	int hp;
	int atk;
	int potion;
}Player;

typedef struct _Monster
{
	int hp;
	int atk;
}Monster;

Player init(){
	Player p;
	strcpy(p.name, "Hero");
	p.lv = 1;
	p.exp = 0;
	p.money = 0;
	p.potion = 0;
	printf("Hero's HP (1~255): ");
	scanf("%d", &p.maxhp);
	p.hp = p.maxhp;
	if(p.hp < 0 || p.hp > 255){
		printf("HP out of the range!\n");
		end = true;
		return p;
	}
	printf("Hero's ATK (1~255): ");
	scanf("%d", &p.atk);
	if(p.atk < 0 || p.atk > 255){
		printf("ATK out of the range!\n");
		end = true;
		return p;
	}
	return p;
}


void stauts1(Player p){
	printf("Name: %s\n", p.name);
	printf("Level: %d\n", p.lv);
	printf("EXP: %d\n", p.exp);
	printf("MONEY: %d\n", p.money);
}

void status2(Player p){
	printf("HP: %d/%d\n", p.hp, p.maxhp);
	printf("ATK: %d\n", p.atk);
	printf("Potion: %d\n", p.potion);
}

void status(Player p){
	int c;
	system("clear");
	stauts1(p);
	printf("-----------\n");
	status2(p);
	while(1){
		printf("-----------\n");
		printf("1)Back\n");
		printf("\nChoice: ");
		scanf("%d", &c);
		switch(c){
			case 1:
				return;
			default:
				printf("No this choice\n");
				break;
		}
	}
}

void shop(int *money, int *potion){
	int c;
	system("clear");
	printf("MONEY: %d\n", *money);
	printf("Potion: %d\n", *potion);
	printf("-----------\n");
	printf("1)Buy one potion\n");
	printf("2)Back\n");
	while(1){
		printf("\nChoice: ");
		scanf("%d", &c);
		switch(c){
			case 1:
				if(*money < 10){
					printf("You don't have enough money.\n");
				}
				else{
					*money -= 10;
					*potion++;
					return shop(money, potion);
				}
				break;
			case 2:
				return;
			default:
				printf("No this choice\n");
				break;

		}
	}
}

void monster(Player *p){
	int c;
	int mhp = 150;
	int matk = 15;
	system("clear");
	printf("Monster\n");
	printf("HP: %d/150\n", mhp);
	printf("ATK: %d\n", matk);
	printf("-----------\n");
	status2(*p);
	printf("-----------\n");
	printf("1)Attack\n");
	printf("2)Potion\n");
	printf("3)Escape\n");
	while(1){
		printf("\nChoice: ");
		scanf("%d", &c);
		switch(c){
			case 1:
				mhp -= p->atk;
				if(mhp <= 0){
					printf("win\n");
					p->exp += 20;
					p->money += 20;
					if(p->exp >= (p->lv + 1) * 100){
						p->maxhp += 20;
						p->hp += 20;
						p->atk += 3;
					}
					return;
				}
				p->hp -= matk;
				return monster(p);
				break;
			case 2:
				if(p->potion <= 0){
					printf("You don't have any potion\n");
					break;
				}
				p->hp += 60;
				p->potion--;
				if(p->hp > p->maxhp)
					p->hp = p->maxhp;
				p->hp -= matk;
				return monster(p);
				break;
			case 3:
				return;
			default:
				printf("No this choice\n");
				break;
		}
		if(p->hp < 0){
			printf("You died!\n");
			end = true;
			return;
		}
	}

}

int main(){
	Player p;
	int c;
	p = init();
	while(!end){
		system("clear");
		printf("1)Status\n");
		printf("2)Shop\n");
		printf("3)Monster\n");
		printf("4)Boss\n");
		printf("5)Exit\n");
		printf("\nChoice: ");
		scanf("%d", &c);
		switch(c){
			case 1:
				status(p);
				break;
			case 2:
				shop(&p.money, &p.potion);
				break;
			case 3:
				monster(&p);
				break;
			case 5:
				end = true;
				break;
			default:
				printf("No this choice\n");
				break;
		}
	}
}