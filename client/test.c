/*
** test.c for bomberman_ex in /home/prieur_b/tek2/cpp/bomberman/client
** 
** Made by aurelien prieur
** Login   <prieur_b@epitech.net>
** 
** Started on  Mon May 19 18:00:15 2014 aurelien prieur
** Last update Fri May 23 15:09:59 2014 aurelien prieur
*/

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <poll.h>
#include <sys/select.h>
#include "../common/Poll.hpp"

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

int                     init_serv(char **av)
{
  int                   sock;
  struct protoent       *proto;
  struct sockaddr_in    sin;

  if ((proto = getprotobyname("tcp")) == NULL)
    return (-1);
  if ((sock = socket(AF_INET, SOCK_STREAM, proto->p_proto)) == -1)
    return (-1);
  sin.sin_family = AF_INET;
  sin.sin_port = htons(atoi(av[1]));
  sin.sin_addr.s_addr = INADDR_ANY;
  if (bind(sock, (struct sockaddr *)(&sin), sizeof(sin)) == -1)
    {
      close(sock);
      return (-1);
    }
  if (listen(sock, 10) == -1)
    {
      close(sock);
      return (-1);
    }
  return (sock);
}

int		main(int ac, char **av)
{
  Poll		poll;
  struct sockaddr_in	sin;
  size_t		size_sin;
  int		sock;
  int		cs;
  char		buf[1024];
  int		ret;

  if ((sock = init_serv(av)) == -1)
    return (-1);
  cs = -1;
  size_sin = sizeof(sin);
  poll.watchEvent(sock, POLLIN);
  while ((ret = poll.pollFn(-1)) >= 0)
    {
      try {
      if (poll.isEventOccurred(sock, POLLIN))
	{
	  
	  if ((cs = accept(sock, (struct sockaddr *)(&sin), (socklen_t *)(&size_sin))) == -1)
	    {
	      perror("Unable to accept connection");
	    }
	   poll.watchEvent(cs, POLLIN);
	}
      if (cs != -1 && poll.isDisconnected(cs))
	{
	  printf("Connection reset by peer\n");
	  return (0);
	}
      if (cs != -1 && poll.isEventOccurred(cs, POLLIN))
	{
	  bzero(buf, 1024);
	  if (read(cs, buf, 1024) == 0)
	    {
	      printf("Client disconnected\n");
	      return (0);
	    }
	  printf("[%s]", buf);
	}
      }
      catch (PollException e) {
	printf("%s\n", e.what());
      }
    }
}

/* int		main(int ac, char **av) */
/* { */
/*   int		cs; */
/*   int		ret; */
/*   struct pollfd	fds; */
/*   char		buf[1024]; */
/*   Poll		poll; */

/*   cs = init(av); */
/*   if (cs == -1) */
/*     printf("SHIT\n"); */
/*   printf("Connected !\n"); */
/*   poll.watchEvent(cs, POLLIN); */
/*   while ((ret = poll.pollFn(-1)) > 0) */
/*     { */
/*       printf("LOOP\n"); */
/*       if (poll.isDisconnected(cs)) */
/*   	{ */
/*   	  printf("Connection reset by peer\n"); */
/*   	  return (0); */
/*   	} */
/*       if (poll.isEventOccurred(cs, POLLIN)) */
/*   	{ */
/*   	  bzero(buf, 1024); */
/*   	  if (read(cs, buf, 1024) == 0) */
/* 	    { */
/* 	      close(cs); */
/* 	      printf("Connection closed\n"); */
/* 	      return (0); */
/* 	    } */
/*   	  printf("[%s]\n", buf); */
/*   	} */
/*     } */
/*   if (ret == -1) */
/*     perror("poll"); */
/*   /\* fds.fd = cs; *\/ */
/*   /\* fds.events = POLLIN | POLLRDHUP | POLLHUP | POLLNVAL; *\/ */
/*   /\* fds.revents = POLLRDHUP | POLLHUP | POLLNVAL; *\/ */
/*   /\* while (poll(&fds, 1, -1) != -1) *\/ */
/*   /\*   { *\/ */
/*   /\*     printf("Poll passed\n"); *\/ */
/*   /\*     if (fds.revents & POLLRDHUP) *\/ */
/*   /\* 	{ *\/ */
/*   /\* 	  printf("Connection closed (revents)\n"); *\/ */
/*   /\* 	  return (0); *\/ */
/*   /\* 	} *\/ */
/*   /\*     if (fds.revents & POLLHUP) *\/ */
/*   /\* 	{ *\/ */
/*   /\* 	  printf("Connection closes (revent POLLHUP)\n"); *\/ */
/*   /\* 	} *\/ */
/*   /\*     if (fds.events & POLLHUP) *\/ */
/*   /\* 	{ *\/ */
/*   /\* 	  printf("Connection closes (event POLLHUP)\n"); *\/ */
/*   /\* 	} *\/ */
/*   /\*     if (fds.events & POLLNVAL) *\/ */
/*   /\* 	{ *\/ */
/*   /\* 	  printf("Connection closes (event POLLNVAL)\n"); *\/ */
/*   /\* 	} *\/ */
      
/*   /\*     if (fds.revents & POLLNVAL) *\/ */
/*   /\* 	{ *\/ */
/*   /\* 	  printf("Connection closes (revent POLLNVAL)\n"); *\/ */
/*   /\* 	} *\/ */
/*   /\*     if (fds.events & POLLIN) *\/ */
/*   /\* 	{ *\/ */
/*   /\* 	  printf("Possible to read\n"); *\/ */
/*   /\* 	  if ((ret = read(cs, buf, 1024)) == 0) *\/ */
/*   /\* 	    { *\/ */
/*   /\* 	      printf("Read == 0\n"); *\/ */
/*   /\* 	      return (0); *\/ */
/*   /\* 	    } *\/ */
/*   /\* 	  else if (ret == -1) *\/ */
/*   /\* 	    { *\/ */
/*   /\* 	      perror("read fail"); *\/ */
/*   /\* 	      return (0); *\/ */
/*   /\* 	    } *\/ */
/*   /\* 	} *\/ */
/*   /\*     else if (ret == -1) *\/ */
/*   /\* 	{ *\/ */
/*   /\* 	  perror("Write fail"); *\/ */
/*   /\* 	  return (0); *\/ */
/*   /\* 	} *\/ */
/*   /\*   } *\/ */
/*   /\* /\\* perror("Select failed"); *\\/ *\/ */
/*   return (0); */
/* } */
