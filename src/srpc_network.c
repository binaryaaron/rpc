
#include "srpc.h"
#include "srpc_network.h"

/* declared in header */
/* struct sockaddr_in client_addr, server_addr; */
/* int _socket, slen=sizeof(server_addr); */
/* int cli_serv_init = 0; */

int client_getserver(server_ip){

    memset((char *) &server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVICE_PORT);
    if (inet_aton(server_ip, &server_addr.sin_addr)==0) {
        printf("inet_aton() failed\n");
        exit(1);
    }
}

Srpc_Status Srpc_ClientInit(
    unsigned int timeout, /* milliseconds before retransmitting */
    unsigned int retries /* max # retries before SRPC_TIMEOUT */)
{
    if (cli_serv_init > 0) return SRPC_ERR_ALREADY_INITIALIZED;

    printf("cli_init func: trying\n");
    /* create a socket */

    if ((_socket=socket(AF_INET, SOCK_DGRAM, 0))==-1)
        printf("socket created\n");

    /* bind it to all local addresses and pick any port number */

    memset((char *)&client_addr, 0, sizeof(client_addr));
    client_addr.sin_family = AF_INET;
    client_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    client_addr.sin_port = htons(0);

    if (bind(_socket, (struct sockaddr *)&client_addr, sizeof(client_addr)) < 0) {
        perror("bind failed");
        return 0;
    }

    /* now define server_addr, the address to whom we want to send messages */
    /* For convenience, the host address is expressed as a numeric IP address */
    /* that we will convert to a binary format via inet_aton */


    return SRPC_ERR_OK;

}



Srpc_Status Srpc_ServerInit(
    unsigned short port,     /* port on which to listen */
    unsigned int timeout,     /* milliseconds before retransmitting */
    unsigned int retries    /* max # retries before SRPC_TIMEOUT */)
{

  return SRPC_ERR_OK;

}

