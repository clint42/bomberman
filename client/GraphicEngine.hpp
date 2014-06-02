//
// GraphicEngine.hpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Fri May 16 16:00:09 2014 aurelien prieur
// Last update Sat May 31 16:03:05 2014 aurelien prieur
//

#ifndef GRAPHICENGINE_HPP_
# define GRAPHICENGINE_HPP_

# include <OpenGL.hh>
# include <Game.hh>
# include <Clock.hh>
# include <Input.hh>
# include <SdlContext.hh>
# include <Geometry.hh>
# include <Texture.hh>
# include <BasicShader.hh>
# include <Model.hh>
# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>
# include "GameEntities.hpp"
# include "EventsHandler.hpp"
# include "Model.hpp"
# include "Floor.hpp"
# include "SafeQueue.hpp"

class			GraphicEngine: public gdl::Game
{
  std::vector<int>	watchedEvents;
  GameEntities		&objects;
  EventsHandler		&eventsHandler;
  gdl::SdlContext	sdlContext;
  gdl::Clock		clock;
  gdl::Input		input;
  gdl::BasicShader	shader;
  Floor			floor;
  SafeQueue<std::pair<std::pair<size_t, size_t>, ObjectType> > &createInstructs;

public:
  GraphicEngine(EventsHandler &eventsHandler, GameEntities &objects,
		SafeQueue<std::pair<std::pair<size_t, size_t>, ObjectType> > &createInstructs);
  ~GraphicEngine();
  virtual bool	initialize();
  virtual bool	update();
  virtual void	draw();
};

#endif // !GRAPHICENGINE_HPP_
