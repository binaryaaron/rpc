#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <arpa/inet.h>
#include "dbg.h"


#include "srpc.h"
#include "marshalling.h"

/* typedef int Srpc_Type; */

/* #define SRPC_TYPE_NONE        0 */
/* #define SRPC_TYPE_INT         1 */
/* #define SRPC_TYPE_DATA        2 */

/* typedef struct Srpc_Arg { */
/*     Srpc_Type type; // Type of argument */
/*     unsigned int size; // Size of arg, in bytes. */
/*     void *value; // Value */
/* } Srpc_Arg; */


int * arg_to_int(Srpc_Arg *arg){
  return (int *)arg->value;
}

unsigned char * arg_to_c(Srpc_Arg *arg){
  return (unsigned char *)arg->value;
}

void print_args(Srpc_Arg *arg){
  debug("SRPC ARG:\n");
  debug("---- type: %d \n", arg->type);
  debug("---- size: %d \n", arg->size);
  if (arg->value != NULL){
    if (arg->type == SRPC_TYPE_INT)
      debug("---- value: %d \n", arg->value);
    if (arg->type == SRPC_TYPE_DATA)
      debug("---- value: %s\n", arg->value);
  }
  else {

      debug("---- value: is null\n\n");
  }
  debug("---- \n");

}

Srpc_Arg *_arg_maker(){
    Srpc_Arg *arg;
    arg = malloc(sizeof(Srpc_Arg));
    arg->type = -1;
    arg->size = -1;
    arg->value = NULL;
    return arg;
}



Srpc_Arg *arg_maker(Srpc_Type t, unsigned int size, void *data){
    Srpc_Arg *arg;
    arg = malloc(sizeof(Srpc_Arg));
    arg->type = t;
    arg->size = size;
    arg->value = data;
    return arg;
}


int srpc_unpack_type(unsigned char *buf)
{
  unsigned char bytes[4];
  int dtype = 0;

  /* bytes = (unsigned char *) malloc(sizeof(int)); */

  /* print_buffer_bytes(buf, 4* sizeof(int)); */
  /* memmove(&dtype, buf, sizeof(int)); */
  memcpy(bytes, buf, sizeof(int));
  dtype |= bytes[3];
  /* print_buffer_bytes(buf, sizeof(int)); */
  /* print_buffer_bytes(bytes, sizeof(int)); */
  /* free(bytes); */

  return dtype;

}

int srpc_unpack_argsize(unsigned char *buf)
{
  unsigned char bytes[4];
  int argsize = 0;

  memcpy(bytes, buf, sizeof(int));
  argsize = bytes[3];

  return argsize;

}

void * srpc_unpack_value(unsigned char *buf, Srpc_Type type, int size){

  unsigned char bytes[size];
  memcpy(bytes, buf, size);
  int val = 0;
  char *data;
  switch(type) {
      case SRPC_TYPE_INT:
          val |= bytes[0] << 24;
          val |= bytes[1] << 16;
          val |= bytes[2] << 8;
          val |= bytes[3] << 0;
          return (void *) (intptr_t) val;
      case SRPC_TYPE_DATA:
          data = (char *) malloc(size);
          memcpy(data, buf, size);
          debug("printing data buffer for size %d", size);
          print_buffer_bytes(data, size);
          return (void *)data;

      case SRPC_TYPE_NONE:
          return NULL;
  }

}



Srpc_Arg *unpack_args(unsigned char *buf){
  unsigned char *ptr = buf;
  Srpc_Type dt = srpc_unpack_type(ptr);
  ptr+= sizeof(int);
  int data_size = srpc_unpack_argsize(ptr);
  ptr+= sizeof(int);
  void *val = srpc_unpack_value(ptr, dt, data_size);

  Srpc_Arg *arg = arg_maker(dt, data_size, val);
  return arg;

}

Srpc_Status Srpc_pack_args(Srpc_Arg *pa, unsigned char *buf){
  /* code from patrick */
  int nErr = SRPC_ERR_OK;
  unsigned char *p = buf;

  while (pa->type != SRPC_TYPE_NONE){
    * (unsigned int *) p = htonl(pa->type);
    p += sizeof(unsigned int);
    * (unsigned int *) p = htonl(pa->size);
    p += sizeof(unsigned int);
    // assign based on data type
    switch (pa->type){

      case SRPC_TYPE_INT:
        /* debug("pack args: switching on int type\n"); */
        // assign based on size
        switch (pa->size){
          case 1:
            *p = htonl((unsigned char) (unsigned int) pa->value);
            break;
          case 2:
            *(unsigned short *)p = htons((unsigned short) (unsigned int)pa->value);
            break;
          case 4:
            *(unsigned int *)p = htonl((unsigned int)pa->value);
            break;
          default:
            nErr = SRPC_ERR_INVALID_ARG_TYPE;
            goto error;
        }
        break;

      case SRPC_TYPE_DATA:
        /* debug("pack args: switching on data type\n"); */
        memcpy(p, pa->value, pa->size);
        break;
      default:
        nErr = SRPC_ERR_INVALID_ARG_TYPE;
        goto error;
    }
    p += pa->size;
    pa++;
  }
  return SRPC_ERR_OK;
  error:
    return nErr;
}



void print_buffer_bytes(unsigned char *bufptr, int n){
    int i = 0;
    unsigned char *byte_array = bufptr;

    while (i < n)
    {
         printf("%02X ", (int)byte_array[i]);
         i++;
         if (i % 4 == 0) printf(" -- ");
    }
    printf("\n\n\n");


}

