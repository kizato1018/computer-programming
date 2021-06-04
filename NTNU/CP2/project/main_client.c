#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "game.h"
#include "agent.h"
#include "client.h"
#define NL puts("")

int card_cmp(const void *a, const void *b) {
    return (*(Card *)a).card - (*(Card *)b).card;
}

int32_t input(int32_t *target, const int32_t id, const int8_t mode) { 
    // return 0 is pick, 1 is exit.
    // mode 0 is stdin, 1 is socket. 
    CData cdata;
    char buffer[1024];
    if(mode == 0) {
        if(!fgets(buffer, sizeof(buffer), stdin)) {
            printf("End of input.\n");
            return 1;
        }
    }
    if(strcmp(buffer, "exit\n") == 0) {
        printf("online mode can't exit\n");
        *target = -1;
        return 0;
    }
    *target = atoi(buffer);
    return 0;
}

void show(Game *game, Player *player, int32_t round) {
    system("clear");
    printf("Round %d\n", round);
    show_score(game, player->id);
    NL;
    show_table(game, stdout);
    NL;
    show_card(player);
    NL;
}

int main() {
    // declare
    int32_t player_num = 0;
    bool gameover = false;
    Game game;
    Player player;
    Card *pick = NULL;
    int32_t round = 1;
    int32_t rank = 1;
    char buffer[1024] = {0};
    time_t now;
    bool online = false;
    int32_t (*Fpick)(Player *player, const int32_t table[4][5], int32_t (*input)(int32_t *target, const int32_t id, const int8_t mode));
    int32_t (*Fchoose)(Player *player, const int32_t table[4][5], int32_t (*input)(int32_t *target, const int32_t id, const int8_t mode));
    CData data;
    Response r;

    
    // Start
    socket_init();
    client_socket_connect();
    data.id = -1;

    r = socket_post(&data);
    print_Response(&r);
    data.id = atoi(r.msg);
    // // Start

    r = socket_post(&data);
    memset(data.input, 0, sizeof(data.input));
    printf("%s\n", r.msg);
    char *token = strtok(r.msg, " \n");
    player_num = atoi(token);
    token = strtok(NULL, " \n");
    printf("Player number: %d\n", player_num);

    game.player_num = player_num;
    memset(game.score, 0, player_num * sizeof(int32_t));
    pick = calloc(player_num, sizeof(Card));
    player.id = data.id;
    player.online = false;
    player.setup = agent_setup;
    player.deal = agent_deal;
    player.pick = player_pick;
    player.choose = player_choose;
    
    for(int i = 0; i < 4; ++i) {
        memset(game.table[i], 0, player_num * sizeof(int32_t));
        game.table[i][0] = atoi(token);
        game.table_cnt[i] = 1;
        token = strtok(NULL, " \n");
    }
    int32_t cards[10];
    for(int i = 0; i < 10; ++i) {
        cards[i] = atoi(token);
        token = strtok(NULL, " \n");
    }
    player.deal(&player, cards);

    // Game

    printf("Game Start!\n");
    while(!gameover) {
        // show information
        show(&game, &player, round);

        while(1) {
            int player_pick_card = -1;
            player_pick_card = player.pick(&player, game.table, input);
            if(player_pick_card == -1)
                gameover = true;
            else {
                pick[0].id = player.id;
                pick[0].card = player_pick_card;
                sprintf(data.input, "%d", player_pick_card);
                break;
            }
        }
        
        // post pick card
        r = socket_post(&data);
        printf("%s", r.msg);
        memset(data.input, 0, sizeof(data.input));
        
        r = socket_post(&data);
        memset(data.input, 0, sizeof(data.input));
        printf("%s", r.msg);
        char *token = strtok(r.msg, " \n");
        for(int i = 0; i < player_num; ++i) {
            pick[i].id = atoi(token);
            token = strtok(NULL, " \n");
            pick[i].card = atoi(token);
            token = strtok(NULL, " \n");
        }
        
        // place card
        qsort(pick, player_num, sizeof(Card), card_cmp);
        for(int32_t i = 0; i < player_num; ++i) {
            show(&game, &player, round);
            show_place_card(pick, i, player_num);
            if(place_card(&game, pick[i].id, pick[i].card)) { // if true, pick one row
                if(pick[i].id == player.id) {
                    sprintf(data.input, "%d", player.choose(&player, game.table, input));
                    r = socket_post(&data);
                    memset(data.input, 0, sizeof(data.input));
                }
                r = socket_post(&data);
                memset(data.input, 0, sizeof(data.input));
                int row = atoi(r.msg);
                game.score[pick[i].id] += new_row(&game, row-1, pick[i].card);
            }
            sleep(1);
        }
        
        // 1 round finish
        ++round;
        if(round > 10)
            gameover = true;
    }

    // Score
    system("clear");
    for(int32_t i = 0; i < player_num; ++i) {
        if(game.score[player.id] > game.score[i])
            ++rank;
    }
    show_score(&game, player.id);
    NL;
    if(rank == 1)
        printf("You win the 1st place!\n");
    else if(rank == 2)
        printf("You win the 2nd place!\n");
    else if(rank == 3)
        printf("You win the 3rd place!\n");
    else
        printf("You win the %dst place!\n", rank);

    // end 
end:
    free(pick);
    socket_close();
    return 0;
}