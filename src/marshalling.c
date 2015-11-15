#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <arpa/inet.h>

#include "dbg.h"
#include "srpc.h"
#include "marshalling.h"

int *arg_to_int(Srpc_Arg *arg){
  return (int *)arg->value;
}

char *arg_to_str(Srpc_Arg *arg){
  return (char *) arg->value;
}

void print_args(Srpc_Arg *arg){
  log_info("SRPC ARG at %p:", (void *) arg);

  log_info("---- type: %d", arg->type);
  log_info("---- size: %d", arg->size);
  if (arg->value != NULL){
    if (arg->type == SRPC_TYPE_INT)
      log_info("---- value: %d", arg->value);
    if (arg->type == SRPC_TYPE_DATA)
      log_info("---- value: %s", arg->value);
  }
  else {

      log_info("---- value: is null");
  }
  log_info("----");

}


/*
 * function that gets the type of an arg
 */
int srpc_unpack_type(unsigned char *buf)
{
  unsigned char bytes[4];
  int dtype = 0;

  memcpy(bytes, buf, sizeof(int));
  /*
   * we only need to take the 'first' byte of the number; it's
   * only 0, 1, or 2
   */
  dtype |= bytes[3];

  return dtype;

}

/*
 * function that gets the number of bytes contained in the message
 */
int srpc_unpack_argsize(unsigned char *buf)
{
  unsigned char bytes[4];
  int argsize = 0;

  /* could forgo memcpy i think and just assign it directly, but whatever*/
  memcpy(bytes, buf, sizeof(int));
  argsize = bytes[3];

  return argsize;

}

/*
 * uses a bit of bitshifting to get out integers values and memcpying to get
 * out void values
 */
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



/* function that wraps the unpacking functions. takes the buffer and returns a
 * packed argument 
 */
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

int check_if_header(Srpc_Arg *arg){



}




/*
 * packs the argument into a buffer. code comes from Patrick Bridges.
 */
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



/* helper function to print out a buffer's byte contents */
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

