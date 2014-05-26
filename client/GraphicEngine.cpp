//
// GraphicEngine.cpp for bomberman_ex in /home/prieur_b/tek2/cpp/bomberman
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Mon May 12 09:39:53 2014 aurelien prieur
// Last update Fri May 23 16:17:16 2014 aurelien prieur
//

#include <iostream>
#include "GraphicEngine.hpp"
#include "Model.hpp"

GraphicEngine::GraphicEngine(GameEntities &objects): objects(objects)
{
}

GraphicEngine::~GraphicEngine()
{
}

bool	GraphicEngine::initialize()
{
  glm::mat4	projection;
  glm::mat4	transformation;
  AObject	*model;

  this->sdlContext.start(800, 600, "Test LibGDL");
  glEnable(GL_DEPTH_TEST);
  if (!shader.load("./shaders/basic.fp", GL_FRAGMENT_SHADER)
      || !shader.load("./shaders/basic.vp", GL_VERTEX_SHADER)
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
  return (true);
}

bool	GraphicEngine::update()
{
  this->sdlContext.updateClock(this->clock);
  this->sdlContext.updateInputs(this->input);
  if (this->input.getKey(SDLK_ESCAPE) || this->input.getInput(SDL_QUIT, false))
    return (false);
  for (std::map<std::pair<size_t, size_t>, AObject *>::iterator it = this->objects.getEntities().begin();
       it != this->objects.getEntities().end(); ++it)
    it->second->update(this->clock, this->input);
  return (true);
}

void	GraphicEngine::draw()
{
  std::cout << "DRAW" << std::endl;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //  std::cout << "Before shader bind" << std::endl;
  shader.bind();
  //std::cout << "After shader bind" << std::endl;
  for (std::map<std::pair<size_t, size_t>, AObject *>::iterator it = this->objects.getEntities().begin();
       it != this->objects.getEntities().end(); ++it)
    it->second->draw(this->shader, this->clock);
  this->sdlContext.flush();
}

