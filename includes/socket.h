#ifndef SOCKET_H
#define SOCKET_H

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
enum sock_type
{
  SERVER_TYPE,
  CLIENT_TYPE
};

struct socket_
{
  int fd;
  socklen_t len;
  struct sockaddr_in sock;
};

struct socket_ *create_sock(char *port, char *ip, int type);
void set_bind(struct socket_ *sock);
void set_listen(struct socket_ *sock, size_t backlog);

#endif // !SOCKET_H

