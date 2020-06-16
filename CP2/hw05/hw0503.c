#include <stdio.h>
#include "hw0503.h"

int main() {
    printf("hw0503 Debug test\n");
    debug_printf(DEBUG_LEVEL_ERROR, "file: %s, function: %s, line: %d   DEBUG_LEVEL_ERROR level: %d\n", __FILE__, __FUNCTION__, __LINE__, 1);
    debug_printf(DEBUG_LEVEL_INFO, "file: %s, function: %s, line: %d   DEBUG_LEVEL_INFO level: %d\n", __FILE__, __FUNCTION__, __LINE__, 2);
    debug_printf(DEBUG_LEVEL_VERBOSE, "file: %s, function: %s, line: %d   DEBUG_LEVEL_VERBOSE level: %d\n", __FILE__, __FUNCTION__, __LINE__, 3);
    debug_printf(DEBUG_LEVEL_VVERBOSE, "file: %s, function: %s, line: %d   DEBUG_LEVEL_VVERBOSE level: %d\n", __FILE__, __FUNCTION__, __LINE__, 4);
}