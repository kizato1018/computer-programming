#ifndef __AGENT_H__
#define __AGENT_H__
#include <memory.h>
#include <time.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct _Player{
    int32_t hand[10];
}Player;

int32_t agent_cmp(void const *a, void const *b);

void agent_deal(Player *player, const int32_t cards[10]);

int32_t agent_pick(Player const *player, const int32_t table[4][5]);

void show_card(Player const *player);

bool check_card(Player const *player, const int32_t pick);

void CSIE_40847025S_setup(void);

#endif