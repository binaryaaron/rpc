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


int * arg_to_int(Srpc_Arg *arg){
  return (int *)arg->value;
}

char * arg_to_c(Srpc_Arg *arg){
  return (char *)arg->value;
}

void print_args(Srpc_Arg *arg){
  printf("SRPC ARG:\n");
  printf("type: %d \n", arg->type);
  printf("size: %d \n", arg->size);

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

Srpc_Status Srpc_unpack_args(char *buf, Srpc_Arg *dest){
  char argtype[4];
  char argsize[4];
  char *argdata;
  char *curr;
  curr = buf;


    memcpy(argtype, buf, sizeof(argtype));    
    unsigned int type_u32 = atoi(argtype);
    dest->type = type_u32;
    printf("%d\n", type_u32);
    curr += sizeof(type_u32);

    memcpy(argsize, buf, sizeof(argsize));
    unsigned int size_u32 = atoi(argsize);
    dest->size = size_u32;
    printf("%d\n", size_u32);
    curr += sizeof(size_u32);

    // handle case here? decrement while loop and read sizeof(var) chunks?
    char data[size_u32];
    memcpy(data, curr, sizeof(size_u32));
    dest->value = (void *)data;
    printf("%s\n", data);

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




int main(void){



    char* buf = "00010004blah";
    char type[4], size[4];
    Srpc_Arg *a;

    memcpy(type, buf, sizeof(type));    
    unsigned int type_u32 = atoi(type);
    printf("%d\n", type_u32);

    buf += sizeof(type_u32) + 8;
    memcpy(size, buf, sizeof(size));    
    unsigned int size_u32 = atoi(size);
    printf("%d\n", size_u32);

    buf += sizeof(size_u32);
    char data[size_u32];
    memcpy(data, buf, sizeof(size_u32));    
    printf("%s\n", data);
    printf("------------------\n");

    char *buf2 = "00010004blah";
    a = _arg_maker();
    Srpc_unpack_args(buf2, a);
    print_args(a);



    return 0;
}
