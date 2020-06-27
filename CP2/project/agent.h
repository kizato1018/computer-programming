#ifndef __AGENT_H__
#define __AGENT_H__
#include <memory.h>
#include <time.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct _Player{
    int32_t id;
    char name[64];
    int32_t hand[10];
    int32_t card_cnt;
    int8_t online;
    void (*setup)(struct _Player *player, int32_t id);
    void (*deal)(struct _Player *player, const int32_t card[10]);
    int32_t (*pick)(struct _Player *player, const int32_t table[4][5], int32_t (*input)(int32_t *target, const int32_t id, const int8_t mode));
    int32_t (*choose)(struct _Player *player, const int32_t table[4][5], int32_t (*input)(int32_t *target, const int32_t id, const int8_t mode));
}Player;

int32_t agent_get_point(int32_t const card);
int32_t agent_cmp(void const *a, void const *b);
void agent_setup(Player *player, const int32_t id);
void agent_deal(Player *player, const int32_t cards[10]);
int32_t player_pick(Player *player, const int32_t table[4][5], int32_t (*input)(int32_t *target, const int32_t id, const int8_t mode));
int32_t player_choose(Player *player, const int32_t table[4][5], int32_t (*input)(int32_t *target, const int32_t id, const int8_t mode));
int32_t agent_pick_mother(Player *player, const int32_t table[4][5], int32_t (*input)(int32_t *target, const int32_t id, const int8_t mode));
int32_t agent_choose_mother(Player *player, const int32_t table[4][5], int32_t (*input)(int32_t *target, const int32_t id, const int8_t mode));
int32_t agent_pick_grandma(Player *player, const int32_t table[4][5], int32_t (*input)(int32_t *target, const int32_t id, const int8_t mode));
int32_t agent_choose_grandma(Player *player, const int32_t table[4][5], int32_t (*input)(int32_t *target, const int32_t id, const int8_t mode));
int32_t agent_pick_father(Player *player, const int32_t table[4][5], int32_t (*input)(int32_t *target, const int32_t id, const int8_t mode));
int32_t agent_choose_father(Player *player, const int32_t table[4][5], int32_t (*input)(int32_t *target, const int32_t id, const int8_t mode));
void show_card(Player const *player);
bool check_card(Player *player, const int32_t pick);

void CSIE_40847025S_setup(void);
void CSIE_40847025S_deal(void);
void CSIE_40847025S_choose(void);

#endif