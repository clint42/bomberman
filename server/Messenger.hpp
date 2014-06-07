//
// Messenger.hpp for  in /home/buret_j/rendu/bomberman/server
// 
// Made by buret_j
// Login   <buret_j@epitech.net>
// 
// Started on  Thu Jun  5 17:15:53 2014 buret_j
// Last update Fri Jun  6 14:42:37 2014 buret_j
//

#ifndef MESSENGER_HPP_
# define MESSENGER_HPP_

# include <string>
# include <vector>

# include "Socket.hpp"

namespace Server {

  class	Messenger {

    std::vector<std::string> _queues;

  public:

    Messenger() {  }
    ~Messenger() {  }

    void	addMessage(Socket const *s, std::string const &toAdd)  {
      if (_queues.capacity() < (size_t)s->getFd())
	_queues.resize(s->getFd() + 1);
      _queues[s->getFd()] += toAdd;
    }
    void	retrieveMessage(Socket const *s, std::string &toFill) {
      toFill = _queues[s->getFd()];
      _queues[s->getFd()].clear();
    }
    void	clearAll() {
      for (std::vector<std::string>::iterator it = _queues.begin(); it != _queues.end(); ++it) 
	(*it).clear();
    }
  };

}

#endif /* !MESSENGER_HPP_ */
