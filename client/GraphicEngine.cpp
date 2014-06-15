//
// GraphicEngine.cpp for bomberman_ex in /home/prieur_b/tek2/cpp/bomberman
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Mon May 12 09:39:53 2014 aurelien prieur
// Last update Sun Jun 15 06:57:15 2014 aurelien prieur
//

#include <unistd.h>
#include <iostream>
#include "GraphicEngine.hpp"
#include "Block.hpp"
#include "Bonus.hpp"
#include "Fire.hpp"
#include "Bomb.hpp"
#include "LoadBar.hpp"

GraphicEngine::GraphicEngine(EventsHandler &eventsHandler,
			     GameEntities &gameEntities,
			     SafeQueue<std::pair<std::pair<size_t, size_t>, int> > &createInstructs):
  objects(gameEntities),
  eventsHandler(eventsHandler),
  createInstructs(createInstructs),
  scores(2)
{
}

GraphicEngine::~GraphicEngine()
{
  if (fps != NULL)
    delete fps;
}

bool	GraphicEngine::mkBackground(void)
{
  if (bgTex.load("./client/assets/background.tga") == false)
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
  this->sdlContext.start(W_WIDTH, W_HEIGHT, "Bomberman", SDL_INIT_VIDEO, SDL_WINDOW_OPENGL//| SDL_WINDOW_FULLSCREEN
		 );
  glEnable(GL_DEPTH_TEST);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  sdlContext.flush();
  if (!this->shader.load("./client/shaders/basic.fp", GL_FRAGMENT_SHADER)
      || !this->shader.load("./client/shaders/basic2.vp", GL_VERTEX_SHADER)
      || !this->shader.build())
    {
      std::cerr << "Shader loading error" << std::endl;
      return (false);
    }
  shader.bind();
  shader.setUniform("color", glm::vec4(1, 1, 1, 1));
  LoadBar	loadBar(sdlContext, shader);
  loadBar.initialize(std::pair<float, float>(660, 525), std::pair<float, float>(600, 30));
  projection = glm::ortho(0.f, (float)(W_WIDTH), (float)(W_HEIGHT), 0.f, 1.f, -3.f);
  shader.setUniform("projection", projection);
  shader.setUniform("view", glm::mat4(1));
  if ((loadBar.update((5.f / 30.f) * 100) && !Fire::load()) ||
      (loadBar.update((15.f / 30.f) * 100) && !Bomb::load()) ||
      (loadBar.update((20.f / 30.f) * 100) && !Player::load()))
    {
      std::cerr << "Error while loading models." << std::endl;
      return (false);
    }
  if ((loadBar.update((25.f / 30.f) * 100) && !Block::loadTextures()) ||
      (loadBar.update((30.f / 30.f) * 100) && !Bonus::loadTextures()))
    {
      std::cerr << "Error while loading textures." << std::endl;
      return (false);
    }
  if (this->mkBackground() == false)
    return (false);
  this->floor.setSize(this->objects.getMapSize());
  this->floor.initialize();
  this->chrono.initialize();
  this->scores[0] = new Score(false);
  this->scores[0]->initialize();
  if (this->objects.isDouble())
    {
      this->scores[1] = new Score(true);
      this->scores[1]->initialize();
    }
  if (SHOW_FPS)
    fps = new FpsDisplay;
  else
    fps = NULL;
  this->sdlContext.updateClock(this->clock);
  return (true);
}

