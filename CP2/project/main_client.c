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
    // show_card(player);
    // NL;
}

int main() {
    // declare
    FILE *log = NULL;
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
    fgets(data.name, sizeof(data.name), stdin);

    r = socket_post(&data);
    print_Response(&r);
    data.id = atoi(r.msg);
    // // Start
    // time(&now);
    // if((log = fopen("log.dat", "a")) == NULL) {
    //     printf("log error\n");
    //     return 1;
    // }
    // fprintf(log, "%s", ctime(&now));
    // system("clear");
    // while(1) {
    //     int32_t choose = 0;
    //     printf("1) Single player\n");
    //     printf("2) Online mode\n");
    //     input(&choose, 0, 0);
    //     if(choose == 1) {
    //         online = false;
    //         break;
    //     }
    //     else if(choose == 2) {
    //         online = true;
    //         break;
    //     }
    //     else 
    //         printf("wrong mode\n");
    // }
    // while(!online) {
    //     printf("Please enter the difficulty(1 mother, 2 father, 3 grandma): ");
    //     if(input(&(game.difficulty), 0, online) == 1)
    //         goto end;
    //     if(game.difficulty == 1) {
    //         Fpick = agent_pick_mother;
    //         Fchoose = agent_choose_mother;
    //         fprintf(log, "difficulty: 1\n");
    //         break;
    //     }
    //     else if(game.difficulty == 2) {
    //         Fpick = agent_pick_father;
    //         Fchoose = agent_choose_father;
    //         fprintf(log, "difficulty: 2\n");
    //         break;
    //     }
    //     else if(game.difficulty == 3) {
    //         Fpick = agent_pick_grandma;
    //         Fchoose = agent_choose_grandma;
    //         fprintf(log, "difficulty: 3\n");
    //         break;
    //     }
    //     else
    //         printf("wrong difficulty\n");
    // }
    

    // while(1) {
    //     printf("Please enter the number of players(2~10): ");
    //     if(input(&player_num, 0, 0) == 1)
    //         goto end;
    //     if(player_num < 2 || player_num > 10) {
    //         printf("Wrong players number.\n");
    //     }
    //     else {
    //         fprintf(log, "player:%d\n", player_num);
    //         break;
    //     }
    // }
    r = socket_post(&data);
    player_num = atoi(r.msg);
    printf("Player number: %d\n", player_num);

    // Game_setup(&game, player_num);
    // player = calloc(player_num, sizeof(Player));
    pick = calloc(player_num, sizeof(Card));
    player.id = data.id;
    player.online = false;
    player.setup = agent_setup;
    player.deal = agent_deal;
    player.pick = player_pick;
    player.choose = player_choose;
    // socket_connect(player_num);
    // for(int32_t i = 0; i < player_num; ++i) {
    //     player[i].id = i;
    //     player[i].online = online;
    //     player[i].setup = agent_setup;
    //     player[i].deal = agent_deal;
    //     if(online || i == 0) {
    //         player[i].pick = player_pick;
    //         player[i].choose = player_choose;
    //     }
    //     else {
    //         player[i].pick = Fpick;
    //         player[i].choose = Fchoose;
    //     }
        
    //     int32_t cards[10];
    //     fprintf(log, "%d:", i);
    //     for(int32_t j = 0; j < 10; ++j) {
    //         cards[j] = deal_card(&game);
    //         fprintf(log, "%3d%c", cards[j], " \n"[j == 9]);
    //     }

    //     player[i].deal(player+i, cards);
    // }

    // Game
    printf("Game Start!\n");
    while(!gameover) {
        // variable
        // int32_t *index = NULL;

        // show information

        r = socket_post(&data);
        printf("%s", r.msg);

        // show(&game, player, round);
        // show_card(player);
        // show_card(player+1);
        // NL;
        // fprintf(log, "\n%d\nScore:\n", round);
        // for(int32_t i = 0; i < player_num; ++i)
        //     fprintf(log, "%d:%d %c", i, game.score[i], " \n"[i == player_num-1]);
        // show_table(&game, log);

        // pick card

        while(1) {
            int player_pick = -1;
            if(input(&player_pick, player.id, 0) == 1)
                goto end;
            else if(check_card(&player, player_pick)) {
                pick[0].id = player.id;
                pick[0].card = player_pick;
                sprintf(data.input, "%d", player_pick);
                break;
            }
        }
        // post pick card
        r = socket_post(&data);
        printf("%s", r.msg);
        memset(data.input, 0, sizeof(data.input));
        

        // fprintf(log, "pick:\n");
        // for(int i = 0; i < player_num; ++i) {
        //     pick[i].card = player[i].pick(player+i, game.table, input);
        //     pick[i].id = i;
        //     if(pick[i].card == -1)
        //         goto end;
        //     fprintf(log, "%d:%d %c", i, pick[i].card, " \n"[i == player_num-1]);
        // }

        // wait for everyone
        r = socket_post(&data);
        printf("%s", r.msg);

        
        // place card
        qsort(pick, player_num, sizeof(Card), card_cmp);
        for(int32_t i = 0; i < player_num; ++i) {
            show(&game, player, round);
            show_card(player);
            show_card(player+1);
            NL;
            show_place_card(pick, i, player_num);
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