//
// GraphicEngine.hpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Fri May 16 16:00:09 2014 aurelien prieur
// Last update Sun Jun 15 06:55:50 2014 aurelien prieur
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
# include "Player.hpp"
# include "Floor.hpp"
# include "SafeQueue.hpp"
# include "GraphicalText.hpp"
# include "Chrono.hpp"
# include "Score.hpp"
# include "FpsDisplay.hpp"

# define W_WIDTH 1920
# define W_HEIGHT 1080
# define SHOW_FPS 1
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
  SafeQueue<std::pair<std::pair<size_t, size_t>, int> > &createInstructs;
  Chrono		chrono;
  gdl::Geometry		background;
  gdl::Texture		bgTex;
  FpsDisplay		*fps;
  std::vector<Score *>	scores;
  void			getPlayerProjection(glm::mat4 &projection) const;
  void			viewPortPlayer(int nPlayer = 0) const;
  void			drawPlayer(int nPlayer);
  void			drawScore(int nPlayer);
  bool			mkBackground(void);
  void			drawBackground(void);
  void			draw2D(void);

public:
  GraphicEngine(EventsHandler &eventsHandler, GameEntities &objects,
		SafeQueue<std::pair<std::pair<size_t, size_t>, int> > &createInstructs);
  ~GraphicEngine();
  virtual bool	initialize();
  virtual bool	update();
  virtual void	draw();
  virtual void	stop();
};

#endif // !GRAPHICENGINE_HPP_
