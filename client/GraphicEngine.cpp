//
// GraphicEngine.cpp for bomberman_ex in /home/prieur_b/tek2/cpp/bomberman
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Mon May 12 09:39:53 2014 aurelien prieur
// Last update Sun May 18 16:24:25 2014 aurelien prieur
//

#include <iostream>
#include "Gui.hpp"
#include "Cube.hpp"
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
  AObject	*cube;

  if (this->sdlContext.start(800, 600, "Test LibGDL") == false)
    throw GraphicEngineException("Unable to initialize gui");
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
  return (true);
}

bool	GraphicEngine::update()
{
  Cube	Cube;
 
  this->sdlContext.updateClock(this->clock);
  this->sdlContext.updateInputs(this->input);
  if (this->input.getKey(SDLK_ESCAPE) || this->input.getInput(SDL_QUIT, false))
    return (false);
  //TODO: iterator (map used instead of vector)
  for (size_t i = 0; i < this->objects.size(); ++i)
    this->objects[i]->update(this->clock, this->input);
  return (true);
}

void	GraphicEngine::draw()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  shader.bind();
  //TODO: iterator (map used instead of vector)
  for (size_t i = 0; i < this->objects.size(); ++i)
    this->objects[i]->draw(this->shader, this->clock);
  this->sdlContext.flush();
}

