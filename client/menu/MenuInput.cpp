//
// MenuInput.cpp for bomberman in /home/virol_g/tek2/cpp/bomberman/client/menu
// 
// Made by virol_g
// Login   <virol_g@epitech.net>
// 
// Started on  Wed Jun  4 18:35:35 2014 virol_g
// Last update Wed Jun 11 13:56:12 2014 aurelien prieur
//

#include	"MenuInput.hpp"

MenuInput::MenuInput(std::pair<size_t, size_t> const &pos,
		     std::pair<size_t, size_t> const &size,
		     glm::vec4 const &color): _color(color),
					      _output("", std::pair<size_t, size_t>(pos.first + 10, pos.second + 10), color, size.second - 20),
					      _pos(pos),
					      _size(size),
					      _hover(false)
{  
  this->initialize("./client/menu/ressources/gradationGreyTex.tga");
}

MenuInput::~MenuInput()
{
}

bool	MenuInput::initialize(const std::string &textureName)
{
  if (_texture.load(textureName) == false)
    {
      std::cerr << "Couldn't load MenuInput texture." << std::endl;
      return (false);
    }
  _geometry.setColor(_color);
  _geometry.pushVertex(glm::vec3(_pos.first, _pos.second, -1));
  _geometry.pushVertex(glm::vec3(_pos.first, _pos.second + _size.second, -1));
  _geometry.pushVertex(glm::vec3(_pos.first + _size.first, _pos.second + _size.second, -1));
  _geometry.pushVertex(glm::vec3(_pos.first + _size.first, _pos.second, -1));
  
  _geometry.pushUv(glm::vec2(0, 1));  
  _geometry.pushUv(glm::vec2(0, 0));
  _geometry.pushUv(glm::vec2(1, 0));
  _geometry.pushUv(glm::vec2(1, 1));

  _geometry.build();
  _keys.insert(std::pair<int, std::pair<char, bool> >(SDLK_KP_0, std::pair<char, bool>('0', false)));
  _keys.insert(std::pair<int, std::pair<char, bool> >(SDLK_KP_1, std::pair<char, bool>('1', false)));
  _keys.insert(std::pair<int, std::pair<char, bool> >(SDLK_KP_2, std::pair<char, bool>('2', false)));
  _keys.insert(std::pair<int, std::pair<char, bool> >(SDLK_KP_3, std::pair<char, bool>('3', false)));
  _keys.insert(std::pair<int, std::pair<char, bool> >(SDLK_KP_4, std::pair<char, bool>('4', false)));
  _keys.insert(std::pair<int, std::pair<char, bool> >(SDLK_KP_5, std::pair<char, bool>('5', false)));
  _keys.insert(std::pair<int, std::pair<char, bool> >(SDLK_KP_6, std::pair<char, bool>('6', false)));
  _keys.insert(std::pair<int, std::pair<char, bool> >(SDLK_KP_7, std::pair<char, bool>('7', false)));
  _keys.insert(std::pair<int, std::pair<char, bool> >(SDLK_KP_8, std::pair<char, bool>('8', false)));
  _keys.insert(std::pair<int, std::pair<char, bool> >(SDLK_KP_9, std::pair<char, bool>('9', false)));
  _keys.insert(std::pair<int, std::pair<char, bool> >(SDLK_BACKSPACE, std::pair<char, bool>('!', false)));
  return (true);
}

bool	MenuInput::update(const gdl::Clock &clock, gdl::Input &input)
{
  (void)clock;
  if (_hover)
    {
      for (std::map<int, std::pair<char, bool> >::iterator it = _keys.begin(); it != _keys.end(); ++it)
	{
	  if (input.getKey(it->first) == true && it->second.second == false)
	    {
	      if (it->first == SDLK_BACKSPACE)
		_output.delLetter();
	      else
		_output.addLetter(it->second.first);
	      it->second.second = true;
	    }
	  else if (input.getKey(it->first) == false)
	    it->second.second = false;
	}
    }
  return (true);
}

void	MenuInput::draw(gdl::AShader &shader, const gdl::Clock &clock)
{
  (void)clock;
  _texture.bind();
  _geometry.draw(shader, glm::mat4(1), GL_QUADS);
  _output.draw(shader);
}

void	MenuInput::hover(bool isHover)
{
  _hover = isHover;
}

std::string	MenuInput::getInput() const
{
  return (this->_output.getString());
}

std::pair<size_t, size_t>	MenuInput::getPos() const
{
  return (_pos);
}

std::pair<size_t, size_t>	MenuInput::getSize() const
{
  return (_size);
}
