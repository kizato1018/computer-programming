#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "game.h"
#include "agent.h"
#include "server.h"
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
    else if(mode == 1) {
        socket_get(&cdata, id, OK_Response());
        strcpy(buffer, cdata.input);
    }
    if(strcmp(buffer, "exit\n") == 0)
        return 1;
    *target = atoi(buffer);
    return 0;
}


void show(Game *game, Player *player, int32_t round) {
    system("clear");
    printf("Round %d\n", round);
    show_score(game, 0);
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
    Player *player = NULL;
    Card *pick = NULL;
    int32_t round = 1;
    int32_t rank = 1;
    char buffer[1024] = {0};
    time_t now;
    bool online = true;
    int32_t (*Fpick)(Player *player, const int32_t table[4][5], int32_t (*input)(int32_t *target, const int32_t id, const int8_t mode));
    int32_t (*Fchoose)(Player *player, const int32_t table[4][5], int32_t (*input)(int32_t *target, const int32_t id, const int8_t mode));
    CData data[2];

    // Start
    if(online) {
        socket_init();
    }

    system("clear");

    while(1) {
        printf("Please enter the number of players(2~10): ");
        if(input(&player_num, 0, 0) == 1)
            goto end;
        if(player_num < 2 || player_num > 10) {
            printf("Wrong players number.\n");
        }
        else {
            break;
        }
    }
    Game_setup(&game, player_num);
    player = calloc(player_num, sizeof(Player));
    pick = calloc(player_num, sizeof(Card));
    if(online) {
        socket_connect(player_num);
    }
    for(int32_t i = 0; i < player_num; ++i) {
        player[i].id = i;
        player[i].online = online;
        player[i].setup = agent_setup;
        player[i].deal = agent_deal;
        if(online || i == 0) {
            player[i].pick = player_pick;
            player[i].choose = player_choose;
        }
        else {
            player[i].pick = Fpick;
            player[i].choose = Fchoose;
        }
        
        int32_t cards[10];
        for(int32_t j = 0; j < 10; ++j) {
            cards[j] = deal_card(&game);
        }

        player[i].deal(player+i, cards);
        

        // online
        if(online) {
            CData data;
            Response r = {0, ""};
            sprintf(r.msg, "%d\n", player_num);
            for(int j = 0; j < 4; ++j) {
                char tmp[64];
                sprintf(tmp, "%d%c", game.table[j][0], " \n"[j == 3]);
                strcat(r.msg, tmp);
            }
            for(int j = 0; j < 10; ++j) {
                char tmp[64];
                sprintf(tmp, "%d%c", cards[j], " \n"[j == 9]);
                strcat(r.msg, tmp);
            }
            socket_get(&data, i, r);
        }
    }

    // Game
    printf("Game Start!\n");
    while(!gameover) {
        // variable
        int32_t *index = NULL;

        // show information
        show(&game, player, round);
        memset(buffer, 0, sizeof(buffer));
        for(int i = 0; i < player_num; ++i) {
            pick[i].card = player[i].pick(player+i, game.table, input);
            pick[i].id = i;
            if(pick[i].card == -1)
                gameover = true;
            if(online) {
                char tmp[64] = {};
                sprintf(tmp, "%d %d\n",pick[i].id, pick[i].card);
                if(i == 0) 
                    strcpy(buffer, tmp);
                else 
                    strcat(buffer, tmp);
            }
        }
        if(online) {
            for(int i = 0; i < player_num; ++i) {
                CData data;
                Response r;
                r.status = 0;
                strcpy(r.msg, buffer);
                socket_get(&data, i, r);
            }
        }
        if(gameover) goto end;
    
        // place card
        qsort(pick, player_num, sizeof(Card), card_cmp);
        for(int32_t i = 0; i < player_num; ++i) {
            show(&game, player, round);
            show_place_card(pick, i, player_num);
            if(place_card(&game, pick[i].id, pick[i].card)) { // if true, pick one row
                int32_t row = 0;
                row = player[pick[i].id].choose(player+pick[i].id, game.table, input);
                if(online) {
                    CData data;
                    Response r;
                    r.status = 0;
                    sprintf(r.msg, "%d", row);
                    for(int i = 0; i < player_num; ++i)
                        socket_get(&data, i, r);
                }
                if(row == -1)
                    gameover = true;
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
    for(int32_t i = 1; i < player_num; ++i) {
        if(game.score[0] > game.score[i])
            ++rank;
    }
    show_score(&game, 0);
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
    free(player);
    free(pick);
    socket_close();
    return 0;
}