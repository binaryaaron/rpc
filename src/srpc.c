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

#include "srpc.h"
#include "srpc_network.h"
#include "hashmap.h"

#define HOSTNAME "127.0.0.1"

Srpc_net_info *client_netinfo;
Srpc_net_info *server_netinfo;
map_t function_table;

static void Error(char *msg, Srpc_Status status) {
  fprintf(stderr, "%s: %s\n", msg, Srpc_StatusMsg(status));
  exit(1);
}

typedef struct f_values
{
    Srpc_Function *f;
    void *f_data;
} f_values;


void Srpc_FreeArgs(
    Srpc_Arg args[])        /* Arg array to be freed. */
{
// don't blow this up
}

Srpc_Status Srpc_Bind(
    char *function,       /* Name of function to which to bind */
    char *server,         /* Server's DNS name */
    unsigned short port,  /* Server's port */
    Srpc_Handle *handle)  /* (Out) handle for Srpc_Call */
{

  return SRPC_ERR_OK; // okay

}

Srpc_Status Srpc_Call(
    Srpc_Handle handle,        /* Returned by Srpc_Bind */
    Srpc_Arg inArgs[],         /* Input arguments */
    Srpc_Status *status,     /* (Out) RPC status from server */
    Srpc_Arg **outArgs)    /* (Out) Output arguments */
{

return SRPC_ERR_OK;
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

Srpc_Status Srpc_Server(void)
{
    /* now loop, receiving data and printing what we received */
  return 0;
}

Srpc_Status Srpc_ClientExit(void)
{
return SRPC_ERR_OK;
}

Srpc_Status Srpc_ServerExit(void)
{

return SRPC_ERR_OK;

}

char *Srpc_StatusMsg(Srpc_Status status) {
  switch (status){
    case 0: return "SRPC_ERR_OK";
    case 1: return "SRPC_ERR_TIMEOUT";
    case 2: return "SRPC_ERR_REBOOT";
    case 3: return "SRPC_ERR_ALREADY_INITIALIZED";
    case 4: return "SRPC_ERR_PORT_INUSE";
    case 5: return "SRPC_ERR_ALREADY_BOUND";
    case 6: return "SRPC_ERR_NO_FUNCTION";
    case 7: return "SRPC_ERR_NO_SERVER";
    case 8: return "SRPC_ERR_ARGS_TOO_BIG";
    case 9: return "SRPC_ERR_INVALID_ARG_TYPE";
    case 10: return "SRPC_ERR_UNINITIALIZED";
    case 11: return "SRPC_ERR_ALREADY_EXPORTED";
    case 12: return "SRPC_ERR_WRONG_NUM_ARGS";
    default: return NULL;
  }
}


Srpc_Status Srpc_ClientInit(
    unsigned int timeout, /* milliseconds before retransmitting */
    unsigned int retries /* max # retries before SRPC_TIMEOUT */)
{
    if (cli_serv_init > 0) return SRPC_ERR_ALREADY_INITIALIZED;
    printf("cli_init func: trying\n");
    client_netinfo = malloc(sizeof(Srpc_net_info));
    init_netinfo(client_netinfo, HOSTNAME, SERVICE_PORT);

    return SRPC_ERR_OK;

}


Srpc_Status Srpc_ServerInit(
    unsigned short port,     /* port on which to listen */
    unsigned int timeout,     /* milliseconds before retransmitting */
    unsigned int retries    /* max # retries before SRPC_TIMEOUT */)
{

    printf("init server func: trying\n");
    server_netinfo = malloc(sizeof(Srpc_net_info));
    init_netinfo(server_netinfo, HOSTNAME, port);
    function_table = hashmap_new();
    return SRPC_ERR_OK;

}

