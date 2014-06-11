//
// Signal.cpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/common
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Wed Jun 11 09:38:46 2014 aurelien prieur
// Last update Wed Jun 11 10:27:11 2014 aurelien prieur
//

#include "Signal.hpp"

std::map<int, bool>	Signal::signalsStatus;

Signal::Signal()
{
}

Signal::~Signal()
{
}

void	Signal::sighandler(int signum)
{
  Signal::signalsStatus[signum] = true;
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
