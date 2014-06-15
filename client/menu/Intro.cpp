//
// Intro.cpp for bomberman in /home/prieur_b/tek2/cpp/bomberman/client/menu
// 
// Made by aurelien prieur
// Login   <prieur_b@epitech.net>
// 
// Started on  Sun Jun 15 21:07:54 2014 aurelien prieur
// Last update Sun Jun 15 21:53:50 2014 aurelien prieur
//

#include "Intro.hpp"

Intro::Intro(gdl::SdlContext *sdlContext): _elapsedTime(0.0),
					   _lastTextDisplayed(-1),
					   _isFinished(false),
					   _sdlContext(sdlContext)
{
}

Intro::~Intro()
{
}

bool	Intro::initialize()
{
  glm::mat4     projection;

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  if (!_shader.load("./client/shaders/basic.fp", GL_FRAGMENT_SHADER)
      || !_shader.load("./client/shaders/basic.vp", GL_VERTEX_SHADER)
      || !_shader.build())
    {
      std::cerr << "Shader loading error" << std::endl;
      return (false);
    }
  projection = glm::ortho(0.f, 800.f, 600.f, 0.f, -1.f, 1.f);
  _shader.bind();
  _shader.setUniform("projection", projection);
  _shader.setUniform("view", glm::mat4(1));
  if (!_backgroundTex.load("./client/menu/ressources/backgroundIntro.tga"))
    {
      std::cerr << "Couldn't load intro background" << std::endl;
      return (false);
    }
  _background.setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
  _background.pushVertex(glm::vec3(0, 0, 0));
  _background.pushVertex(glm::vec3(800, 0, 0));
  _background.pushVertex(glm::vec3(800, 600, 0));
  _background.pushVertex(glm::vec3(0, 600, 0));
  _background.pushUv(glm::vec2(1, 1));
  _background.pushUv(glm::vec2(0, 1));
  _background.pushUv(glm::vec2(0, 0));
  _background.pushUv(glm::vec2(1, 0));
  _background.build();

  _texts.push_back(new GraphicalText("franel_j", std::pair<size_t, size_t>(435, 200),
				     glm::vec4(1.f, 1.f, 1.f, 1.f), 40, "airstrikeBold"));
  _texts.push_back(new GraphicalText("virol_g", std::pair<size_t, size_t>(435, 250),
				     glm::vec4(1.f, 1.f, 1.f, 1.f), 40, "airstrikeBold"));
  _texts.push_back(new GraphicalText("buret_j", std::pair<size_t, size_t>(435, 300),
				    glm::vec4(1.f, 1.f, 1.f, 1.f), 40, "airstrikeBold"));
  _texts.push_back(new GraphicalText("lafitt_g", std::pair<size_t, size_t>(435, 350),
				     glm::vec4(1.f, 1.f, 1.f, 1.f), 40, "airstrikeBold"));
  _texts.push_back(new GraphicalText("prieur_b", std::pair<size_t, size_t>(435, 400),
				     glm::vec4(1.f, 1.f, 1.f, 1.f), 40, "airstrikeBold"));
  _texts.push_back(new GraphicalText("monnet_s", std::pair<size_t, size_t>(435, 450),
				     glm::vec4(1.f, 1.f, 1.f, 1.f), 40, "airstrikeBold"));
  return (true);
}

bool	Intro::update()
{
  _sdlContext->updateClock(_clock);
  _sdlContext->updateInputs(_input);
  if (_input.getKey(SDLK_ESCAPE) || _input.getInput(SDL_QUIT, false))
    return (false);
  
  _elapsedTime += _clock.getElapsed();
  if (_lastTextDisplayed < static_cast<int>(_texts.size()) &&
      _elapsedTime > 1)
    {
      _elapsedTime = 0.0;
      ++_lastTextDisplayed;
    }
  if (_lastTextDisplayed == static_cast<int>(_texts.size()) && _elapsedTime > 3)
    {
      _isFinished = true;
    }
  return (true);
}

void	Intro::draw()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  _backgroundTex.bind();
  _background.draw(_shader, glm::mat4(1), GL_QUADS);
  for (int i = 0; i < _lastTextDisplayed; ++i)
    {
      _texts[i]->draw(_shader);
    }
  _sdlContext->flush();
}

bool	Intro::isFinished() const
{
  return (_isFinished);
}
