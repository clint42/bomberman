/*
** Md5it.cpp for Md5it in /home/lafitt_g/Tek2/c++/bomberman/common
** 
** Made by lafitt_g
** Login   <lafitt_g@lafittg>
** 
** Started on  Mon May  5 17:01:29 2014 lafitt_g
** Last update Mon May  5 19:49:32 2014 lafitt_g
*/

#include <openssl/md5.h>
#include <fstream>
#include <iostream>
#include <string>
#include "Exception.hh"

void
Map::Md5it(std::string filename, std::string &save)
{
  std::ifstream filemap(filename.c_str(), std::ios::in);

  if(filemap)
    {
      char key[MD5_DIGEST_LENGTH] = {0};
      std::string content, line;

      while (filemap >> line)
        content += line;
      filemap.close();
      MD5((unsigned char *)content.c_str(), content.size(), (unsigned char *)key);
      save = key;
    }
  else
    {
      throw Md5Exception();
    }
}

