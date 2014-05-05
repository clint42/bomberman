##
## Makefile for  in /home/franel_j/tek2/cpp/bomberman
## 
## Made by julie franel
## Login   <franel_j@epitech.net>
## 
## Started on  Mon May  5 17:04:35 2014 julie franel
## Last update Mon May  5 19:47:53 2014 julie franel
##

CXX		=	clang++

RM		=	rm

NAME		=	bomberman

SRC		=	common/Map.cpp \
			main.cpp

OBJ		=	$(SRC:.cpp=.o)

LDFLAGS		=	-Iserver/ -Icommon/ -Iclient/ -lssl -lcrypto

CXXFLAGS	+=	-Wall -Wextra -Werror

all:			$(NAME)

$(NAME):		$(OBJ)
			$(CXX) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
			$(RM) -f $(OBJ)

fclean:			clean
			$(RM) -f $(NAME)


re:			fclean all

.PHONY:			all clean fclean re
