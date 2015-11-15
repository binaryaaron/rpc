

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
#include "srpc_network.h"
#include "srpc_client.h"
#include "dbg.h"
#include "hashmap.h"
#include "marshalling.h"


#define HOSTNAME "127.0.0.1"

Srpc_net_info *client_netinfo;
Srpc_net_info *server_netinfo;
map_t function_table;

Srpc_Status Srpc_ClientInit( unsigned int timeout, unsigned int retries)
{
    /* if (cli_serv_init > 0) return SRPC_ERR_ALREADY_INITIALIZED; */
    debug("cli_init func: trying");
    client_netinfo = malloc(sizeof(Srpc_net_info));
    int init = client_init(HOSTNAME, SERVICE_PORT);

    return SRPC_ERR_OK;

}





Srpc_Status Srpc_Bind(
    char *function,       /* Name of function to which to bind */
    char *server,         /* Server's DNS name */
    unsigned short port,  /* Server's port */
    Srpc_Handle *handle)  /* (Out) handle for Srpc_Call */
{

  Srpc_Arg *bind_arg = arg_maker(SRPC_TYPE_DATA, strlen(function) + 1 , (void *) function);

  return SRPC_ERR_OK; // okay

}


int client_init (char *hostname, uint16_t port)
{
  /* from gnu */
  int sock;
  server_netinfo = malloc(sizeof(Srpc_net_info));

  struct sockaddr_in self;

  if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    log_warn("cannot create socket");
    return 0;
  }
  server_netinfo->socket_no = sock;

  memset((char *)&self, 0, sizeof(self));
  self.sin_family = AF_INET;
  self.sin_addr.s_addr = htonl(INADDR_ANY);
  self.sin_port = htons(0);

  if (bind(sock, (struct sockaddr *)&self, sizeof(self)) < 0) {
    log_warn("bind failed");
    return 0;
  }

  return 0;

}

