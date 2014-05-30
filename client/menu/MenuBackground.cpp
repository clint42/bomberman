//
// MenuBackground.cpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client/menu
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Mon May 26 16:09:25 2014 aurelien prieur
// Last update Mon May 26 16:27:44 2014 aurelien prieur
//

#include <iostream>
#include "MenuBackground.hpp"

MenuBackground::MenuBackground()
{
  this->initialize("test");
}

MenuBackground::~MenuBackground()
{
}

bool	MenuBackground::initialize(std::string const &textureName)
{
  if (_texture.load("./ressources/mainMenuBg.tga") == false)
    {
      std::cerr << "Couldn't load background texture." << std::endl;
      return (false);
    }
  _geometry.setColor(glm::vec4(1, 1, 1, 1));
  _geometry.pushVertex(glm::vec3(0, 0, -1));
  _geometry.pushVertex(glm::vec3(800, 0, -1));
  _geometry.pushVertex(glm::vec3(800, 600, -1));
  _geometry.pushVertex(glm::vec3(0, 600, -1));
  _geometry.pushUv(glm::vec2(0, 1));
  _geometry.pushUv(glm::vec2(1, 1));
  _geometry.pushUv(glm::vec2(1, 0));
  _geometry.pushUv(glm::vec2(0, 0));
  _geometry.build();
  return (true);
}

bool	MenuBackground::update(gdl::Clock const &clock, gdl::Input &input)
{
  return (true);
}

void	MenuBackground::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  (void)(clock);
  _texture.bind();
  _geometry.draw(shader, glm::mat4(1), GL_QUADS);
}

void	MenuBackground::hover(bool isHover)
{
}


