//
// Signal.cpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/common
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Wed Jun 11 09:38:46 2014 aurelien prieur
// Last update Fri Jun 13 14:00:52 2014 aurelien prieur
//

#include <sys/types.h>
#include <sys/wait.h>
#include "Signal.hpp"

std::map<int, bool>	Signal::signalsStatus;
ConnexionHandler	*Signal::_connexion = NULL;

Signal::Signal(ConnexionHandler *connexion)
{
  _connexion = connexion;
}

Signal::~Signal()
{
}

void	Signal::sighandler(int signum)
{
  Signal::signalsStatus[signum] = true;
  if (signum == SIGINT)
    {
      if (_connexion != NULL)
	_connexion->reset();
      _exit(-1);
    }
}

bool	Signal::catchSignal(int signum, bool ignore)
{
  if (!ignore)
    {
      if (signal(signum, sighandler) == SIG_ERR)
	return (false);
    }
  else
    {
      if (signal(signum, SIG_IGN) == SIG_ERR)
	return (false);
    }
  return (true);
}

bool	Signal::isCatched(int signum) const
{
  return (Signal::signalsStatus[signum]);
}
