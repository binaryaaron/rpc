#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "marshalling.h"
#include "hashmap.h"
#include "srpc.h"
#include "srpc_network.h"
#include "dbg.h"

#define HOSTNAME "127.0.0.1"

/* typedef struct net_info{ */
/*   struct sockaddr_in si_other; */
/*   /1* struct hostent *server; *1/ */
/*   int socketfd; */
/* } Srp_net_info; */

Srpc_net_info *client_netinfo;
Srpc_net_info *server_netinfo;
map_t function_table;

typedef struct f_values
{
    Srpc_Function *f;
    void *f_data;
} f_values;


int server_init (struct sockaddr_in *name, const char *hostname, uint16_t port)
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



Srpc_Status Srpc_ServerInit(
    unsigned short port,     /* port on which to listen */
    unsigned int timeout,     /* milliseconds before retransmitting */
    unsigned int retries    /* max # retries before SRPC_TIMEOUT */)
{

    printf("init server func: trying\n");
    server_init(server_netinfo, HOSTNAME, port);
    function_table = hashmap_new();
    return SRPC_ERR_OK;

}


/* duplicate replies = sequence numbers on things */

/* ####### select example ########### */
/* timeouts in ms to different socket format */
/* while (retries > 0 ){ */
/*   sendto(sock, ...); */
/*   FDSET(fds, sock); */
/*   n = select(&fds, ..., timeout); */
/*   if (n) { */
/*     recvfrom(...); */
/*     break; */
/*   } */
/*   else retries--; */
/* } */


Srpc_Status Srpc_Server(void)
{
    int bytes_received;            /* # bytes received */
    int _socket = server_netinfo->socket_no;                /* our socket */
    int msgcnt = 0;            /* count # of messages we received */
    unsigned char buf[BUFSIZE];    /* receive buffer */
    struct sockaddr_in server_addr = server_netinfo->self;    /* our address */
    struct sockaddr_in remote_addr = server_netinfo->remote;    /* remote address */
    socklen_t addrlen = sizeof(remote_addr);        /* length of addresses */

    for (;;) {
        printf("waiting on port %d\n", SERVICE_PORT);
        bytes_received = recvfrom(_socket,
                                  buf,
                                  BUFSIZE,
                                  0,
                                  (struct sockaddr *)&remote_addr,
                                  &addrlen);
        if (bytes_received > 0) {
            buf[bytes_received] = 0;
            printf("received message: \"%s\" (%d bytes)\n", buf, bytes_received);
        }
        else{
            printf("uh oh - something went wrong!\n");
            return 1;
        }

        sprintf(buf, "ack %d", msgcnt++);

        printf("sending response \"%s\"\n", buf);
        int send_sign = sendto(_socket,
                               buf,
                               strlen(buf),
                               0,
                               (struct sockaddr *)&remote_addr,
                               addrlen);
        if (send_sign < 0) perror("sendto");
    }
    /* never exits */
    /* now loop, receiving data and printing what we received */
  return 0;
}


  /*
   * may need a bit more here - perhaps the little tuple DS i have isn't going
   * to work on retrevial
   * functiondata: pointer to opaque data
   */
Srpc_Status Srpc_Export(char *name, Srpc_Function *function, void *functionData)
{
    int error;
    printf("Debug: exporting function %s to function table\n", name);
    f_values *function_holder;
    function_holder = malloc(sizeof(f_values));
    function_holder->f = function;
    function_holder->f_data = functionData;

    error = hashmap_put(function_table, name, (void *) function_holder);
    if (error != 0){
      printf("error assigning function to table\n");
      return SRPC_ERR_ALREADY_INITIALIZED;
    }

    error = hashmap_get(function_table, name, (void **) function_holder);
    if (error != 0){
      printf("error assigning function to table\n");
      return SRPC_ERR_ALREADY_INITIALIZED;
    }

    printf("getting function back\n");
    if (function_holder->f == function) printf("success on getting function\n");
    function_holder = NULL;
    free(function_holder);


  return SRPC_ERR_OK;
}

