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
#include "srpc_client.h"
#include "marshalling.h"
#include "hashmap.h"

#define HOSTNAME "127.0.0.1"

Srpc_net_info *client_netinfo;
Srpc_net_info *server_netinfo;
map_t function_table;

static void Error(char *msg, Srpc_Status status) {
  fprintf(stderr, "%s: %s\n", msg, Srpc_StatusMsg(status));
  exit(1);
}


void Srpc_FreeArgs(
    Srpc_Arg args[])        /* Arg array to be freed. */
{
// don't blow this up
}


Srpc_Status Srpc_Call(
    Srpc_Handle handle,        /* Returned by Srpc_Bind */
    Srpc_Arg inArgs[],         /* Input arguments */
    Srpc_Status *status,     /* (Out) RPC status from server */
    Srpc_Arg **outArgs)    /* (Out) Output arguments */
{

return SRPC_ERR_OK;
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


/*
 * helper function to allocate a new arg. 
 * initializes the arg to have size 0 and invalid type
 */
Srpc_Arg *_arg_maker(){
    Srpc_Arg *arg;
    arg = malloc(sizeof(Srpc_Arg));
    arg->type = -1;
    arg->size = 0;
    arg->value = NULL;
    return arg;
}


/*
 * intializes an Srpc_Arg with the values passed to it
 */
Srpc_Arg *arg_maker(Srpc_Type t, unsigned int size, void *data){
    Srpc_Arg *arg = _arg_maker();
    arg->type = t;
    arg->size = size;
    arg->value = data;
    return arg;
}


