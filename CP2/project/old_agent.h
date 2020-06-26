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
    int32_t card_cnt;
    void (*setup)(int32_t id);
    void (*deal)( const int32_t card[10] );
    int32_t (*pick)( const int32_t table[4][5], const int32_t score[2], const int32_t last[8] );
    int32_t (*choose)( const int32_t table[4][5], int32_t card );
}Player;

int32_t agent_get_point(int32_t const card);
int32_t agent_cmp(void const *a, void const *b);
void agent_deal(Player *player, const int32_t cards[10]);
int32_t agent_pick_easy(Player *player, const int32_t table[4][5]);
int32_t agent_choose_easy(const int32_t table[4][5]);
int32_t agent_pick_normal(Player *player, const int32_t table[4][5]);
int32_t agent_choose_normal(const int32_t table[4][5]);
int32_t agent_pick_hard(Player *player, const int32_t table[4][5]);
int32_t agent_choose_hard(const int32_t table[4][5]);
void show_card(Player const *player);
bool check_card(Player *player, const int32_t pick);

void CSIE_40847025S_setup(void);
void CSIE_40847025S_deal(void);
void CSIE_40847025S_choose(void);

#endif