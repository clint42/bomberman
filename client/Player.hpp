//
// Player.hpp for  in /home/franel_j/tek2/cpp/bomberman
//
// Made by julie franel
// Login   <franel_j@epitech.net>
//
// Started on  Wed May  7 11:40:32 2014 julie franel
// Last update Wed May  7 13:18:54 2014 julie franel
//

#ifndef		PLAYER_HPP_
# define	PLAYER_HPP_

# include	<string>

namespace Client {

  class			Player
  {
    size_t		_id;
    size_t		_posX;
    size_t		_posY;
    size_t		_color;
    std::string		_name;

  public:
    Player(size_t id, size_t posX, size_t posY, size_t color, const std::string &name);
    ~Player();

    size_t		getId() const;
    size_t		getPosX() const;
    size_t		getPosY() const;
    size_t		getColor() const;
    const std::string	&getName() const;
  };
}

#endif		/* !PLAYER_HPP_ */
