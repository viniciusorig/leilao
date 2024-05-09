#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "../includes/socket.h"

int
main(int argc, char *argv[])
{
  if(argc < 2)
  {
    fprintf(stderr, "parameters missing\n");
    exit(EXIT_FAILURE);  
  }

  struct socket_ *sk = create_sock(argv[1], "127.0.0.1", CLIENT_TYPE);
  if(connect(sk->fd, (const struct sockaddr *)&sk->sock, sk->len) != 0)
  {
    fprintf(stderr, "error:: connect\ncode_error: %d\nerror_description: %s", errno, strerror(errno));
    exit(EXIT_FAILURE);
  }
  fprintf(stdout, "servidor conectado\n");
  unsigned char buffer[1024];
  while (recv(sk->fd, buffer, 1024, 0) > 0) 
  {
    printf("%s\n", buffer);
    memset(buffer, 0, 1024);
  } 
  close(sk->fd);
  return 0;
}
