#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#define SERVER_IP "64.106.39.123"
#define NPACK 10
#define PORT 9930
#define BUFLEN 10

void die_print(char *s)
{
  printf("error");
  perror(s);
  exit(1);
}

int main(void)
{
  struct sockaddr_in si_other;
  int s, i, slen=sizeof(si_other);
  char buf[BUFLEN];

  for (i = 0; i < BUFLEN; i++){
    buf[i] = i+100;
  }

  printf("Testing\n");

  if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
  {
    die_print("socket error");
  }

  memset ((char *) &si_other, 0, sizeof(si_other));
  si_other.sin_family = AF_INET;
  si_other.sin_port = htons(PORT);
  if (inet_aton(SERVER_IP, &si_other.sin_addr) == 0)
  {
    fprintf(stderr, "inet_aton() failed\n");
    exit(1);
  }

  i = 0;
  for (; ;)
  {
    int n;
    printf("Sending packet %d\n", i);
    int j = 0;
    if (sendto(s, buf, BUFLEN, 0, &si_other, slen) == 1)
      die_print("sendto() failed");

    printf("trying to receive packet %d\n", i);

    n = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen);
    printf("Received packet from %s:%d\nData: %s\n", 
    inet_ntoa(si_other.sin_addr), 
    ntohs(si_other.sin_port), buf);

  }
  close(s);
  return 0;

}
