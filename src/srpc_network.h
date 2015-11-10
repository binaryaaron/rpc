#ifndef SRPC_NETWORK_H
#define SRPC_NETWORK_H

#include <netdb.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "srpc.h"

struct sockaddr_in client_addr, server_addr;
int _socket;
int slen;
int cli_serv_init ;

#define SERVICE_PORT 2000
#define BUFSIZE 1024

#endif

Srpc_Status srcp_client_send(char *msg, int port);

typedef struct net_info{
  struct sockaddr_in si_other;
  /* struct hostent *server; */
  int socket_no;
} Srpc_net_info;

void init_netinfo(Srpc_net_info *ni, const char *hostname, uint16_t port);
int init_sockaddr (struct sockaddr_in *name, const char *hostname, uint16_t port);
int make_socket (uint16_t port);
