#include "Game.hpp"

void *
Server::Game::trampoline_botsProcessing(void *g) {
  static_cast<Server::Game *>(g)->botsProcessing();
  return NULL;
}

void
Server::Game::botsProcessing() {
  t_cmd *	c;
  (void)c;
  while (!_ended) {
    if (_started && !_paused) {
      std::cout << "On update les bots. Ca va chier !" << std::endl;
      for (std::list<Bot *>::iterator it = _bots.begin(); it != _bots.end(); ++it)
	(*it)->actionBot(this->timeLeft(), _events);
    }
    else {
      usleep(200000);
    }
  }
}
