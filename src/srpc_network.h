#include <netdb.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <stdlib.h>
#include "srpc.h"

struct sockaddr_in client_addr, server_addr;
int _socket, slen=sizeof(server_addr);
int cli_serv_init= 0;

#define SERVICE_PORT 2000
