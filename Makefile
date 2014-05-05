##
## Makefile for  in /home/franel_j/tek2/cpp/bomberman
## 
## Made by julie franel
## Login   <franel_j@epitech.net>
## 
## Started on  Mon May  5 17:04:35 2014 julie franel
## Last update Mon May  5 17:08:04 2014 julie franel
##

CXX		=	clang++

RM		=	rm

NAME		=	bomberman

SRC		=	common/map.cpp \
			main.cpp

OBJ		=	$(SRC:.cpp=.o)

INC		=	-Iserver/ -Icommon/ -Iclient/

CXXFLAGS	+=	-Wall -Wextra -Werror

all:			$(NAME)

$(NAME):		$(OBJ)
			$(CXX) -o $(NAME) $(OBJ) $(INC)

clean:
			$(RM) -f $(OBJ)

fclean:			clean
			$(RM) -f $(NAME)


re:			fclean all

.PHONY:			all clean fclean re
