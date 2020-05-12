#include <stdio.h>
#include <unistd.h>
#include "game.h"
#include "agent.h"
#define NL puts("")

typedef struct _Card{
    int32_t id;
    int32_t card;
}Card;

int card_cmp(const void *a, const void *b) {
    return (*(Card *)a).card - (*(Card *)b).card;
}

void show(Game *game, Player *player, int32_t round) {
    system("clear");
    printf("Round %d\n", round);
    show_score(game);
    NL;
    show_table(game);
    NL;
    printf("Your hand cards:\n");
    show_card(player);
    NL;
}

int main() {
    // declare
    int32_t player_num = 0;
    bool gameover = false;
    Game game;
    Player *player;
    Player *CPU;
    Card *pick;
    int32_t player_pick = 0;
    int32_t round = 1;
    int32_t rank = 1;

    // Start
    printf("Please enter number of plyer: ");
    scanf("%d", &player_num);
    Game_setup(&game, player_num);
    player = calloc(1, sizeof(Player));
    CPU = calloc(player_num-1, sizeof(Player));
    pick = calloc(player_num, sizeof(Card));
    for(int32_t i = 0; i < player_num; ++i) {
        int32_t cards[10];
        for(int32_t j = 0; j < 10; ++j) {
            cards[j] = deal_card(&game);
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

        // pick card
        bool isPick = false;
        while(!isPick) {
            printf("pick your card: ");
            scanf("%d", &player_pick);
            if(!check_card(player, player_pick)) {
                printf("pick wrong card.\n");
            }
            else {
                isPick = true;
                pick[0].card = player_pick;
                pick[0].id = 0;
            }
        }
        for(int i = 0; i < player_num-1; ++i) {
            pick[i+1].card = agent_pickcard(CPU+i, game.table);
            pick[i+1].id = i+1;
        }

        // deal card
        printf("deal card\n");
        for(int32_t i = 0; i < player_num; ++i) {
            if(i == 0) {
                index = bsearch(&(pick[i].card), player->hand, 10, sizeof(int32_t), agent_cmp);
                *index = deal_card(&game);
                agent_deal(player, player->hand);
            }
            else {
                index = bsearch(&(pick[i].card), CPU[i-1].hand, 10, sizeof(int32_t), agent_cmp);
                *index = deal_card(&game);
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
                        scanf("%d", &row);
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
    
}