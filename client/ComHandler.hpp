//
// ComHandler.hpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Tue May 20 10:51:05 2014 aurelien prieur
// Last update Tue May 20 10:57:28 2014 aurelien prieur
//

#ifndef COMHANDLER_HPP_
# define COMHANDLER_HPP_

class	ComHandler
{
  SocketCtl	socket;

public:
  ComHandler();
  ~ComHandler();
  bool	initialize();

  //Return values:
  //0: connection closed by host
  //-1: critical error
  //1: connection closed by client
  int	run();
};

#endif // !COMANDLER_HPP_
