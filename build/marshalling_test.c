#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "srpc.h"
#include "dbg.h"
#include "marshalling.h"


void test_pack(Srpc_Arg *in, unsigned char *buf){

    debug("-----Testing argument packing-----\n\n");
    int err = Srpc_pack_args(in, buf);

    debug("-- packing status-----: %s\n\n\n", Srpc_StatusMsg(err));

}

void test_unpack_type(Srpc_Type type){

    Srpc_Arg *in_arg;
    Srpc_Arg *out_arg;
    unsigned char *out_buf;
    unsigned char string[] = "fuck";
    int myint = 42;
    /* out_buf = (unsigned char *) malloc(sizeof(12)); */
    int dtype;
    log_info("----test marshalling----: unpacking type\n");

    if (type == SRPC_TYPE_INT){
        debug("making int arg");
        in_arg = arg_maker(SRPC_TYPE_INT, sizeof(myint), (void *) (intptr_t) myint);
        print_args(in_arg);
        out_buf = (unsigned char *) malloc((3 * sizeof(int)));
    }
    if (type == SRPC_TYPE_DATA){
        debug("making data arg");
        in_arg = arg_maker(SRPC_TYPE_DATA, sizeof(string), (void *) string);
        print_args(in_arg);
        out_buf = (unsigned char *) malloc(sizeof(string + sizeof(int) + sizeof(int)));
    }

    /* print_args(in); */
    int err = Srpc_pack_args(in_arg, out_buf);
    debug("buffer after packing");
    print_buffer_bytes(out_buf, in_arg->size + 2 * sizeof(int));
    dtype = srpc_unpack_type(out_buf);


    assert(in_arg->type == dtype);
    log_info ("Unpack TYPE %d TEST PASSED: ", type);

}

void test_unpack_size(unsigned char *buf, Srpc_Arg *in){

    int size;
    /* print_args(in); */
    debug("----test marshalling----: unpacking size\n");
    int dtype = srpc_unpack_type(buf);
    debug("Dtype unpacked: %d\n", dtype);


    assert(in->type == dtype);
/*     Srpc_Type type; // Type of argument */
/*     unsigned int size; // Size of arg, in bytes. */
/*     void *value; // Value */

}



void test_unpack(Srpc_Type type){
    Srpc_Arg *in;
    Srpc_Arg *dest;
    unsigned char *out_buf;
    unsigned char string[] = "fuck";
    int myint = 42;
    /* out_buf = (unsigned char *) malloc(sizeof(12)); */
    int dtype;
    log_info("----test marshalling----: unpacking type\n");

    if (type == SRPC_TYPE_INT){
        debug("making int arg");
        in = arg_maker(SRPC_TYPE_INT, sizeof(myint), (void *) (intptr_t) myint);
        print_args(in);
        out_buf = (unsigned char *) malloc((3 * sizeof(int)));
    }
    if (type == SRPC_TYPE_DATA){
        debug("making data arg");
        in = arg_maker(SRPC_TYPE_DATA, sizeof(string), (void *) string);
        print_args(in);
        out_buf = (unsigned char *) malloc(sizeof(string + sizeof(int) + sizeof(int)));
    }

    /* print_args(in); */
    int err = Srpc_pack_args(in, out_buf);

    debug("buffer after packing");
    print_buffer_bytes(out_buf, in->size + 2 * sizeof(int));

    dest = unpack_args(out_buf);
    debug("printing dest arg");
    print_args(dest);

    assert(in->type == dest->type);
    assert(in->size == dest->size);
    assert((char *) in->value == (char *) dest->value);

    log_info ("Unpack %d TEST PASSED: ", type);


}


int main(void){

    test_unpack_type(SRPC_TYPE_INT);
    test_unpack_type(SRPC_TYPE_DATA);

    test_unpack(SRPC_TYPE_INT);
    test_unpack(SRPC_TYPE_DATA);



    return 0;
}
