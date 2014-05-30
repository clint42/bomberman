//
// GraphicEngine.cpp for bomberman_ex in /home/prieur_b/tek2/cpp/bomberman
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Mon May 12 09:39:53 2014 aurelien prieur
// Last update Fri May 30 15:38:02 2014 aurelien prieur
//

#include <iostream>
#include "GraphicEngine.hpp"
#include "Model.hpp"

GraphicEngine::GraphicEngine(EventsHandler &eventsHandler,
			     GameEntities &gameEntities,
			     SafeQueue<std::pair<std::pair<size_t, size_t>, ObjectType> > &createInstructs):
  createInstructs(createInstructs),
  eventsHandler(eventsHandler),
  objects(gameEntities)
{
}

GraphicEngine::~GraphicEngine()
{
}

bool	GraphicEngine::initialize()
{
  glm::mat4	projection;
  glm::mat4	transformation;

  this->sdlContext.start(800, 600, "Test LibGDL");
  glEnable(GL_DEPTH_TEST);
  if (!shader.load("/home/prieur_b/LibBomberman_linux_x64/shaders/basic.fp", GL_FRAGMENT_SHADER)
      || !shader.load("/home/prieur_b/LibBomberman_linux_x64/shaders/basic.vp", GL_VERTEX_SHADER)
      || !shader.build())
    {
      std::cerr << "Shader loading error" << std::endl;
      return (false);
    }
  projection = glm::perspective(60.0f, 800.0f / 600.0f, 0.1f, 100.f);
  transformation = glm::lookAt(glm::vec3(0, 15, 20), glm::vec3(0, 5, 0), glm::vec3(0, 6, 0));
  shader.bind();
  shader.setUniform("view", transformation);
  shader.setUniform("projection", projection);
  // model = new Model();
  // if (model->initialize() == false)
  //   return (false); 
  std::cout << "End of init" << std::endl;
  return (true);
}

bool	GraphicEngine::update()
{
  std::pair<std::pair<size_t, size_t>, ObjectType>	instruct;

  this->sdlContext.updateClock(this->clock);
  this->sdlContext.updateInputs(this->input);
  if (this->input.getKey(SDLK_ESCAPE) || this->input.getInput(SDL_QUIT, false))
    return (false);

  //EXEC CREATE INSTRUCT
  while (createInstructs.getSize() > 0)
    {
      createInstructs.tryPop(&instruct);
      objects.addEntity(instruct);
    }
  this->objects.lock();
  for (std::map<std::pair<size_t, size_t>, AObject *>::iterator it = this->objects.getEntities().begin();
       it != this->objects.getEntities().end(); ++it)
    it->second->update(this->clock, this->input);
  this->objects.unlock();
  return (true);
}

void	GraphicEngine::draw()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  shader.bind();
  //model->draw(this->shader, this->clock);
  this->objects.lock();
  for (std::map<std::pair<size_t, size_t>, AObject *>::iterator it = this->objects.getEntities().begin();
       it != this->objects.getEntities().end(); ++it)
    it->second->draw(this->shader, this->clock);
  this->objects.unlock();
  this->sdlContext.flush();
}

