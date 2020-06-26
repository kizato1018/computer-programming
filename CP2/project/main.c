#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "game.h"
#include "agent.h"
#include "server.h"
#define NL puts("")

typedef struct _Card{
    int32_t id;
    int32_t card;
}Card;

int card_cmp(const void *a, const void *b) {
    return (*(Card *)a).card - (*(Card *)b).card;
}

int input(int *target, int mode) { 
    // return 0 is pick, 1 is exit.
    // mode 0 is stdin, 1 is socket. 
    CData cdata;
    char buffer[1024];
    if(mode == 0) {
        fgets(buffer, sizeof(buffer), stdin);
    }
    else if(mode == 1) {
        socket_get(&cdata);
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
    show_score(game);
    NL;
    show_table(game, stdout);
    NL;
    printf("Your hand cards:\n");
    show_card(player);
    NL;
}

int main() {
    // declare
    FILE *log = NULL;
    int32_t player_num = 0;
    bool gameover = false;
    Game game;
    Player *player = NULL;
    Player *CPU = NULL;
    Card *pick = NULL;
    int32_t player_pick = 0;
    int32_t round = 1;
    int32_t rank = 1;
    char buffer[1024] = {0};
    time_t now;

    // Start
    time(&now);
    if((log = fopen("log.dat", "a")) == NULL) {
        printf("log error\n");
        return 1;
    }
    system("clear");
    while(1) {
        printf("Please enter the number of players(2~10): ");
        // fgets(buffer, sizeof(buffer), stdin);
        // player_num = atoi(buffer);
        if(input(&player_num, 0) == 1)
            goto end;
        if(player_num < 2 || player_num > 10) {
            printf("Wrong players number.\n");
            system("clear");
        }
        else {
            fprintf(log, "player:%d\n", player_num);
            break;
        }
    }
    fprintf(log, "%s", ctime(&now));
    Game_setup(&game, player_num);
    player = calloc(1, sizeof(Player));
    CPU = calloc(player_num-1, sizeof(Player));
    pick = calloc(player_num, sizeof(Card));
    for(int32_t i = 0; i < player_num; ++i) {
        int32_t cards[10];
        fprintf(log, "%d:", i);
        for(int32_t j = 0; j < 10; ++j) {
            cards[j] = deal_card(&game);
            fprintf(log, "%3d%c", cards[j], " \n"[j == 9]);
        }
        if(i == 0)
            agent_deal(player, cards);
        else 
            agent_deal(CPU+i-1, cards);
    }

    // Game
    printf("Game Start!\n");
    while(!gameover) {
        // variable
        int32_t *index = NULL;

        // show information
        show(&game, player, round);
        fprintf(log, "\n%d\nScore:\n", round);
        for(int32_t i = 0; i < player_num; ++i)
            fprintf(log, "%d:%d %c", i, game.score[i], " \n"[i == player_num-1]);
        show_table(&game, log);
        // pick card
        fprintf(log, "pick:\n");
        bool isPick = false;
        while(!isPick) {
            printf("pick your card: ");
            if(input(&player_pick, 0) == 1)
                goto end;
            // fgets(buffer, sizeof(buffer), stdin);
            // player_pick = atoi(buffer);
            if(!check_card(player, player_pick)) {
                printf("pick wrong card.\n");
            }
            else {
                isPick = true;
                pick[0].card = player_pick;
                pick[0].id = 0;
                fprintf(log, "%d:%d  ", 0, pick[0].card);
            }
        }
        for(int i = 0; i < player_num-1; ++i) {
            pick[i+1].card = agent_pickcard(CPU+i, game.table);
            pick[i+1].id = i+1;
            fprintf(log, "%d:%d %c", i+1, pick[i+1].card, " \n"[i == player_num-2]);
        }

        // deal card
        printf("deal card\n");
        for(int32_t i = 0; i < player_num; ++i) {
            if(i == 0) {
                index = bsearch(&(pick[i].card), player->hand, 10, sizeof(int32_t), agent_cmp);
                *index = 0;
                // *index = deal_card(&game);
                agent_deal(player, player->hand);
            }
            else {
                index = bsearch(&(pick[i].card), CPU[i-1].hand, 10, sizeof(int32_t), agent_cmp);
                *index = 0;
                // *index = deal_card(&game);
                agent_deal(CPU+i-1, CPU[i-1].hand);
            }
        }
    
        // place card
        qsort(pick, player_num, sizeof(Card), card_cmp);
        for(int32_t i = 0; i < player_num; ++i) {
            show(&game, player, round);
            printf("Placing cards: ");
            for(int32_t j = i; j < player_num; ++j) {
                printf("%3d ", pick[j].card);
            }
            NL;
            if(place_card(&game, pick[i].id, pick[i].card)) { // if true, pick one row
                int32_t row = 0;
                isPick = false;
                if(pick[i].card == player_pick) {
                    printf("Your card is smaller than all row.\n");
                    while(!isPick) {
                        printf("Pick one row (1~4): ");
                        // scanf("%d", &row);
                        if(input(&row, 0) == 1)
                            goto end;
                        if(row < 1 || row > 4) 
                            printf("Wrong input.\n");
                        else
                            isPick = true;
                    }
                }
                else {
                    row = agent_pickrow(game.table);
                }
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
    show_score(&game);
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
    fprintf(log, "---------------------------------------\n");
    fclose(log);
    free(player);
    free(CPU);
    free(pick);
    return 0;
}