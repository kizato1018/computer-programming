#include "40847025S.h"
#include <stdlib.h>
#include <time.h>

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
void CSIE_40847025S_setup(int32_t id) { 
    srand(time(NULL));
    return;
}
void CSIE_40847025S_deal(const int32_t card[10]) { return; }
int32_t CSIE_40847025S_pick(const int32_t table[4][5], const int32_t score[2], const int32_t last[8], const int32_t card[10]) {
    int32_t pick = rand() % 10;
    while(card[pick] == -1)
        pick = rand() % 10;
    return card[pick];
}
int32_t CSIE_40847025S_choose(const int32_t table[4][5], int32_t card) {
    int32_t Min = 100;
    int32_t Min_row = -1;
    for(int32_t i = 0; i < 4; ++i) {
        int32_t sum = 0;
        for(int32_t j = 0; j < 5; ++j) {
            sum += get_point(table[i][j]);
        }
        if(sum < Min) {
            Min = sum;
            Min_row = i;
        }
        else if(sum == Min && (rand() % 2)) {
            Min = sum;
            Min_row = i;
        }
    }
    return Min_row;
}