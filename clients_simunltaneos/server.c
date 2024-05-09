#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
int
main(int argc, char **argv)
{
  int server = socket(AF_INET, SOCK_STREAM, 0);

  if(server < 0)
  {
    return -1;
  }

  struct sockaddr_in s;
  s.sin_family = AF_INET;
  s.sin_addr.s_addr = INADDR_ANY;
  s.sin_port = htons(atoi(argv[1]));
  memset(s.sin_zero, 0, sizeof(s.sin_zero));
  
  socklen_t s_size = sizeof(s_size);

  if(bind(server, (struct sockaddr *)&s, s_size) < 0 )
  {
    return -1;
  } 
  
  if(listen(server, 10) < 0)
  {
    return -1;
  }

  int client = accept(server, (struct sockaddr *)&s, &s_size);

  send(client, "opa", 3, 0);
  char buf[256];
  recv(client, buf, 256, 0);

  printf("client :: %s", buf);
  close(client);
  close(server);
  return 0;
}
