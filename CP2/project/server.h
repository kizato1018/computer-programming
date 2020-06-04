#ifndef __SERVER_H__
#define __SERVER_H__

typedef struct _CData {     // client data
    int id;
    char name[64];
    int pick;
}CData;

typedef struct _Response {
    int status;
    char msg[1024];
}Response;

void print_CData(const CData *);
int socket_init();
int socket_connect();
int socket_get(CData *);

#endif