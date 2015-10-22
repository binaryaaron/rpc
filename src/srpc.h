/*
 * srpc.h --
 *
 *	Declarations for SRPC. 
 *
 *	DO NOT MODIFY THIS FILE!!
 *
 */

#ifndef _SRPC
#define _SRPC

/*
 * Status codes
 */

typedef unsigned int Srpc_Status;

#define SRPC_ERR_OK			0
#define SRPC_ERR_TIMEOUT		1
#define SRPC_ERR_REBOOT			2
#define SRPC_ERR_ALREADY_INITIALIZED	3
#define SRPC_ERR_PORT_INUSE		4
#define SRPC_ERR_ALREADY_BOUND		5
#define SRPC_ERR_NO_FUNCTION		6
#define SRPC_ERR_NO_SERVER		7
#define SRPC_ERR_ARGS_TOO_BIG		8
#define SRPC_ERR_INVALID_ARG_TYPE	9
#define SRPC_ERR_UNINITIALIZED		10
#define SRPC_ERR_ALREADY_EXPORTED	11
#define SRPC_ERR_WRONG_NUM_ARGS		12


/*
 * Argument type
 */
typedef int Srpc_Type;

#define SRPC_TYPE_NONE		0
#define SRPC_TYPE_INT		1
#define SRPC_TYPE_DATA		2

/*
 * Argument structure
 */

typedef struct Srpc_Arg {
    Srpc_Type type; 	/* Type of argument */
    unsigned int size; 	/* Size of arg, in bytes. */
    void *value; 	/* Value */
} Srpc_Arg;



/*
 * Handle returned by Srcp_Bind.
 */

typedef void *Srpc_Handle;

/*
 * Maximum size of marshalled SRPC arguments, in bytes.
 */

#define SRPC_MAX_ARG_SIZE	1024

/*
 * Exported function definition
 */

typedef Srpc_Status (Srpc_Function)(
    void *functionData, 	/* Opaque data passed by Srpc_Export */
    Srpc_Arg inArgs[], 		/* Input args */
    Srpc_Arg **outArgs); 	/* (Out) Output args */

/* Begin CPP gate */
#ifdef __cplusplus
extern "C" {
#endif

/*
 * SRPC library interface.
 */	
Srpc_Status Srpc_ClientInit(
    unsigned int timeout, 	/* milliseconds before retransmitting */
    unsigned int retries); 	/* max # retries before SRPC_TIMEOUT */

Srpc_Status Srpc_ServerInit(
    unsigned short port, 	/* port on which to listen */
    unsigned int timeout, 	/* milliseconds before retransmitting */
    unsigned int retries); 	/* max # retries before SRPC_TIMEOUT */

void Srpc_FreeArgs(
    Srpc_Arg args[]);		/* Arg array to be freed. */

Srpc_Status Srpc_Bind(
    char *function, 		/* Name of function to which to bind */
    char *server, 		/* Server's DNS name */
    unsigned short port, 	/* Server's port */
    Srpc_Handle *handle); 	/* (Out) handle for Srpc_Call */

Srpc_Status Srpc_Call(
    Srpc_Handle handle,		/* Returned by Srpc_Bind */
    Srpc_Arg inArgs[], 		/* Input arguments */
    Srpc_Status *status, 	/* (Out) RPC status from server */
    Srpc_Arg **outArgs);	/* (Out) Output arguments */

Srpc_Status Srpc_Export(
    char *name, 		/* Name to export */
    Srpc_Function *function, 	/* Function to invoke */
    void *functionData); 	/* Opaque data passed to function */

Srpc_Status Srpc_Server(void);

Srpc_Status Srpc_ClientExit(void);

Srpc_Status Srpc_ServerExit(void);

char *Srpc_StatusMsg(Srpc_Status status);

/* end CPP gate */
#ifdef __cplusplus
}
#endif


#endif /* _SRPC */

