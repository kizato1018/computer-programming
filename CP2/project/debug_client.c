#include <stdio.h>
#include "client.h"

int main() {
    CData data = {1, "kizato"};
    Response r;
    print_CData(&data);
    socket_init();
    client_socket_connect();

    r = socket_post(&data);
    print_Response(&r);
	
	while(1) { 
        fgets(data.input, sizeof(data.input), stdin);
        // scanf("%s", &data.input);
        print_CData(&data);
        r = socket_post(&data);
        print_Response(&r);
    }
}
