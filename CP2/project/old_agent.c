#include "agent.h"

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


void agent_deal(Player *player, const int32_t cards[10]) {
    player->card_cnt = 10;
    memcpy(player->hand, cards, player->card_cnt*sizeof(int32_t));
    qsort(player->hand, player->card_cnt, sizeof(int32_t), agent_cmp);
    return;
}
int32_t agent_pick_easy(Player *player, const int32_t table[4][5]) {
    --player->card_cnt;
    int32_t pick = player->card_cnt-1;
    int32_t card = player->hand[pick];
    
    return card;
}
int32_t agent_choose_easy(const int32_t table[4][5]) {
    srand(time(NULL));
    return (rand() % 4) + 1;
}
int32_t agent_pick_normal(Player *player, const int32_t table[4][5]) {
    srand(time(NULL));
    int32_t pick = rand()%player->card_cnt;
    int32_t card = player->hand[pick];
    for(int32_t i = pick; i < player->card_cnt-1; ++i)
        player->hand[i] = player->hand[i+1];
    --player->card_cnt;
    
    return card;
}

int32_t agent_choose_normal(const int32_t table[4][5]) {
    srand(time(NULL));
    return (rand() % 4) + 1;
}

int32_t agent_pick_hard(Player *player, const int32_t table[4][5]) {
    int32_t pick = 0;
    int32_t card = player->hand[pick];
    for(int32_t i = pick; i < player->card_cnt-1; ++i)
        player->hand[i] = player->hand[i+1];
    --player->card_cnt;
    
    return card;
}
int32_t agent_choose_hard(const int32_t table[4][5]) {
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
}

void show_card(Player const *player) {
    for(int32_t i = 0; i < 10; ++i) {
        if(player->hand[i] > 0)
            printf("%d%c", player->hand[i], " \n"[i==9]);
    }
    return;
}

bool check_card(Player *player, const int32_t pick) {
    bool valid = false;
    for(int32_t i = 0; i < player->card_cnt; ++i) {
        if(valid) {
            player->hand[i-1] = player->hand[i];
            player->card_cnt -= (i == player->card_cnt-1);
        }
        if(player->hand[i] == pick && pick > 0)
            valid = true;
    }
    return valid;
}

Player *CSIE_40847025S;

void CSIE_40847025S_setup(void) {
    CSIE_40847025S = calloc(1, sizeof(Player));
    return;
}
