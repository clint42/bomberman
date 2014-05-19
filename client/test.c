/*
** test.c for bomberman_ex in /home/prieur_b/tek2/cpp/bomberman/client
** 
** Made by aurelien prieur
** Login   <prieur_b@epitech.net>
** 
** Started on  Mon May 19 18:00:15 2014 aurelien prieur
** Last update Mon May 19 18:30:27 2014 aurelien prieur
*/

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <sys/select.h>

int                     init(char **av)
{
  int                   sock;
  struct protoent       *proto;
  struct sockaddr_in    sin;

  if ((proto = getprotobyname("tcp")) == NULL)
    return (-1);
  if ((sock = socket(AF_INET, SOCK_STREAM, proto->p_proto)) == -1)
    return (-1);
  printf("socket ok\n");
  sin.sin_family = AF_INET;
  if (av[2] != NULL)
    sin.sin_port = htons(atoi(av[2]));
  else
    sin.sin_port = htons(6697);
  printf("htons ok\n");
  if (inet_aton(av[1], (struct in_addr *)(&sin.sin_addr.s_addr)) == 0)
    {
      close(sock);
      perror("inet_aton fail");
      return (-1);
    }
  printf("inet_aton ok\n");
  if (connect(sock, (struct sockaddr *)(&sin), sizeof(sin)) == -1)
    {
      close(sock);
      perror("connect fail");
      return (-1);
    }
  return (sock);
}

int		main(int ac, char **av)
{
  int		cs;
  int		ret;
  fd_set	readfds;
  fd_set	writefds;
  char		buf[1024];

  cs = init(av);
  if (cs == -1)
    printf("SHIT\n");
  printf("Connected !\n");
  FD_ZERO(&readfds);
  FD_SET(cs, &readfds);
  FD_SET(cs, &writefds);
  while (select(cs + 1, &readfds, &writefds, NULL, NULL) != -1)
    {
      if (FD_ISSET(cs, &readfds))
	{
	  printf("Possible to read\n");
	  if ((ret = read(cs, buf, 1024)) == 0)
	    {
	      printf("Read == 0\n");
	      return (0);
	    }
	  else if (ret == -1)
	    {
	      perror("read fail");
	      return (0);
	    }
	}
      scanf("%s", buf);
      if (FD_ISSET(cs, &writefds))
	{
	  printf("Possible to write\n");
	  if ((ret = write(cs, buf, strlen(buf))) == 0)
	     {
	      printf("Write == 0\n");
	      return (0);
	    }
	  else if (ret == -1)
	    {
	      perror("Write fail");
	      return (0);
	    }
	}
    }
  perror("Select failed");
  return (0);
}
