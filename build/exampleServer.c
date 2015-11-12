#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "srpc.h"

#define MSG "Hello World!"

static void Error(char *msg, Srpc_Status status) {
  fprintf(stderr, "%s: %s\n", msg, Srpc_StatusMsg(status));
  exit(1);
}

static Srpc_Function     HelloWorldStub;
static char         *HelloWorld(void);

int main(int argc, char *argv[]) {

    Srpc_Status    status;

    status = Srpc_ServerInit(4242, 100, 5);
    if (status != SRPC_ERR_OK) {
    Error("Srpc_ServerInit failed", status);
    }
    status = Srpc_Export("hello", HelloWorldStub, NULL);
    if (status != SRPC_ERR_OK) {
    Error("Srpc_ServerInit failed", status);
    }
    printf("exported\n");

    printf("Server Ready \n");
    status = Srpc_Server();
    if (status != SRPC_ERR_OK) {
    Error("Srpc_Server failed", status);
    }
    return 0;
}

static Srpc_Status HelloWorldStub(
    void     *dummy,         // not used
    Srpc_Arg     inArgs[],        // input arguments 
    Srpc_Arg     **outArgs) {

    Srpc_Arg    *args;

    if (inArgs != NULL && inArgs[0].type != SRPC_TYPE_NONE) {
    return SRPC_ERR_WRONG_NUM_ARGS;
    }
    args = (Srpc_Arg *) malloc(2 * sizeof(Srpc_Arg));
    args[0].type = SRPC_TYPE_DATA;
    args[0].value = strdup(HelloWorld());
    args[0].size = strlen(args[0].value) + 1;
    args[1].type = SRPC_TYPE_NONE;
    *outArgs = args;
    return SRPC_ERR_OK;
}

static char *
HelloWorld(void) {
    return MSG;
}
 
