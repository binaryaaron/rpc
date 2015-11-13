#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <arpa/inet.h>


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
  printf("SRPC ARG:\n");
  printf("---- type: %d \n", arg->type);
  printf("---- size: %d \n", arg->size);
  if (arg->value != NULL){
    if (arg->type == SRPC_TYPE_INT)
      printf("---- value: %d \n", arg->value);
    if (arg->type == SRPC_TYPE_DATA)
      printf("---- value: %s\n", arg->value);
  }
  else {

      printf("---- value: is null\n\n");
  }
  printf("---- \n");

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

int srpc_unpack(unsigned char *buf)
{
  unsigned char bytes[4];
  int dtype = 0;

  memcpy(bytes, buf, sizeof(int));
  dtype |= bytes[3];
  print_buffer_bytes(bytes, sizeof(int));

  return dtype;

}

int srpc_unpack_type(unsigned char *buf)
{
  unsigned char bytes[4];
  int dtype = 0;

  /* bytes = (unsigned char *) malloc(sizeof(int)); */

  /* memmove(&dtype, buf, sizeof(int)); */
  memcpy(bytes, buf, sizeof(int));
  dtype |= *(buf + 3);
  print_buffer_bytes(bytes, sizeof(int));
  /* free(bytes); */

  return dtype;

}

int srpc_unpack_argsize(unsigned char *buf)
{
  unsigned char bytes[4];
  int argsize = 0;

  /* bytes = (unsigned char *) malloc(sizeof(int)); */

  /* memmove(&dtype, buf, sizeof(int)); */
  memcpy(bytes, buf, sizeof(int));
  /* buf += sizeof(int); */
  /* dtype = bytes[0] | ( (int)bytes[1] << 8 ) | ( (int)bytes[2] << 16 ) | ( (int)bytes[3] << 24 ); */
  argsize = bytes[3];
  /* print_buffer_bytes(bytes, sizeof(int)); */
  /* free(bytes); */

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
        printf("debug: pack args: switching on int type\n");
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

    printf("---Printing the bytes in the buffer---\n");
    while (i < n)
    {
         printf("%02X", (int)byte_array[i]);
         i++;
         if (i % 4 == 0) printf(" ");
    }
    printf("\n\n\n");


}

