##
## Makefile for  in /home/franel_j/tek2/cpp/bomberman
## 
## Made by julie franel
## Login   <franel_j@epitech.net>
## 
## Started on  Mon May  5 17:04:35 2014 julie franel
## Last update Sun Jun  8 20:59:53 2014 buret_j
##

CXX		=	clang++

RM		=	rm

NAME		=	bomberman

SRC		=	main.cpp			\
\
			common/Poll.cpp			\
			common/ConnexionHandler.cpp	\
			common/Map.cpp			\
			common/Exception.cpp		\
			common/Select.cpp		\
			common/Mutex.cpp		\
			common/ScopedLock.cpp		\
\
			server/Server.cpp		\
			server/Game.cpp			\
			server/Player.cpp		\
			server/Team.cpp			\
			server/ColorGenerator.cpp	\

OBJ		=	$(SRC:.cpp=.o)

CXXFLAGS	=	-Wall -Wextra -Werror 	\
			-Icommon/		\

all:			$(NAME)

$(NAME):		$(OBJ)
			$(CXX) -o $(NAME) $(OBJ) -lssl -lcrypto -lpthread

clean:
			$(RM) -f $(OBJ)

fclean:			clean
			$(RM) -f $(NAME)


re:			fclean all

.PHONY:			all clean fclean re
