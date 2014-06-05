//
// ClientCore.hpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Thu May 29 15:42:09 2014 aurelien prieur
// Last update Wed Jun  4 17:57:30 2014 aurelien prieur
//

#ifndef CLIENTCORE_HPP_
# define CLIENTCORE_HPP_

# include <utility>
# include "Socket.hpp"
# include "GameEntities.hpp"
# include "EventsHandler.hpp"
# include "SafeQueue.hpp"

class		ClientCore
{
  int			_playerId;
  GameEntities		&_gameEntities;
  EventsHandler		&_eventsHandler;
  Socket		*_socket;
  ConnexionHandler	&_connexion;
  SafeQueue<std::pair<std::pair<size_t, size_t>, int> > &_createInstructs;
  bool			read(void);
  bool			write(void);

public:
  ClientCore(GameEntities &gameEntities, EventsHandler &eventsHandler,
	     SafeQueue<std::pair<std::pair<size_t, size_t>, int> > &createInstructs,
	     ConnexionHandler &connexionHandler);
  ~ClientCore();
  bool		initialize();
  bool		run();
  void		io(Socket *socket, bool b[3]);
};

#endif // !CLIENTCORE_HPP_
