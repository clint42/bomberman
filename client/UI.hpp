//
// UI.hpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Fri May 16 17:33:28 2014 aurelien prieur
// Last update Wed Jun  4 17:45:25 2014 aurelien prieur
//

#ifndef UI_HPP
# define UI_HPP

# include <utility>
# include "GraphicEngine.hpp"
# include "EventsHandler.hpp"
# include "SafeQueue.hpp"

class	UI
{
  GraphicEngine	_graphicEngine;
public:
  UI(EventsHandler &eventsHandler, GameEntities &gamEntities,
     SafeQueue<std::pair<std::pair<size_t, size_t>, int> > &createInstruct);
  ~UI();
  bool	run();
};

#endif // !UI_HPP
