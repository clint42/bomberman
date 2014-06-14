#include "Game.hpp"

bool
Server::Game::orientUp(Player *p, t_cmd *c)
{
  c->action = "ROTATE";
  return(p->orient(Server::Player::UP));
}

bool
Server::Game::orientRight(Player *p, t_cmd *c)
{
  c->action = "ROTATE";
  return(p->orient(Server::Player::RIGHT));
}

bool
Server::Game::orientDown(Player *p, t_cmd *c)
{
  c->action = "ROTATE";
  return(p->orient(Server::Player::DOWN));
}

bool
Server::Game::orientLeft(Player *p, t_cmd *c)
{
  c->action = "ROTATE";
  return(p->orient(Server::Player::LEFT));
}
