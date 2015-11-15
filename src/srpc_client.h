#ifndef SRPC_CLIENT_H
#define SRPC_CLIENT_H


Srpc_Status Srpc_ClientInit();

Srpc_Status Srpc_ClientExit(void);


int client_init (char *hostname, uint16_t port);







#endif
