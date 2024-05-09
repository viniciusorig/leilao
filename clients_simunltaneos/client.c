#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int
main(int argc, char *argv[])
{
  int server = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in s;
  s.sin_addr.s_addr = inet_addr("127.0.0.1");
  s.sin_port = htons(atoi(argv[1]));
  s.sin_family = AF_INET;
  memset(s.sin_zero, 0, sizeof(s.sin_zero));
  socklen_t size = sizeof(struct sockaddr_in);
  if(connect(server, (struct sockaddr *)&s, size))
  {
    return -1;
  }

  printf("sever conectado\n");

  char b[] = "meme";
  if(send(server, b, 4, 0) == -1)
  {
    return -1;
  }

  char buffer[1024];
  size_t size_len = recv(server, buffer, sizeof(buffer), 0);
  printf("size buffer :: %ld\tbuffer :: %s\n", size_len, buffer);
  close(server);
  return 0;
}
