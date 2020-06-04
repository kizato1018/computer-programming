#include "test.h"

int Global = 0;

int change(int a) {
    Global = 10 + a;
    return Global;
}