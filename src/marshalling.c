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

char * arg_to_c(Srpc_Arg *arg){
  return (char *)arg->value;
}

void print_args(Srpc_Arg *arg){
  printf("SRPC ARG:\n");
  printf("---- type: %d \n", arg->type);
  printf("---- size: %d \n", arg->size);
  printf("---- \n");

}

Srpc_Arg *_arg_maker(){
    Srpc_Arg *arg;
    arg = malloc(sizeof(Srpc_Arg));
    arg->type = 0;
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


int srpc_unpack_type(char *buf)
{
  char *bytes;
  int dtype;

  bytes = (char *) malloc(sizeof(int));

  memmove(bytes, buf, sizeof(int));
  /* memcpy(bytes, buf, 5); */
  /* buf += sizeof(int); */
  dtype = * (int *) bytes;
  print_buffer_bytes(bytes, sizeof(int));
  free(bytes);

  return dtype;

}


Srpc_Status Srpc_unpack_args(char *buf, Srpc_Arg *dest){
  char argtype[4];
  char argsize[4];
  char *argdata;
  unsigned int uint32;


  printf("Buffer address: %p\n", (void *)buf);

    memcpy(argtype, buf, sizeof(int));    
    /* unsigned int type_u32 = atoi(argtype); */
    dest->type = (int) argtype[0];
    /* printf("%d\n", type_u32); */
    buf += sizeof(int);

    printf("copying size to new arg\n");
    printf("Buffer address: %p\n", (void *)buf);

    memcpy(argsize, buf, sizeof(uint32));
    /* unsigned int size_u32 = atoi(argsize); */
    dest->size = (unsigned int) argsize[0];
    /* printf("%d\n", size_u32); */
    buf += sizeof(unsigned int);

  printf("Buffer address: %p\n", (void *)buf);
    // handle case here? decrement while loop and read sizeof(var) chunks?
    char data[dest->size];
    memcpy(data, buf, dest->size);
    dest->value = (void *)data;

    return 0;

}

Srpc_Status Srpc_pack_args(Srpc_Arg *pa, char *buf){
  /* code from patrick */
  int nErr = SRPC_ERR_OK;
  char *p = buf;

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



void print_buffer_bytes(char *bufptr, int n){
    int i = 0;
    char *byte_array = bufptr;

    printf("---Printing the bytes in the buffer---\n");
    while (i < n)
    {
         printf("%02X", (int)byte_array[i]);
         i++;
         if (i % 4 == 0) printf(" ");
    }
    printf("\n\n\n");


}

