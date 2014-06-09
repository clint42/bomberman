/*
** main.cpp for bomberman_ex in /home/prieur_b/tek2/cpp/bomberman/test
** 
** Made by aurelien prieur
** Login   <prieur_b@epitech.net>
** 
** Started on  Mon Jun  9 13:38:42 2014 aurelien prieur
** Last update Mon Jun  9 14:00:20 2014 buret_j
*/

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>

static int cs = -1;
void	catch_sig(int signum)
{
  close(cs);
}

int	connection(char **av)
{
  int                   sock;
  struct protoent       *proto;
  struct sockaddr_in    sin;

  if ((proto = getprotobyname("tcp")) == NULL)
    return (-1);
  if ((sock = socket(AF_INET, SOCK_STREAM, proto->p_proto)) == -1)
    return (-1);
  sin.sin_family = AF_INET;
  if (av[2] != NULL)
    sin.sin_port = htons(atoi(av[2]));
  else
    sin.sin_port = htons(6697);
  if (inet_aton(av[1], (struct in_addr *)(&sin.sin_addr.s_addr)) == 0)
    {
      close(sock);
      printf("inet_aton error\n");
      return (-1);
    }
  if (connect(sock, (struct sockaddr *)(&sin), sizeof(sin)) == -1)
    {
      close(sock);
      printf("connect error\n");
      return (-1);
    }
  cs = sock;
  return (sock);
}

int	main(int ac, char **av)
{
  int	sock;
  char  buf[500];

  if ((sock = connection(av)) != -1)
    {
      signal(SIGINT, catch_sig);
    }
  bzero(buf, 500);
  read(sock, buf, 499);
  printf("%s", buf);
  return (0);
}
