##
## Makefile for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
## 
## Made by aurelien prieur
## Login   <prieur_b@epitech.net>
## 
## Started on  Mon May 19 14:27:29 2014 aurelien prieur
## Last update Mon May 19 17:44:38 2014 aurelien prieur
##

CXX =	clang++

CXXFLAGS += -I/home/prieur_b/LibBomberman_linux_x64/includes -ggdb

LXXFLAGS =  -L/home/prieur_b/LibBomberman_linux_x64/libs -lgdl_gl -lGL -lGLEW -ldl -lrt -lfbxsdk -lSDL2 -lpthread

NAME =	client

SRC =   main.cpp \
	AObject.cpp \
	GameEntities.cpp \
	GraphicEngine.cpp \
	Model.cpp \
	../common/Mutex.cpp \
	../common/SafeQueue.cpp \
	../common/ScopedLock.cpp \
	../common/Select.cpp \
	ThreadUI.cpp \
	UI.cpp

OBJ =	$(SRC:.cpp=.o)

$(NAME): all

all: $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(LXXFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
