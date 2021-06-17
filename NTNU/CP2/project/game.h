#ifndef __GAME_H__
#define __GAME_H__
#include <stdio.h>
#include <memory.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#define CARD_NUM 104

typedef struct _Card{
    int32_t id;
    int32_t card;
}Card;

typedef struct _Game {
    bool card[CARD_NUM];    // Is the card has been picked
    int32_t table[4][5];    // card on table
    int32_t table_cnt[4];   // count cards in each row
    int32_t score[10];         // each player's score
    int32_t player_num;
    int32_t difficulty;
}Game;

int32_t game_cmp(const void *a, const void *b);
int32_t deal_card(Game *game);
int32_t get_point(int32_t const card);
int new_row(Game *game, int32_t const row, int32_t const front);
void Game_setup(Game *game, int32_t player_num);
bool place_card(Game *game, int32_t id, int32_t pick);
void show_score(Game const *game, const int32_t id);
void show_table(Game const *game, FILE*);
void show_place_card(const Card *pick, const int32_t i, const int32_t num);

#endif