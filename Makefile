##
## Makefile for  in /home/franel_j/tek2/cpp/bomberman
## 
## Made by julie franel
## Login   <franel_j@epitech.net>
## 
## Started on  Mon May  5 17:04:35 2014 julie franel
## Last update Wed May  7 13:18:17 2014 julie franel
##

CXX		=	clang++

RM		=	rm

NAME		=	bomberman

SRC		=	main.cpp			\
			common/Map.cpp			\
			common/Exception.cpp		\
			server/Server.cpp		\
			server/Player.cpp		\
			server/Team.cpp			\
			server/ColorGenerator.cpp	\
			client/Player.cpp

OBJ		=	$(SRC:.cpp=.o)

CXXFLAGS	=	-Wall -Wextra -Werror 	\
			-Icommon/		\

all:			$(NAME)

$(NAME):		$(OBJ)
			$(CXX) -o $(NAME) $(OBJ) -lssl -lcrypto

clean:
			$(RM) -f $(OBJ)

fclean:			clean
			$(RM) -f $(NAME)


re:			fclean all

.PHONY:			all clean fclean re
