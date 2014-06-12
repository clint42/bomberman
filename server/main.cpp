//
// main.cpp for  in /home/buret_j/rendu/bomberman/server
// 
// Made by buret_j
// Login   <buret_j@epitech.net>
// 
// Started on  Thu Jun 12 10:40:33 2014 buret_j
// Last update Thu Jun 12 11:17:20 2014 buret_j
//

#include "Server.hpp"
#include "ConnexionHandler.hpp"

int debug_align = 0;

int main() {

  ConnexionHandler co;
  Server::Server   s(&co);
  
  s.run();

  return 0;
}
