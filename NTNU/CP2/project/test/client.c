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

    //socket的建立
    int sockfd = 0;
    sockfd = socket(AF_INET , SOCK_STREAM , 0);

    if (sockfd == -1){
        printf("Fail to create a socket.");
    }

    //socket的連線

    struct sockaddr_in info;
    bzero(&info,sizeof(info));
    info.sin_family = PF_INET;

    //localhost test
    info.sin_addr.s_addr = inet_addr("114.34.59.80");
    info.sin_port = htons(8700);


    int err = connect(sockfd,(struct sockaddr *)&info,sizeof(info));
    if(err==-1){
        printf("Connection error");
    }


    //Send a message to server
    
    
    int nBytes = 0;
    while(1) {
        // char message[1024] = {"Hi there"};
        // char receiveMessage[100] = {"HHHHHHHHHHHHHHHH"};
        // fgets(message, 1024, stdin);
        int num = 0;
        int total = 0;
        scanf("%d", &num);
        send(sockfd, &num, sizeof(num), 0);
        recv(sockfd, &total, sizeof(total), 0);
        printf("total = %d\n", total);
        // nBytes = strlen(message) + 1;
        // printf("socket:%d\n", sockfd);
        // if(send(sockfd,message,nBytes,0) == -1) {
        //     printf("send error\n");
        //     return -1;
        // }
        // if(recv(sockfd,receiveMessage,sizeof(receiveMessage),0) == -1) {
        //     printf("recive error\n");
        //     return -1;
        // }
        // printf("%s",receiveMessage);
    }
    printf("close Socket\n");
    
    close(sockfd);
    return 0;
}