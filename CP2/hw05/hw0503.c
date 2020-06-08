#include <stdio.h>
#include "hw0503.h"

int main() {
    debug_printf(DEBUG_LEVEL_VVERBOSE, "DEBUG_LEVEL_VVERBOSE level: %d\n", 1);
    debug_printf(DEBUG_LEVEL_VERBOSE, "DEBUG_LEVEL_VERBOSE level: %d\n", 2);
    debug_printf(DEBUG_LEVEL_INFO, "DEBUG_LEVEL_INFO level: %d\n", 3);
    debug_printf(DEBUG_LEVEL_ERROR, "DEBUG_LEVEL_ERROR level: %d\n", 4);
}