#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "srpc.h"
#include "marshalling.h"


void test_pack(Srpc_Arg *in, char *buf){

    printf("-----Testing argument packing-----\n\n");
    int err = Srpc_pack_args(in, buf);

    printf("-- packing status-----: %s\n\n\n", Srpc_StatusMsg(err));

}

void test_unpack_type(char *buf, Srpc_Arg *in){

    int dtype;
    /* print_args(in); */
    printf("----test marshalling----: unpacking type\n");
    dtype = srpc_unpack_type(buf);
    printf("Dtype unpacked: %d\n", dtype);


    assert(in->type == dtype);
/*     Srpc_Type type; // Type of argument */
/*     unsigned int size; // Size of arg, in bytes. */
/*     void *value; // Value */

}


void test_unpack(char *buf, Srpc_Arg *in, Srpc_Arg *out){

    print_args(in);
    printf("unpacking buffer into outarg\n");
    Srpc_unpack_args(buf, out);
    print_args(out);

    assert(in->type == out->type);
    assert(in->size == out->size);
    assert(in->value == out->value);
/*     Srpc_Type type; // Type of argument */
/*     unsigned int size; // Size of arg, in bytes. */
/*     void *value; // Value */

}


int main(void){


    printf("Initialzing arg\n");
    Srpc_Arg *in_arg;
    Srpc_Arg *out_arg;
    char *out_buf;
    out_buf = (char *) malloc(sizeof(12));

    char string[] = "fuck";
    int myint = 42;



    in_arg = arg_maker(SRPC_TYPE_INT, sizeof(myint), (void *) (intptr_t) myint);
    print_args(in_arg);
    /* printf("Size of 'fuck': %lu\n", sizeof(myint)); */

    test_pack(in_arg, out_buf);
    print_buffer_bytes(out_buf, 12);
    out_arg = _arg_maker();

    printf("Testing unpacking args\n");
    test_unpack_type(out_buf, in_arg);
    /* test_unpack(out_buf, in_arg, out_arg); */



    return 0;
}
