#include "agent.h"

int32_t agent_cmp(void const *a, void const *b) {
    return *(int32_t *)a - *(int32_t *)b;
}

void agent_deal(Player *player, const int32_t cards[10]) {
    memcpy(player->hand, cards, 10*sizeof(int32_t));
    qsort(player->hand, 10, sizeof(int32_t), agent_cmp);
    return;
}

int32_t agent_pick_normal(Player const *player, const int32_t table[4][5]) {
    srand(time(NULL));
    int32_t pick = 0;
    while(pick == 0) {
        pick = player->hand[rand()%10];
    }
    return pick;
}

int32_t agent_choose_normal(const int32_t table[4][5]) {
    srand(time(NULL));
    return (rand() % 4) + 1;
}

void show_card(Player const *player) {
    for(int32_t i = 0; i < 10; ++i) {
        if(player->hand[i] > 0)
            printf("%d%c", player->hand[i], " \n"[i==9]);
    }
    return;
}

bool check_card(Player const *player, const int32_t pick) {
    bool valid = false;
    for(int32_t i = 0; i < 10; ++i) {
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
