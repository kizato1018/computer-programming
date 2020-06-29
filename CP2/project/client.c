#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "client.h"

#define HOST_IP "114.34.59.80"
#define PORT 8700

//char inputBuffer[256] = {};
Response response;
char message[] = {"Hi,this is server.\n"};
int sockfd = 0, forClientSockfd = 0;

struct sockaddr_in info;

Response OK_Response() {
    Response r = {1, "OK"};
    return r;
}
void print_CData(const CData *d) {
    printf("%d %s %s\n", d->id, d->name, d->input);
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

int client_socket_connect() {
    //socket的連線

    bzero(&info,sizeof(info));
    info.sin_family = PF_INET;
    info.sin_addr.s_addr = inet_addr(HOST_IP);
    info.sin_port = htons(PORT);
    int err = connect(sockfd,(struct sockaddr *)&info,sizeof(info));
    if(err == -1){
        printf("Connection error");
        return -1;
    }
    return 0;
}

// CData socket_get() {
//     forClientSockfd = accept(sockfd,(struct sockaddr*) &clientInfo, &addrlen);
//     if(!fork) {
//         recv(forClientSockfd, &inputBuffer, 1, 0);
//         print_CData(&inputBuffer);
//         response = OK_Response();
//         send(forClientSockfd, &response, 1, 0);
//         close(forClientSockfd);
//         return inputBuffer;
//     }
//     else 
//         close(forClientSockfd);
// }
Response socket_post(const CData *data) {
    send(sockfd, data, sizeof(CData), 0);
    recv(sockfd, &response, sizeof(Response), 0);
    return response;
}
void socket_close() {
    close(sockfd);
}
