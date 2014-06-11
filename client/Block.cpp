//
// Block.cpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client/menu
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Thu Jun  5 12:08:48 2014 aurelien prieur
// Last update Wed Jun 11 13:53:59 2014 aurelien prieur
//

#include <iostream>
#include "Block.hpp"

std::map<ObjectType, gdl::Texture *> Block::textures;

bool	Block::loadTextures(void)
{
  textures[BLOCK] = new gdl::Texture;
  textures[BOX] = new gdl::Texture;
  if (!(textures[BLOCK]->load("./client/assets/ublock.tga")) ||
      !(textures[BOX]->load("./client/assets/box.tga")))
    {
      std::cerr << "Failed to load block textures" << std::endl;
      return (false);
    }
  return (true);
}

Block::Block(ObjectType blockType): _blockType(blockType)
{
}

Block::~Block()
{
}

bool	Block::initialize(std::pair<size_t, size_t> const &pos)
{
  textures[_blockType]->bind();
  _geometry.setColor(glm::vec4(1, 1, 1, 1));
  _geometry.pushVertex(glm::vec3(pos.first, 0, pos.second));
  _geometry.pushVertex(glm::vec3(pos.first + 1, 0, pos.second));
  _geometry.pushVertex(glm::vec3(pos.first + 1, 0, pos.second + 1));
  _geometry.pushVertex(glm::vec3(pos.first, 0, pos.second + 1));
  _geometry.pushUv(glm::vec2(0, 1));
  _geometry.pushUv(glm::vec2(0, 0));
  _geometry.pushUv(glm::vec2(1, 0));
  _geometry.pushUv(glm::vec2(1, 1));
  _geometry.pushVertex(glm::vec3(pos.first, 1, pos.second));
  _geometry.pushVertex(glm::vec3(pos.first + 1, 1, pos.second));
  _geometry.pushVertex(glm::vec3(pos.first + 1, 0, pos.second));
  _geometry.pushVertex(glm::vec3(pos.first, 0, pos.second));
  _geometry.pushUv(glm::vec2(0, 0));
  _geometry.pushUv(glm::vec2(1, 0));
  _geometry.pushUv(glm::vec2(1, 1));
  _geometry.pushUv(glm::vec2(0, 1));
  _geometry.pushVertex(glm::vec3(pos.first + 1, 1, pos.second));
  _geometry.pushVertex(glm::vec3(pos.first + 1, 1, pos.second + 1));
  _geometry.pushVertex(glm::vec3(pos.first + 1, 0, pos.second + 1));
  _geometry.pushVertex(glm::vec3(pos.first + 1, 0, pos.second));
  _geometry.pushUv(glm::vec2(0, 0));
  _geometry.pushUv(glm::vec2(1, 0));
  _geometry.pushUv(glm::vec2(1, 1));
  _geometry.pushUv(glm::vec2(0, 1));
  _geometry.pushVertex(glm::vec3(pos.first, 1, pos.second + 1));
  _geometry.pushVertex(glm::vec3(pos.first + 1, 1, pos.second + 1));
  _geometry.pushVertex(glm::vec3(pos.first + 1, 0, pos.second + 1));
  _geometry.pushVertex(glm::vec3(pos.first, 0, pos.second + 1));
  _geometry.pushUv(glm::vec2(0, 0));
  _geometry.pushUv(glm::vec2(1, 0));
  _geometry.pushUv(glm::vec2(1, 1));
  _geometry.pushUv(glm::vec2(0, 1));
  _geometry.pushVertex(glm::vec3(pos.first, 1, pos.second));
  _geometry.pushVertex(glm::vec3(pos.first, 1, pos.second + 1));
  _geometry.pushVertex(glm::vec3(pos.first, 0, pos.second + 1));
  _geometry.pushVertex(glm::vec3(pos.first, 0, pos.second));
  _geometry.pushUv(glm::vec2(0, 0));
  _geometry.pushUv(glm::vec2(1, 0));
  _geometry.pushUv(glm::vec2(1, 1));
  _geometry.pushUv(glm::vec2(0, 1));
  _geometry.pushVertex(glm::vec3(pos.first, 1, pos.second));
  _geometry.pushVertex(glm::vec3(pos.first + 1, 1, pos.second));
  _geometry.pushVertex(glm::vec3(pos.first + 1, 1, pos.second + 1));
  _geometry.pushVertex(glm::vec3(pos.first, 1, pos.second + 1));
  _geometry.pushUv(glm::vec2(0, 0));
  _geometry.pushUv(glm::vec2(1, 0));
  _geometry.pushUv(glm::vec2(1, 1));
  _geometry.pushUv(glm::vec2(0, 1));
  if (_geometry.build() == false)
    return (false);
  return (true);
}

void	Block::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  (void)(clock);
  textures[_blockType]->bind();
  _geometry.draw(shader, getTransformation(), GL_QUADS);
}
