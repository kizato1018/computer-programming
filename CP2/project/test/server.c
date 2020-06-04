#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc , char *argv[])
{
    static int total = 0;
    //socket的建立
    int num = 0;
    char inputBuffer[256] = {};
    char message[] = {"Hi,this is server.\n"};
    int sockfd = 0,forClientSockfd = 0;
    sockfd = socket(AF_INET , SOCK_STREAM , 0);

    if (sockfd == -1){
        printf("Fail to create a socket.");
    }

    //socket的連線
    struct sockaddr_in serverInfo;
    struct sockaddr_storage clientInfo;
    socklen_t addrlen = sizeof(clientInfo);
    //bzero(&serverInfo,sizeof(serverInfo));

    serverInfo.sin_family = PF_INET;
    inet_pton(AF_INET, "192.168.0.10", &(serverInfo.sin_addr.s_addr));
    // serverInfo.sin_addr.s_addr = inet_addr();
    serverInfo.sin_port = htons(8700);
    memset(serverInfo.sin_zero, '\0', sizeof serverInfo.sin_zero); 
    bind(sockfd,(struct sockaddr *)&serverInfo,sizeof(serverInfo));
    if(listen(sockfd,10) == 0) 
        printf("Listening\n");
    else
        printf("Error\n");

    while(1) {
        // printf("Hi\n");
        forClientSockfd = accept(sockfd,(struct sockaddr*) &clientInfo, &addrlen);
        //send(forClientSockfd,message,sizeof(message),0);
        
         if(!fork()) {
            int nBytes = 1;
            /*loop while connection is live*/
            printf("Ok\n");
            while(nBytes != 0) {
                nBytes = recv(forClientSockfd, &num, sizeof(num), 0);
                printf("num: %d\n", num);
                total += num;
                printf("total: %d\n", total);
                send(forClientSockfd, &total, sizeof(total), 0);
                // nBytes = recv(forClientSockfd,inputBuffer,256,0);
                // //printf("ip:%d\n", clientInfo.sin_addr.s_addr);
                // printf("Get:%s\n",inputBuffer);
                // for (int i=0;i<nBytes-1;i++){
                //     inputBuffer[i] = toupper(inputBuffer[i]);
                // }
                //send(forClientSockfd,inputBuffer,nBytes,0);
                
            }
            close(forClientSockfd);
            return 0;
         }
         else {
            printf("Not Ok\n");
            close(forClientSockfd);
         }
        
    }
    return 0;
}