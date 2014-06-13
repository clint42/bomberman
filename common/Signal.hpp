//
// Signal.hpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/common
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Wed Jun 11 09:33:50 2014 aurelien prieur
// Last update Fri Jun 13 10:23:34 2014 aurelien prieur
//

#ifndef SIGNAL_HPP_
# define SIGNAL_HPP_

# include <signal.h>
# include <iostream>
# include <map>
# include "ConnexionHandler.hpp"

class		Signal
{
  static ConnexionHandler	*_connexion;
  static void		        sighandler(int signum);
  static std::map<int, bool>	signalsStatus;	
public:
  Signal(ConnexionHandler *connexion);
  ~Signal();
  bool	catchSignal(int signum, bool ignore = false);
  bool	isCatched(int signum) const;
};

#endif // !SIGNAL_HPP_
