#include <stdio.h>
#define RED "\033[41m"
#define GREEN "\033[42m"
#define Yellow "\033[43m"
#define BLUE "\033[44m"
#define PURPLE "\033[45m"
#define RESET "\033[m"
#define print(color, fmt, ...) printf(color fmt RESET, __VA_ARGS__)

int main() {
    print(RED, "Hello %d", 9527);
    puts("");
}