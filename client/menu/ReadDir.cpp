//
// ReadDir.cpp for bomberman in /home/virol_g/tek2/cpp/bomberman/client/menu
// 
// Made by virol_g
// Login   <virol_g@epitech.net>
// 
// Started on  Fri Jun 13 11:27:59 2014 virol_g
// Last update Fri Jun 13 11:59:21 2014 virol_g
//

#include	"ReadDir.hpp"

ReadDir::ReadDir(const std::string &dirName):
  _dirName(dirName)
{
}

ReadDir::~ReadDir()
{
  if (_dir != NULL)
    closedir(_dir);
}

bool	ReadDir::initialize()
{
  if ((_dir = opendir(_dirName.c_str())) == NULL)
    {
      std::cerr << "Couldn't read map names." << std::endl;
      return (false);
    }
  return (true);
}

std::string	ReadDir::readFileName()
{
  if ((_dirent = readdir(_dir)) != NULL)
    return (std::string(_dirent->d_name));
  return ("");
}
