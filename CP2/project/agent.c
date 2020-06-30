#include "agent.h"
#define RED "\033[0;41m"
#define GREEN "\033[0;42;30m"
#define YELLOW "\033[0;43;30m"
#define BLUE "\033[0;44m"
#define RESET "\033[m"
#define color_print(color, fmt, ...) printf(color fmt RESET, __VA_ARGS__)

int32_t agent_get_point(int32_t const card) {
    if(card == 55) {
        return 7;
    }
    else if(card % 11 == 0) {
        return 5;
    }
    else if(card % 10 == 0) {
        return 3;
    }
    else if(card % 5 == 0) {
        return 2;
    }
    else
        return 1;
}

int32_t agent_cmp(void const *a, void const *b) {
    return *(int32_t *)a - *(int32_t *)b;
}
void agent_setup(Player *player, const int32_t id) {
    player->id = id;
}
void agent_deal(Player *player, const int32_t cards[10]) {
    player->card_cnt = 10;
    memcpy(player->hand, cards, player->card_cnt * sizeof(int32_t));
    qsort(player->hand, player->card_cnt, sizeof(int32_t), agent_cmp);
    return;
}
int32_t player_pick(Player *player, const int32_t table[4][5], int32_t (*input)(int32_t *target, const int32_t id, const int8_t mode)) {
    bool isPick = false;
    int32_t pick = 0;
    while(!isPick) {
        printf("pick your card: ");
        if(input(&pick, player->id, player->online) == 1)
            return -1;
        if(!check_card(player, pick)) {
            printf("pick wrong card.\n");
        }
        else {
            isPick = true;
            break;
        }
    }
    return pick;
}
int32_t player_choose(Player *player, const int32_t table[4][5], int32_t (*input)(int32_t *target, const int32_t id, const int8_t mode)) {
    bool isPick = false;
    int32_t row = 0;
    printf("Your card is smaller than all row.\n");
    while(!isPick) {
        printf("Pick one row (1~4): ");
        if(input(&row, player->id, player->online) == 1)
            return -1;
        if(row < 1 || row > 4) 
            printf("Wrong input.\n");
        else {
            isPick = true;
            break;
        }
    }
    return row;
}

int32_t agent_pick_mother(Player *player, const int32_t table[4][5], int32_t (*input)(int32_t *target, const int32_t id, const int8_t mode)) {
    --player->card_cnt;
    int32_t pick = player->card_cnt-1;
    int32_t card = player->hand[pick];
    
    return card;
}
int32_t agent_choose_mother(Player *player, const int32_t table[4][5], int32_t (*input)(int32_t *target, const int32_t id, const int8_t mode)) {
    srand(time(NULL));
    return (rand() % 4) + 1;
}
int32_t agent_pick_grandma(Player *player, const int32_t table[4][5], int32_t (*input)(int32_t *target, const int32_t id, const int8_t mode)) {
    srand(time(NULL));
    int32_t pick = rand()%player->card_cnt;
    int32_t card = player->hand[pick];
    for(int32_t i = pick; i < player->card_cnt-1; ++i)
        player->hand[i] = player->hand[i+1];
    --player->card_cnt;
    
    return card;
}

int32_t agent_choose_grandma(Player *player, const int32_t table[4][5], int32_t (*input)(int32_t *target, const int32_t id, const int8_t mode)) {
    srand(time(NULL));
    return (rand() % 4) + 1;
}

int32_t agent_choose_father(Player *player, const int32_t table[4][5], int32_t (*input)(int32_t *target, const int32_t id, const int8_t mode)) {
    int32_t Min = 100;
    int32_t Min_card = 6;
    int32_t Min_row = 0;
    int32_t i = 0, j = 0, sum = 0;
    for(i = 0; i < 4; ++i) {
        sum = 0;
        for(j = 0; j < 5; ++j) {
            if(table[i][j] == 0) {
                break;
            }
            sum += agent_get_point(table[i][j]);
        }
        if(sum < Min) {
            Min = sum;
            Min_card = j;
            Min_row = i+1;
        }
        else if(sum == Min) {
            if(j < Min_card) {
                Min_card = j;
                Min_row = i+1;
            }
        }
    }
    return Min_row;
}

int32_t agent_pick_father(Player *player, const int32_t table[4][5], int32_t (*input)(int32_t *target, const int32_t id, const int8_t mode)) {
    int32_t pick = 0;
    int32_t card = player->hand[pick];
    for(int32_t i = pick; i < player->card_cnt-1; ++i)
        player->hand[i] = player->hand[i+1];
    --player->card_cnt;
    
    return card;
}

void show_card(Player const *player) {
    printf("Card color score\n");
    color_print(BLUE, "%c", ' ');
    printf(":2 ");
    color_print(GREEN, "%c", ' ');
    printf(":3 ");
    color_print(RED, "%c", ' ');
    printf(":5 ");
    color_print(YELLOW, "%c", ' ');
    printf(":7\n\n");

    printf("Your hand cards:\n");
    for(int32_t i = 0; i < 10; ++i) {
        if(player->hand[i] > 0) {
            switch (agent_get_point(player->hand[i])) {
            case 2:
                color_print(BLUE, "%d", player->hand[i]);
                printf("%c", " \n"[i==player->card_cnt-1]);
                break;
            case 3:
                color_print(GREEN, "%d", player->hand[i]);
                printf("%c", " \n"[i==player->card_cnt-1]);
                break;
            case 5:
                color_print(RED, "%d", player->hand[i]);
                printf("%c", " \n"[i==player->card_cnt-1]);
                break;
            case 7:
                color_print(YELLOW, "%d", player->hand[i]);
                printf("%c", " \n"[i==player->card_cnt-1]);
                break;
            
            default:
                printf("%d%c", player->hand[i], " \n"[i==player->card_cnt-1]);
                break;
            }
        }
    }
    return;
}

bool check_card(Player *player, const int32_t pick) {
    bool valid = false;
    for(int32_t i = 0; i < player->card_cnt; ++i) {
        if(valid) 
            player->hand[i-1] = player->hand[i];
        if(player->hand[i] == pick && pick > 0)
            valid = true;
    }
    if(valid) {
        --player->card_cnt;
        player->hand[player->card_cnt] = 0;
    }
    return valid;
}

Player *CSIE_40847025S;

void CSIE_40847025S_setup(void) {
    CSIE_40847025S = calloc(1, sizeof(Player));
    return;
}

