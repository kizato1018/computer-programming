#include "game.h"
#include <stdio.h>
#include <unistd.h>
#define RED "\033[0;41m"
#define GREEN "\033[0;42;30m"
#define YELLOW "\033[0;43;30m"
#define BLUE "\033[0;44m"
#define RESET "\033[m"
#define color_print(out, color, fmt, ...) fprintf(out, color fmt RESET, __VA_ARGS__)

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

int32_t get_point(int32_t const card) {
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
        score += get_point(game->table[row][i]);
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
        memset(game->table[i], 0, sizeof(game->table[i]));
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

void show_table(Game const *game, FILE *out) {
    fprintf(out, "Table:\n");
    for(int32_t i = 0; i < 4; i++) {
        for(int32_t j = 0; j < game->table_cnt[i]; ++j) {
            if(out == stdout) {
                switch (get_point(game->table[i][j])) {
                case 2:
                    color_print(out, BLUE, "%3d", game->table[i][j]);
                    fprintf(out, " ");
                    break;
                case 3:
                    color_print(out, GREEN, "%3d", game->table[i][j]);
                    fprintf(out, " ");
                    break;
                case 5:
                    color_print(out, RED, "%3d", game->table[i][j]);
                    fprintf(out, " ");
                    break;
                case 7:
                    color_print(out, YELLOW, "%3d", game->table[i][j]);
                    fprintf(out, " ");
                    break;
                
                default:
                    fprintf(out, "%3d", game->table[i][j]);
                    fprintf(out, " ");
                    break;
                }
            }
            else {
                fprintf(out, "%3d", game->table[i][j]);
                fprintf(out, " ");
            }

        }
        fputs("\n", out);
    }
}

void show_place_card(const Card *pick, const int32_t i, const int32_t num) {
    printf("Placing cards: ");
    for(int32_t j = i; j < num; ++j) {
        switch (get_point(pick[j].card)) {
        case 2:
            color_print(stdout, BLUE, "%3d", pick[j].card);
            fprintf(stdout, " ");
            break;
        case 3:
            color_print(stdout, GREEN, "%3d", pick[j].card);
            fprintf(stdout, " ");
            break;
        case 5:
            color_print(stdout, RED, "%3d", pick[j].card);
            fprintf(stdout, " ");
            break;
        case 7:
            color_print(stdout, YELLOW, "%3d", pick[j].card);
            fprintf(stdout, " ");
            break;
        
        default:
            fprintf(stdout, "%3d", pick[j].card);
            fprintf(stdout, " ");
            break;
        }
    }
    puts("");
}