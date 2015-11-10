
#include "srpc.h"
#include "srpc_network.h"

/* typedef struct net_info{ */
/*   struct sockaddr_in si_other; */
/*   /1* struct hostent *server; *1/ */
/*   int socketfd; */
/* } Srp_net_info; */

void init_netinfo(Srpc_net_info *ni, const char *hostname, uint16_t port)
{
  printf("initializing custom netinfo struct\n");
  ni->socket_no = init_sockaddr(&ni->si_other, hostname, port);
  /* ni->socketfd = make_socket(port); */

}

int init_sockaddr (struct sockaddr_in *name, const char *hostname, uint16_t port)
{
  /* from gnu */
  struct hostent *hostinfo;

  int sock = socket(AF_INET, SOCK_DGRAM, 0);
  /* memset((char *)name, 0, sizeof(*name)); */
  name->sin_family = AF_INET;
  /* name->sin_addr.s_addr = htonl(INADDR_ANY); */
  name->sin_port = htons(port);
  hostinfo = gethostbyname (hostname);
  if (hostinfo == NULL)
  {
    fprintf (stderr, "Unknown host %s.\n", hostname);
    exit (EXIT_FAILURE);
  }
  name->sin_addr = *(struct in_addr *) hostinfo->h_addr;
  if (bind (sock, (struct sockaddr *) name, sizeof (*name)) < 0)
    {
      perror ("bind");
      exit (EXIT_FAILURE);
    }
  return sock;
}


int make_socket (uint16_t port)
{
  /* from gnu */
  int sock;
  struct sockaddr_in name;

  /* Create the socket. */
  sock = socket(AF_INET, SOCK_DGRAM, 0);
  if (sock < 0)
    {
      perror ("socket");
      exit (EXIT_FAILURE);
    }

  /* Give the socket a name. */
  name.sin_family = AF_INET;
  name.sin_port = htons (port);
  name.sin_addr.s_addr = htonl (INADDR_ANY);
  if (bind (sock, (struct sockaddr *) &name, sizeof (name)) < 0)
    {
      perror ("bind");
      exit (EXIT_FAILURE);
    }

  return sock;
}


