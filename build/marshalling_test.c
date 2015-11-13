#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "srpc.h"
#include "marshalling.h"


void test_pack(Srpc_Arg *in, unsigned char *buf){

    printf("-----Testing argument packing-----\n\n");
    int err = Srpc_pack_args(in, buf);

    printf("-- packing status-----: %s\n\n\n", Srpc_StatusMsg(err));

}

void test_unpack_type(unsigned char *buf, Srpc_Arg *in){

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

void test_unpack_size(unsigned char *buf, Srpc_Arg *in){

    int size;
    /* print_args(in); */
    printf("----test marshalling----: unpacking size\n");
    int dtype = srpc_unpack_type(buf);
    printf("Dtype unpacked: %d\n", dtype);


    assert(in->type == dtype);
/*     Srpc_Type type; // Type of argument */
/*     unsigned int size; // Size of arg, in bytes. */
/*     void *value; // Value */

}



void test_unpack(unsigned char *buf, Srpc_Arg *in){

    Srpc_Arg *dest;
    print_args(in);
    printf("unpacking buffer into outarg\n");
    /* Srpc_unpack_args(buf, out); */
    dest = unpack_args(buf);

    assert(in->type == dest->type);
    assert(in->size == dest->size);
    assert(in->value == dest->value);
    printf("Unpacking works:\n");
    print_args(dest);
/*     Srpc_Type type; // Type of argument */
/*     unsigned int size; // Size of arg, in bytes. */
/*     void *value; // Value */

}


int main(void){


    printf("Initialzing arg\n");
    Srpc_Arg *in_arg;
    Srpc_Arg *out_arg;
    unsigned char *out_buf;
    out_buf = (unsigned char *) malloc(sizeof(12));

    unsigned char string[] = "fuck";
    int myint = 100000000;



    in_arg = arg_maker(SRPC_TYPE_INT, sizeof(myint), (void *) (intptr_t) myint);
    print_args(in_arg);
    /* printf("Size of 'fuck': %lu\n", sizeof(myint)); */

    test_pack(in_arg, out_buf);
    print_buffer_bytes(out_buf, 12);
    out_arg = _arg_maker();

    printf("Testing unpacking args\n");
    test_unpack_type(out_buf, in_arg);
    test_unpack(out_buf, in_arg);
    printf("Making a new arg\n");

    in_arg = arg_maker(SRPC_TYPE_DATA, sizeof(string), (void *) string);
    print_args(in_arg);
    out_buf = (unsigned char *) malloc(sizeof(string));
    test_unpack_type(out_buf, in_arg);
    test_unpack(out_buf, in_arg);


    return 0;
}
