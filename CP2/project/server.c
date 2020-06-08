#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "server.h"

#define HOST_IP "10.0.2.15"
#define PORT 8700

CData inputBuffer;
Response response;
char message[] = {"Hi,this is server.\n"};
int sockfd = 0, forClientSockfd = 0;

struct sockaddr_in serverInfo;
struct sockaddr_storage clientInfo;
socklen_t addrlen = sizeof(clientInfo);

Response OK_Response() {
    Response r = {1, "OK"};
    return r;
}

void print_CData(const CData *d) {
    printf("%d %s %d\n", d->id, d->name, d->pick);
}
void print_Response(const Response *r) {
    printf("%d %s\n", r->status, r->msg);
}

int socket_init() {
     //socket的建立
    sockfd = socket(AF_INET , SOCK_STREAM , 0);
    if (sockfd == -1){
        printf("Fail to create a socket.");
        return -1;
    }
    return 0;
}

int socket_connect() {
    //socket的連線

    bzero(&serverInfo,sizeof(serverInfo));
    serverInfo.sin_family = PF_INET;
    serverInfo.sin_addr.s_addr = inet_addr(HOST_IP);
    serverInfo.sin_port = htons(PORT);
    bind(sockfd,(struct sockaddr *)&serverInfo,sizeof(serverInfo));
    if(listen(sockfd,10) == 0)
        printf("Listening\n");
    else {
        printf("Error\n");
        return -1;
    }
    forClientSockfd = accept(sockfd,(struct sockaddr*) &clientInfo, &addrlen);
    return 0;
}

int socket_get(CData *data) {
    
    while(1) {

        printf("OK\n");
        // if(!fork()) {
            recv(forClientSockfd, &inputBuffer, sizeof(CData), 0);
            
            response = OK_Response();
            send(forClientSockfd, &response, sizeof(Response), 0);
            memcpy(data, &inputBuffer, sizeof(CData));
            // close(forClientSockfd);
            printf("close\n");
            return 0;
        // }
        // else 
        //     close(forClientSockfd);
    }
}
