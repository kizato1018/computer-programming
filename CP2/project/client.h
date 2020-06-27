#ifndef __CLIENT_H__
#define __CLIENT_H__

typedef struct _CData {     // client data
    int id;
    char name[64];
    char input[1024];
}CData;

typedef struct _Response {
    int status;
    char msg[1024];
}Response;

void print_CData(const CData *);
void print_Response(const Response *);
int socket_init();
int client_socket_connect();
Response socket_post(const CData *);

#endif