//
// ReadDir.hpp for bomberman in /home/virol_g/tek2/cpp/bomberman/client/menu
// 
// Made by virol_g
// Login   <virol_g@epitech.net>
// 
// Started on  Fri Jun 13 11:23:58 2014 virol_g
// Last update Fri Jun 13 11:50:26 2014 virol_g
//

#ifndef		READDIR_HPP_
# define	READDIR_HPP_

# include	<sys/types.h>
# include	<dirent.h>
# include	<vector>
# include	<string>
# include	<iostream>

class		ReadDir
{
  DIR		*_dir;
  struct dirent	*_dirent;
  std::string	_dirName;
public:
  ReadDir(const std::string &dirName);
  ~ReadDir();
  bool	initialize();
  std::string	readFileName();
};

#endif		// !READDIR_HPP_
