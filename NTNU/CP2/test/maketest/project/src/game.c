#include "game.h"
#include <stdio.h>

int32_t game_cmp(const void *a, const void *b) {
    return *(int32_t *)a - *(int32_t *)b;
}

int32_t deal_card(Game *game) {
    static int32_t left_card = CARD_NUM;
    srand(time(NULL));
    if(left_card < 1) return 0;
    int32_t deal = 0;
    do {
        deal = rand() % CARD_NUM;
    } while(game->card[deal]);
    game->card[deal] = true;
    --left_card;
    return deal+1;
}

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

int new_row(Game *game, int32_t const row, int32_t const front) {
    int32_t score = 0;
    for(int32_t i = 0; i < 5; ++i) {
        if(game->table[row][i] == 0) break;
        score += agent_get_point(game->table[row][i]);
        game->table[row][i] = 0;
    }
    game->table[row][0] = front;
    game->table_cnt[row] = 1;
    return score;
}

void Game_setup(Game *game, int32_t player_num) {    

    // declear
    int32_t pick = 0;

    // initillize
    memset(game->card, 0, CARD_NUM * sizeof(bool));
    game->score = calloc(player_num, sizeof(int32_t));
    memset(game->score, 0, player_num * sizeof(int32_t));
    game->player_num = player_num;

    // pick 4 card on table
    for(int i = 0; i < 4 ; ++i) {
        pick = deal_card(game);
        new_row(game, i, pick);
    }

    printf("Setup\n");
    return;
}

bool place_card(Game *game, int32_t id, int32_t pick) {

    int32_t value = 0;
    int32_t row = -1;
    for(int32_t j = 0; j < 4; ++j) {
        if(game->table[j][game->table_cnt[j]-1] < pick && game->table[j][game->table_cnt[j]-1] > value) {
            value = game->table[j][game->table_cnt[j]-1];
            row = j;
        }
    }
    if(row < 0) {
        return true; // pick one row
    }
    else if(game->table_cnt[row] == 5) {
        game->score[id] += new_row(game, row, pick);
    }
    else {
        game->table[row][game->table_cnt[row]] = pick;
        ++game->table_cnt[row];
    }

    return false;
}

void show_score(Game const *game) {
    for(int32_t i = 0; i < game->player_num; ++i) {
        if(i == 0)
            printf("Your Score: %d    ", game->score[i]);
        else
            printf("CPU%d Score: %d    ", i, game->score[i]);
    }
    puts("");
    return;
}

void show_table(Game const *game) {
    printf("Table:\n");
    for(int32_t i = 0; i < 4; i++) {
        for(int32_t j = 0; j < game->table_cnt[i]; ++j) {
            printf("%4d", game->table[i][j]);
        }
        puts("");
    }
}