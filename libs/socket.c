#include "../includes/socket.h"
#include <stdio.h>

struct socket_ *
create_sock(char *port, char *ip,int type)
{
  struct socket_ *sock = calloc(1, sizeof(struct socket_));
  sock->fd = socket(AF_INET, SOCK_STREAM, 0);
  if(sock->fd < 0)
  {
    fprintf(stderr, "error: create sock file\ncode_error: %d\nerror_description: %s\n",  errno, strerror(errno));
    exit(EXIT_FAILURE);
  }
  sock->len = sizeof(struct sockaddr_in);
  sock->sock.sin_family = AF_INET;
  sock->sock.sin_port = htons(atoi(port));
  memset(sock->sock.sin_zero, 0, sizeof(sock->sock.sin_port));
  
  switch (type) 
  {
    case SERVER_TYPE:
      sock->sock.sin_addr.s_addr = INADDR_ANY;
      break;
    case CLIENT_TYPE:
      if(inet_pton(AF_INET, ip, &sock->sock.sin_addr) <= 0)
      {
        fprintf(stderr, "error:: covert ip\ncode_error: %d\nerror_description: %s", errno, strerror(errno));
        exit(EXIT_FAILURE);
      }
      break;
    default:
      fprintf(stderr, "error:: invalid_option");
      exit(EXIT_FAILURE);
  }


  return sock;
}

void
set_bind(struct socket_ *sock)
{
  if(sock == NULL)
  {
    fprintf(stderr, "struct sock is NULL");
    return;
  }

  if(bind(sock->fd, (struct sockaddr*)&sock->sock, sock->len) != 0)
  {
    fprintf(stderr, "error: bind\ncode_error: %d\nerror_description: %s\n",  errno, strerror(errno));
    close(sock->fd);
    exit(EXIT_FAILURE);   
  }
}

void
set_listen(struct socket_ *sock, size_t backlog)
{
  if(sock == NULL)
  {
    fprintf(stderr, "struct socket_ is NULL");
    return;
  }
  if(backlog < 1)
  {
    fprintf(stderr, "backlog is incorret");
    return;
  }

  if(listen(sock->fd, backlog) != 0)
  {
    fprintf(stderr, "error: listen\ncode_error: %d\nerror_description: %s\n",  errno, strerror(errno));
    close(sock->fd);
    exit(EXIT_FAILURE);   
  }
 
}
 
