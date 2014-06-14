//
// Bonus.cpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Sat Jun 14 11:54:40 2014 aurelien prieur
// Last update Sat Jun 14 14:19:38 2014 aurelien prieur
//

#include "Bonus.hpp"

std::map<ObjectType, gdl::Texture *>	Bonus::_textures;

bool	Bonus::loadTextures(void)
{
  _textures[BONUSRANGE] = new gdl::Texture;
  _textures[BONUSSPEED] = new gdl::Texture;
  _textures[BONUSBOMB] = new gdl::Texture;
  if (!(_textures[BONUSRANGE]->load("./client/assets/bonusRange.tga")) ||
      !(_textures[BONUSSPEED]->load("./client/assets/bonusSpeed.tga")) ||
      !(_textures[BONUSBOMB]->load("./client/assets/bonusBomb.tga")))
    {
      std::cerr << "Failed to load block textures" << std::endl;
      return (false);
    }
  return (true);
}

Bonus::Bonus(ObjectType bonusType): _bonusType(bonusType)
{
}

Bonus::~Bonus()
{
}

bool	Bonus::initialize(std::pair<size_t, size_t> const &pos)
{
  float	posX;
  float	posY;
  float	posZ;
  float	size;

  posX = pos.first + 0.25;
  posY = pos.second + 0.25;
  posZ = 0.25;
  size = 0.5;
  _textures[_bonusType]->bind();
  _geometry.setColor(glm::vec4(1, 1, 1, 1));
  _geometry.pushVertex(glm::vec3(posX, posZ, posY));
  _geometry.pushVertex(glm::vec3(posX + size, posZ, posY));
  _geometry.pushVertex(glm::vec3(posX + size, posZ, posY + size));
  _geometry.pushVertex(glm::vec3(posX, posZ, posY + size));
  _geometry.pushUv(glm::vec2(1, 1));
  _geometry.pushUv(glm::vec2(0, 1));
  _geometry.pushUv(glm::vec2(0, 0));
  _geometry.pushUv(glm::vec2(1, 0));
  _geometry.pushVertex(glm::vec3(posX, posZ + size, posY));
  _geometry.pushVertex(glm::vec3(posX + size, posZ + size, posY));
  _geometry.pushVertex(glm::vec3(posX + size, posZ, posY));
  _geometry.pushVertex(glm::vec3(posX, posZ, posY));
  _geometry.pushUv(glm::vec2(1, 1));
  _geometry.pushUv(glm::vec2(0, 1));
  _geometry.pushUv(glm::vec2(0, 0));
  _geometry.pushUv(glm::vec2(1, 0));
  _geometry.pushVertex(glm::vec3(posX + size, posZ + size, posY));
  _geometry.pushVertex(glm::vec3(posX + size, posZ + size, posY + size));
  _geometry.pushVertex(glm::vec3(posX + size, posZ, posY + size));
  _geometry.pushVertex(glm::vec3(posX + size, posZ, posY));
  _geometry.pushUv(glm::vec2(1, 1));
  _geometry.pushUv(glm::vec2(0, 1));
  _geometry.pushUv(glm::vec2(0, 0));
  _geometry.pushUv(glm::vec2(1, 0));
  _geometry.pushVertex(glm::vec3(posX, posZ + size, posY + size));
  _geometry.pushVertex(glm::vec3(posX + size, posZ + size, posY + size));
  _geometry.pushVertex(glm::vec3(posX + size, posZ, posY + size));
  _geometry.pushVertex(glm::vec3(posX, posZ, posY + size));
  _geometry.pushUv(glm::vec2(1, 1));
  _geometry.pushUv(glm::vec2(0, 1));
  _geometry.pushUv(glm::vec2(0, 0));
  _geometry.pushUv(glm::vec2(1, 0));
  _geometry.pushVertex(glm::vec3(posX, posZ + size, posY));
  _geometry.pushVertex(glm::vec3(posX, posZ + size, posY + size));
  _geometry.pushVertex(glm::vec3(posX, posZ, posY + size));
  _geometry.pushVertex(glm::vec3(posX, posZ, posY));
  _geometry.pushUv(glm::vec2(1, 1));
  _geometry.pushUv(glm::vec2(0, 1));
  _geometry.pushUv(glm::vec2(0, 0));
  _geometry.pushUv(glm::vec2(1, 0));
  _geometry.pushVertex(glm::vec3(posX, posZ + size, posY));
  _geometry.pushVertex(glm::vec3(posX + size, posZ + size, posY));
  _geometry.pushVertex(glm::vec3(posX + size, posZ + size, posY + size));
  _geometry.pushVertex(glm::vec3(posX, posZ + size, posY + size));
  _geometry.pushUv(glm::vec2(1, 1));
  _geometry.pushUv(glm::vec2(0, 1));
  _geometry.pushUv(glm::vec2(0, 0));
  _geometry.pushUv(glm::vec2(1, 0));
  if (_geometry.build() == false)
    return (false);
  return (true);
}

void	Bonus::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  (void)(clock);
  
  _textures[_bonusType]->bind();
  _geometry.draw(shader, getTransformation(), GL_QUADS);
}
