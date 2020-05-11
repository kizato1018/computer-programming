#include <stdio.h>
#include <unistd.h>
#include "game.h"
#include "agent.h"

int main() {
    // declare
    int32_t player_num = 0;
    bool gameover = false;
    Game game;
    Player *player;
    Player *CPU;
    int32_t *pick;

    // Start
    printf("Please enter number of plyer: ");
    scanf("%d", &player_num);
    Game_setup(&game, player_num);
    player = calloc(1, sizeof(Player));
    CPU = calloc(player_num-1, sizeof(Player));
    pick = calloc(player_num, sizeof(int32_t));
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
        system("clear");
        show_score(&game);
        show_table(&game);

        // pick card
        bool isPick = false;
        while(!isPick) {
            printf("Your hand cards:\n");
            show_card(player);
            printf("pick your card: ");
            scanf("%d", &pick[0]);
            if(!check_card(player, pick[0])) {
                printf("pick wrong card.\n");
            }
            else 
                isPick = true;
        }
        for(int i = 0; i < player_num-1; ++i) {
            pick[i+1] = agent_pick(CPU+i, game.table);
        }

        // deal card
        printf("deal card\n");
        for(int32_t i = 0; i < player_num; ++i) {
            int32_t cards[10] = {0};
            if(i == 0) {
                //printf("%d ", pick[i]);
                index = bsearch(&(pick[i]), player->hand, 10, sizeof(int32_t), agent_cmp);
                // memcpy(cards, player->hand, 10*sizeof(int32_t));
            }
            else {
                index = bsearch(&(pick[i]), CPU[i-1].hand, 10, sizeof(int32_t), agent_cmp);
                // memcpy(cards, CPU[i-1].hand, 10*sizeof(int32_t));
            }
            
            // if(index != NULL) printf("%d ", *index);
            // else printf("NULL\n");
            *index = deal_card(&game);

        }
    
        place_card(&game, pick);
        puts("");
        sleep(3);
    }
    
}