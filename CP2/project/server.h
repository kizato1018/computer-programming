#ifndef __SERVER_H__
#define __SERVER_H__

typedef struct _CData {     // client data
    int id;
    char name[64];
    char input[1024];
}CData;

typedef struct _Response {
    int status;
    char msg[1024];
}Response;

Response OK_Response();
void print_CData(const CData *);
int socket_init();
int socket_connect(const int);
int socket_get(CData *, const int, const Response r);
void socket_close();

#endif