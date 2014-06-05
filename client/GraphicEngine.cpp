//
// GraphicEngine.cpp for bomberman_ex in /home/prieur_b/tek2/cpp/bomberman
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Mon May 12 09:39:53 2014 aurelien prieur
// Last update Wed Jun  4 19:47:53 2014 aurelien prieur
//

#include <unistd.h>
#include <iostream>
#include "GraphicEngine.hpp"
#include "Model.hpp"

GraphicEngine::GraphicEngine(EventsHandler &eventsHandler,
			     GameEntities &gameEntities,
			     SafeQueue<std::pair<std::pair<size_t, size_t>, int> > &createInstructs):
  createInstructs(createInstructs),
  eventsHandler(eventsHandler),
  objects(gameEntities),
  floor(std::pair<size_t, size_t>(20, 20))
{
}

GraphicEngine::~GraphicEngine()
{
}

bool	GraphicEngine::initialize()
{
  glm::mat4	projection;
  glm::mat4	transformation;

  std::cout << "Initialize Graphic engine" << std::endl;
  this->sdlContext.start(800, 600, "Test LibGDL", SDL_INIT_VIDEO, SDL_WINDOW_OPENGL // | SDL_WINDOW_FULLSCREEN
			 );
  glEnable(GL_DEPTH_TEST);
  if (!this->shader.load("/home/prieur_b/LibBomberman_linux_x64/shaders/basic.fp", GL_FRAGMENT_SHADER)
      || !this->shader.load("/home/prieur_b/LibBomberman_linux_x64/shaders/basic.vp", GL_VERTEX_SHADER)
      || !this->shader.build())
    {
      std::cerr << "Shader loading error" << std::endl;
      return (false);
    }
  projection = glm::perspective(60.0f, 1920.0f / 1080.0f, 0.1f, 100.f);
  transformation = glm::lookAt(glm::vec3(0, 7, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
  this->shader.bind();
  this->shader.setUniform("view", transformation);
  this->shader.setUniform("projection", projection);
  this->floor.initialize();
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
  this->objects.lock();
  for (std::map<std::pair<size_t, size_t>, AObject *>::iterator it = this->objects.getEntities().begin();
       it != this->objects.getEntities().end(); ++it)
    it->second->update(this->clock, this->eventsHandler);
  this->objects.unlock();
  return (true);
}

void		GraphicEngine::draw()
{
  glm::mat4	transformation;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  shader.bind();
  this->floor.draw(this->shader, this->clock);
  this->objects.lock();
  AObject const *player = this->objects.getPlayer();
  if (player != NULL)
    {
      transformation = glm::lookAt(glm::vec3(0, 7, 5) + player->getPos(), player->getPos(), glm::vec3(0, 1, 0));
      this->shader.setUniform("view", transformation);
    }
  for (std::map<std::pair<size_t, size_t>, AObject *>::iterator it = this->objects.getEntities().begin();
       it != this->objects.getEntities().end(); ++it)
    it->second->draw(this->shader, this->clock);
  this->objects.unlock();
  this->sdlContext.flush();
}

void	GraphicEngine::stop()
{
  sdlContext.stop();
}
