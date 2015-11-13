#ifndef _MARSHALLING
#define _MARSHALLING


#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "srpc.h"

/* typedef int Srpc_Type; */

/* #define SRPC_TYPE_NONE        0 */
/* #define SRPC_TYPE_INT         1 */
/* #define SRPC_TYPE_DATA        2 */

/* typedef struct Srpc_Arg { */
/*     Srpc_Type type; // Type of argument */
/*     unsigned int size; // Size of arg, in bytes. */
/*     void *value; // Value */
/* } Srpc_Arg; */


int *arg_to_int(Srpc_Arg *arg);

char *arg_to_c(Srpc_Arg *arg);

void print_args(Srpc_Arg *arg);

/*
 * helper function to allocate a new Arg
 */
Srpc_Arg *_arg_maker();



/*
 * helper function to allocate and assign a new Arg
 */
Srpc_Arg *arg_maker(Srpc_Type t, unsigned int size, void *data);

/*
 * unpack function into pre-allocated arg pointed at (dest)
 */
Srpc_Status Srpc_unpack_args(char *buf, Srpc_Arg *dest);
int srpc_unpack_type(char *buf);

Srpc_Status Srpc_pack_args(Srpc_Arg *pa, char *buf);


void print_buffer_bytes(char *bufptr, int n);




#endif
