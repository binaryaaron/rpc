#include <stdlib.h>
#include <stdio.h>
#include "srpc.h"



#define SERVER_IP "127.0.0.1"
#define PORT 4000

int main(){


  int stat = Srpc_ServerInit(PORT, 10, 10);
  printf("Status: %d\n", stat);


  return 0;

}
