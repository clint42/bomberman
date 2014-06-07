//
// GraphicEngine.cpp for bomberman_ex in /home/prieur_b/tek2/cpp/bomberman
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Mon May 12 09:39:53 2014 aurelien prieur
// Last update Sat Jun  7 19:26:58 2014 aurelien prieur
//

#include <unistd.h>
#include <iostream>
#include "GraphicEngine.hpp"
#include "Model.hpp"

GraphicEngine::GraphicEngine(EventsHandler &eventsHandler,
			     GameEntities &gameEntities,
			     SafeQueue<std::pair<std::pair<size_t, size_t>, int> > &createInstructs):
  isDouble(true),
  objects(gameEntities),
  eventsHandler(eventsHandler),
  floor(std::pair<size_t, size_t>(40, 40)),
  createInstructs(createInstructs)
{
}

GraphicEngine::~GraphicEngine()
{
}

bool	GraphicEngine::mkBackground(void)
{
  if (bgTex.load("./assets/background.tga") == false)
    {
      std::cerr << "Load background error" << std::endl;
      return (false);
    }
  bgTex.bind();
  background.setColor(glm::vec4(1, 1, 1, 1));
  background.pushVertex(glm::vec3(0.f, 0.f, -1.f));
  background.pushVertex(glm::vec3((float)(W_WIDTH), 0, -1.f));
  background.pushVertex(glm::vec3((float)(W_WIDTH), (float)(W_HEIGHT), -1.f));
  background.pushVertex(glm::vec3(0, (float)(W_HEIGHT), -1));
  background.pushUv(glm::vec2(0, 0));
  background.pushUv(glm::vec2(1, 0));
  background.pushUv(glm::vec2(1, 1));
  background.pushUv(glm::vec2(0, 1));
  background.build();
  return (true);
}

bool	GraphicEngine::initialize()
{
  glm::mat4	projection;
  glm::mat4	transformation;

  std::cout << "Initialize Graphic engine" << std::endl;
  this->sdlContext.start(W_WIDTH, W_HEIGHT, "Test LibGDL", SDL_INIT_VIDEO, SDL_WINDOW_OPENGL // | SDL_WINDOW_FULLSCREEN
			 );
  glEnable(GL_DEPTH_TEST);
  if (!this->shader.load("./shaders/basic.fp", GL_FRAGMENT_SHADER)
      || !this->shader.load("./shaders/basic.vp", GL_VERTEX_SHADER)
      || !this->shader.build())
    {
      std::cerr << "Shader loading error" << std::endl;
      return (false);
    }
  if (this->mkBackground() == false)
    return (false);
  this->floor.initialize();
  score1 = new GraphicalText("100", std::pair<size_t, size_t>(320, 0), glm::vec4(1, 1, 1, 1), 50, "airstrikeBold");
  score2 = new GraphicalText("100", std::pair<size_t, size_t>(W_WIDTH / 2 + 400, 0), glm::vec4(1, 1, 1, 1), 50, "airstrikeBold");
  this->chrono.initialize();
  this->chrono.setTime(360.f);
  return (true);
}

bool	GraphicEngine::update()
{
  std::pair<std::pair<size_t, size_t>, int>	instruct;

  this->eventsHandler.interpret();
  this->sdlContext.updateClock(this->clock);
  this->sdlContext.updateInputs(this->input);
  this->eventsHandler.update(this->input);
  if (this->input.getKey(SDLK_ESCAPE) || this->input.getInput(SDL_QUIT, false))
    {
      eventsHandler.finish();
      return (false);
    }
  //EXEC CREATE INSTRUCT
  while (createInstructs.getSize() > 0)
    {
      createInstructs.tryPop(&instruct);
      objects.addEntity(instruct);
    }
  this->chrono.update(this->clock, this->eventsHandler);
  this->objects.lock();
  for (std::map<std::pair<size_t, size_t>, AObject *>::iterator it = this->objects.getEntities().begin();
       it != this->objects.getEntities().end(); ++it)
    it->second->update(this->clock, this->eventsHandler);
  this->objects.unlock();
  return (true);
}

void		GraphicEngine::drawPlayer(int nPlayer)
{
  glm::mat4	transformation;
  glm::mat4	projection;

  projection = glm::perspective(60.0f, (((float)(W_WIDTH) / 2.f) - 5.f) / ((float)(W_HEIGHT) - 50.f), 0.1f, 100.f);
  this->shader.setUniform("projection", projection);
  glViewport((((float)(W_WIDTH) / 2.f) + 5.f) * nPlayer, 0, ((float)(W_WIDTH) / 2.f) - 5.f, (float)(W_HEIGHT) - 50.f);
  AObject const *player = this->objects.getPlayer(true, 0);
  if (player != NULL)
    {
         transformation = glm::lookAt(glm::vec3(0, 14, 10) + player->getPos(), player->getPos(), glm::vec3(0, 1, 0));
      this->shader.setUniform("view", transformation);
    }
  for (std::map<std::pair<size_t, size_t>, AObject *>::iterator it = this->objects.getEntities().begin();
       it != this->objects.getEntities().end(); ++it)
    it->second->draw(this->shader, this->clock);
  this->floor.draw(this->shader, this->clock);
}

void		GraphicEngine::drawScore(int nPlayer)
{
  std::ostringstream	oss;
  int			playerScore;
  int			i;

  i = 1;
  glViewport(0, 0, 1920, 1080);
  playerScore = objects.getPlayerScore(true, nPlayer);
  while ((playerScore /= 10) > 0)
    ++i;
  for (int j = 0; j < (6 - i) / 2; ++j)
    oss <<  " ";
  oss << objects.getPlayerScore(true, nPlayer);
  if (nPlayer == 0)
    {
      score1->updateText(oss.str());
      score1->draw(shader);
    }
  else
    {
      score2->updateText(oss.str());
      score2->draw(shader);
    }
}

void		GraphicEngine::drawBackground(void)
{
  glm::mat4	projection;

  glDepthMask(false);
  glViewport(0, 0, W_WIDTH, W_HEIGHT);
  bgTex.bind();
  background.draw(shader, glm::mat4(1), GL_QUADS);
  glDepthMask(true);
}

void		GraphicEngine::draw2D(void)
{
  glm::mat4	projection;

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  projection = glm::ortho(0.f, (float)(W_WIDTH), (float)(W_HEIGHT), 0.f, 1.f, -3.f);
  shader.setUniform("projection", projection);
  shader.setUniform("view", glm::mat4(1));
  drawBackground();
  drawScore(0);
  drawScore(1);
  chrono.draw(this->shader, this->clock);
  glDisable(GL_BLEND);
}

void		GraphicEngine::draw()
{
  glm::mat4	transformation;
  glm::mat4	projection;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  this->objects.lock();
  shader.bind();
  draw2D();
  drawPlayer(0);
  if (isDouble)
    drawPlayer(1);
  this->objects.unlock();
  this->sdlContext.flush();
}

void	GraphicEngine::stop()
{
  sdlContext.stop();
}
