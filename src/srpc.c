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

Srpc_Status Srpc_ClientInit(
    unsigned int timeout, /* milliseconds before retransmitting */
    unsigned int retries /* max # retries before SRPC_TIMEOUT */)
{

  return SRPC_ERR_OK;
}

Srpc_Status Srpc_ServerInit(
    unsigned short port,     /* port on which to listen */
    unsigned int timeout,     /* milliseconds before retransmitting */
    unsigned int retries    /* max # retries before SRPC_TIMEOUT */)
{

  return SRPC_ERR_OK;

}

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

Srpc_Status Srpc_Export(
    char *name,         /* Name to export */
    Srpc_Function *function,     /* Function to invoke */
    void *functionData)     /* Opaque data passed to function */
{

return SRPC_ERR_OK;
}

Srpc_Status Srpc_Server(void)
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

char *Srpc_StatusMsg(Srpc_Status status)
{

return 'j';
}

