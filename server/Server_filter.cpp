#include "Server.hpp"

void
Server::Server::getInformation(const std::string *msg, size_t *field, size_t cur_1, size_t cur_2)
{
  if (cur_1 != std::string::npos && cur_2 != std::string::npos)
    {
      std::stringstream convert(msg->substr(cur_1, cur_2));
      convert >> *field;
    }
  else
    field = 0;
}

void
Server::Server::filterMsg() {
  t_cmd *	cmd = new t_cmd;
  size_t        cur_1 = 0;
  size_t        cur_2 = 0;

  if (this->_messages.size() > 0)
    {
      std::string *msg = this->_messages.front();
      std::cout << "Msg recu [" << *msg << "]" << std::endl;
      if (_game)
	cmd->date = _game->timeLeft();
      cur_1 = msg->find(" ", cur_1);
      this->getInformation(msg, &cmd->id, cur_2, cur_1);
      cur_2 = msg->find(" ", cur_1 + 1);
      this->getInformation(msg, &cmd->pos.first, cur_1 + 1, cur_2 - (cur_1 + 1));
      cur_1 = msg->find(" ", cur_2 + 1);
      this->getInformation(msg, &cmd->pos.second, cur_2 + 1, cur_1 - (cur_2 + 1));
      cur_2 = msg->find(" ", cur_1 + 1);
      cmd->action = msg->substr(cur_1 + 1, cur_2 - (cur_1 + 1));
      while (cur_2 != std::string::npos && cur_1 != std::string::npos) {
	cur_1 = msg->find(" ", cur_2 + 1);
	cmd->params.push_back(msg->substr(cur_2 + 1, cur_1 - (cur_2 + 1)));
	if (cur_1 != std::string::npos && (cur_2 = msg->find(" ", cur_1 + 1)) != std::string::npos)
	  cmd->params.push_back(msg->substr(cur_1 + 1, cur_2 - (cur_1 + 1)));
      }
      _messages.pop_front();
      delete msg;
      this->putCmdInQueue(cmd);
    }
}

void
Server::Server::putCmdInQueue(t_cmd *cmd) {
  DEBUG("Server::Server::putCmdInQueue()", 1);
  if (this->_game && _game->isStarted() && !_game->isPaused() && !_game->ended()
      && ((cmd->params.size() == 0 && cmd->action == "BOMB") ||
	  (cmd->params.size() == 1 && (cmd->action == "MOVE" &&
				       (cmd->params[0] == "UP" ||
					cmd->params[0] == "DOWN" ||
					cmd->params[0] == "LEFT" ||
					cmd->params[0] == "RIGHT"))))) {
    DEBUG("Server::Server::putCmdInQueue() => c'est une commande de deplacement", 0);
    this->_game->addEvent(cmd);
  }
  else if (((!cmd->action.compare("PAUSE") ||
	     !cmd->action.compare("KILL") ||
	     !cmd->action.compare("SAVE")) && cmd->params.size() == 0) ||
	   (!cmd->action.compare("CONFIG") && cmd->params.size() == 5) ||
	   (!cmd->action.compare("WITHFRIEND") && cmd->params.size() == 1) ||
	   (!cmd->action.compare("MD5") && cmd->params.size() == 1)) {
    this->_ext.push_back(cmd);
    DEBUG("Server::Server::putCmdInQueue() => la commande est bonne", 0);
  }
  else {
    DEBUG("Server::Server::putCmdInQueue() => la commande pue ou soit on a pas le faire", 0);
    delete cmd;
  }
  DEBUG("! Server::Server::putCmdInQueue()", -1);
}
