#ifndef __40847025S_H__
#define __40847025S_H__

#include <stdint.h>

void CSIE_40847025S_setup(int32_t);
void CSIE_40847025S_deal(const int32_t card[10]);
int32_t CSIE_40847025S_pick(const int32_t table[4][5], const int32_t score[2], const int32_t last[8], const int32_t card[10]);
int32_t CSIE_40847025S_choose(const int32_t table[4][5], int32_t card);

#endif