bool	GraphicEngine::update()
{
  std::pair<std::pair<size_t, size_t>, int>	instruct;

  if (fps != NULL)
    fps->updateTimer(clock.getElapsed());
  this->eventsHandler.interpret();
  this->sdlContext.updateClock(this->clock);
  this->sdlContext.updateInputs(this->input);
  this->eventsHandler.update(this->input);
  if (this->input.getKey(SDLK_ESCAPE) || this->input.getInput(SDL_QUIT, false))
    {
      eventsHandler.finish();
      return (false);
    }
  while (createInstructs.size() > 0)
    {
      createInstructs.tryPop(&instruct);
      objects.addEntity(instruct);
    }
  if (!this->objects.lock())
    {
      std::cerr << "Unable to lock mutex" << std::endl;
      return (false);
    }
  for (std::map<std::pair<size_t, size_t>, AObject *>::iterator it = this->objects.getEntities().begin();
       it != this->objects.getEntities().end(); ++it) 
    {
      if (!it->second->update(this->clock, this->eventsHandler))
	{
	  delete it->second;
	  this->objects.getEntities().erase(it);
	}
    }  
  this->scores[0]->update(this->objects.getPlayerScore(true, 0));
  if (this->objects.isDouble(true))
    this->scores[1]->update(this->objects.getPlayerScore(true, 1));
  if (this->chrono.getTime() == -1.f)
    this->chrono.setTime(this->objects.getTimeLeft(true));
  if (this->objects.isStarted(true))
    this->chrono.update(this->clock, this->eventsHandler);
  if (!this->objects.unlock())
    {
      std::cerr << "Unable to unlock mutex" << std::endl;
    }
  return (true);
}

void		GraphicEngine::drawPlayer(int nPlayer)
{
  glm::mat4	transformation;
  glm::mat4	projection;
  std::pair<size_t, size_t> const	*playerPos = this->objects.getPlayerPos(nPlayer, true);
  std::pair<size_t, size_t>	pos;
  size_t			pY;
  size_t			pX;

  pY = playerPos->second;
  pX = playerPos->first;
  viewPortPlayer(nPlayer);
  getPlayerProjection(projection);
  this->shader.setUniform("projection", projection);
  AObject const *player = this->objects.getPlayer(true, nPlayer);
  if (player != NULL)
    transformation = glm::lookAt(glm::vec3(0, 8, 4) + player->getPos(), player->getPos(), glm::vec3(0, 1, 0));
  else
    {
      std::pair<double, double> const &sizeMap = floor.getSize();
      transformation = glm::lookAt(glm::vec3(0, 8, 4) + glm::vec3(sizeMap.first / 2.f, 0, sizeMap.second / 2.f),
				   glm::vec3(sizeMap.first / 2.f, 0, sizeMap.second / 2.f), glm::vec3(0, 1, 0));
    }
  this->shader.setUniform("view", transformation);
  this->floor.draw(this->shader, this->clock);
  pos.first = (pX >= 12) ? pX - 12 : 0;
  std::map<std::pair<size_t, size_t>, AObject *> entities = this->objects.getEntities();
  while (pos.first < pX + 11)
    {
      pos.second = (pY >= 10) ? pY - 10 : 0;
      while (pos.second < pY + 6)
	{
	  if (entities.find(pos) != entities.end())
	    entities[pos]->draw(shader, clock);
	  ++pos.second;
	}
      ++pos.first;
    }
}

void		GraphicEngine::drawScore(int nPlayer)
{
  int			i;

  i = 1;
  glViewport(0, 0, 1920, 1080);
  if (fps != NULL)
    fps->draw(this->shader);
  scores[nPlayer]->draw(this->shader);
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
  if (this->objects.isDouble(true))
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
  if (this->objects.isDouble(true))
    drawPlayer(1);
  this->objects.unlock();
  this->sdlContext.flush();
}

void	GraphicEngine::stop()
{
  sdlContext.stop();
}

void	GraphicEngine::viewPortPlayer(int nPlayer) const
{
  if (!this->objects.isDouble(true))
    {
      glViewport(0, 0, (float)(W_WIDTH), (float)(W_HEIGHT) - 80.f);
    }
  else
    glViewport((((float)(W_WIDTH) / 2.f) + 5.f) * nPlayer, 0, ((float)(W_WIDTH) / 2.f) - 5.f, (float)(W_HEIGHT) - 80.f);
}

void	GraphicEngine::getPlayerProjection(glm::mat4 &projection) const
{
  if (!this->objects.isDouble(true))
      projection = glm::perspective(60.0f, (float)(W_WIDTH) / (float)(W_HEIGHT), 0.1f, 100.f);
  else
    projection = glm::perspective(60.0f, (((float)(W_WIDTH) / 2.f) - 5.f) / ((float)(W_HEIGHT) - 50.f), 0.1f, 100.f);
}
