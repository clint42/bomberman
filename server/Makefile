##
## Makefile for  in /home/franel_j/tek2/cpp/bomberman
## 
## Made by julie franel
## Login   <franel_j@epitech.net>
## 
## Started on  Mon May  5 17:04:35 2014 julie franel
## Last update Thu Jun 12 12:08:03 2014 buret_j
##

CXX		=	clang++

RM		=	rm

NAME		=	bomberman

SRC		=	main.cpp			\
\
			../common/Poll.cpp		\
			../common/ConnexionHandler.cpp	\
			../common/Map.cpp		\
			../common/Exception.cpp		\
			../common/Mutex.cpp		\
			../common/ScopedLock.cpp	\
\
			Server.cpp		\
			Server_adminCommand.cpp	\
			Server_filter.cpp	\
			Server_peerConnexion.cpp \
			Game.cpp		\
			Player.cpp		\
			Team.cpp		\
			ColorGenerator.cpp	\

OBJ		=	$(SRC:.cpp=.o)

CXXFLAGS	=	-Wall -Wextra -Werror -ggdb	\
			-I../common/		\

all:			$(NAME)

$(NAME):		$(OBJ)
			$(CXX) -o $(NAME) $(OBJ) -lssl -lcrypto -lpthread

clean:
			$(RM) -f $(OBJ)

fclean:			clean
			$(RM) -f $(NAME)


re:			fclean all

.PHONY:			all clean fclean re
