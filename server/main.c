#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "../includes/socket.h"

#define LEILAO_DIR "../itens/"

int
main(int argc, char *argv[])
{
  if(argc < 2)
  {
    fprintf(stderr, "parametrs missing\n"); 
    exit(EXIT_FAILURE);
  }
  
  struct socket_ *s = create_sock(argv[1], NULL, SERVER_TYPE);
  set_bind(s);
  set_listen(s, 10);

  int client = accept(s->fd, (struct sockaddr*)&s->sock, &s->len);

  struct dirent *dr = NULL;
  DIR *dir = opendir(LEILAO_DIR);

  if(dir == NULL)
  {
    fprintf(stderr, "error: can't open dir\ncode_error: %d\nerror_description: %s\n",  errno, strerror(errno));
    close(s->fd);
    close(client);
    exit(EXIT_FAILURE);
  }

  FILE *file = NULL;
  dr = readdir(dir);
  unsigned char b = 0, *buffer = malloc(sizeof(unsigned char));
  char *path;
  size_t i = 0;

  while(dr != NULL)
  {
    if((strcmp(dr->d_name, ".") == 0) || (strcmp(dr->d_name, "..") == 0))
    {
      dr = readdir(dir);
      continue;
    }
    path = malloc((strlen(LEILAO_DIR) + strlen(dr->d_name)) * sizeof(unsigned char));
    sprintf(path, "%s%s", LEILAO_DIR, dr->d_name);

    file = fopen(path, "r");
    if(file == NULL)
    {
      fprintf(stderr, "error: can't open file\ncode_error: %d\nerror_description: %s\n",  errno, strerror(errno));
      close(s->fd);
      close(client);
      exit(EXIT_FAILURE);
    }
    while(fread(&b, sizeof(unsigned char), 1, file))
    {
      if(b == '\n')
      {
        send(client, buffer, i, 0);
        memset(buffer, 0, i);
        i = 0;
        continue;
      }
      buffer[i] = b;
      i++;
      buffer = realloc(buffer, ((i+1)*sizeof(unsigned char)));
    }


    /*
    * comecar as threds por aqui
    * timeout para lances 
    * enquanto recebe um lance
    * aproveitar e ja inicializar os clientes com as threds 
    */

    free(path);
    dr = readdir(dir);
  }

  closedir(dir);
  shutdown(s->fd, SHUT_RDWR);
  shutdown(client, SHUT_RDWR);
  close(client);
  close(s->fd);
  return EXIT_SUCCESS;
}
