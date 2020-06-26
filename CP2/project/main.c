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

int32_t input(int32_t *target, int8_t mode) { 
    // return 0 is pick, 1 is exit.
    // mode 0 is none, 1 is stdin, 2 is socket. 
    if(mode == 0) return 0;
    CData cdata;
    char buffer[1024];
    if(mode == 1) {
        fgets(buffer, sizeof(buffer), stdin);
    }
    else if(mode == 2) {
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
    Card *pick = NULL;
    int32_t round = 1;
    int32_t rank = 1;
    char buffer[1024] = {0};
    time_t now;
    bool online = false;
    int32_t (*Fpick)(Player *player, const int32_t table[4][5], int32_t (*input)(int32_t *target, int8_t mode));
    int32_t (*Fchoose)(Player *player, const int32_t table[4][5], int32_t (*input)(int32_t *target, int8_t mode));

    // Start
    time(&now);
    if((log = fopen("log.dat", "a")) == NULL) {
        printf("log error\n");
        return 1;
    }
    system("clear");
    while(1) {
        printf("Please enter the difficulty(1 easy, 2 normal, 3 hard): ");
        if(input(&(game.difficulty), 1) == 1)
            goto end;
        if(game.difficulty == 1) {
            Fpick = agent_pick_easy;
            Fchoose = agent_choose_mother;
            break;
        }
        else if(game.difficulty == 2) {
            Fpick = agent_pick_grandma;
            Fchoose = agent_choose_grandma;
            break;
        }
        else if(game.difficulty == 3) {
            Fpick = agent_pick_father;
            Fchoose = agent_choose_father;
            break;
        }
        else
            printf("wrong difficulty\n");
    }
    while(1) {
        printf("Please enter the number of players(2~10): ");
        if(input(&player_num, 1) == 1)
            goto end;
        if(player_num < 2 || player_num > 10) {
            printf("Wrong players number.\n");
        }
        else {
            fprintf(log, "player:%d\n", player_num);
            break;
        }
    }
    fprintf(log, "%s", ctime(&now));
    Game_setup(&game, player_num);
    player = calloc(player_num, sizeof(Player));
    pick = calloc(player_num, sizeof(Card));
    for(int32_t i = 0; i < player_num; ++i) {
        player[i].setup = agent_setup;
        player[i].deal = agent_deal;
        if(i == 0) {
            player[i].pick = player_pick;
            player[i].choose = player_choose;
        }
        else {
            player[i].pick = Fpick;
            player[i].choose = Fchoose;
        }
        int32_t cards[10];
        fprintf(log, "%d:", i);
        for(int32_t j = 0; j < 10; ++j) {
            cards[j] = deal_card(&game);
            fprintf(log, "%3d%c", cards[j], " \n"[j == 9]);
        }
        player[i].deal(player+i, cards);
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
        for(int i = 0; i < player_num; ++i) {
            pick[i].card = player[i].pick(player+i, game.table, input);
            pick[i].id = i;
            if(pick[i].card == -1)
                goto end;
            fprintf(log, "%d:%d %c", i, pick[i].card, " \n"[i == player_num-1]);
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
                row = player[pick[i].id].choose(player+i, game.table, input);
                if(row == -1)
                    goto end;
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
    free(pick);
    return 0;
}