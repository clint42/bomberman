##
## Makefile for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
## 
## Made by aurelien prieur
## Login   <prieur_b@epitech.net>
## 
## Started on  Mon May 19 14:27:29 2014 aurelien prieur
## Last update Thu Jun 12 12:08:50 2014 buret_j
##

CXX =	clang++

CXXFLAGS += -I/home/$(USER)/LibBomberman_linux_x64/includes -Icommon -Iclient/menu -Werror -Wall -Wextra -o3

LXXFLAGS =  -L/home/$(USER)/LibBomberman_linux_x64/libs -lgdl_gl -lGL -lGLEW -ldl -lrt -lfbxsdk -lSDL2 -lpthread -lssl -lcrypto

NAME =	bomberman

SRC =   client/main.cpp \
	client/MenuHandler.cpp \
	client/menu/AMenu.cpp \
	client/menu/MainMenu.cpp \
	client/menu/CreateMenu.cpp \
	client/menu/JoinMenu.cpp \
	client/menu/MenuInput.cpp \
	client/menu/MenuButton.cpp \
	client/menu/MenuScroll.cpp \
	client/menu/MenuBackground.cpp \
	client/MapRender.cpp \
	client/AObject.cpp \
	client/GameEntities.cpp \
	client/GraphicEngine.cpp \
	client/EventsHandler.cpp \
	client/ClientCore.cpp \
	client/Parser.cpp \
	client/Player.cpp \
	client/Floor.cpp \
	client/Block.cpp \
	client/Bomb.cpp \
	client/Fire.cpp \
	client/Chrono.cpp \
	client/Score.cpp \
	client/FpsDisplay.cpp \
	client/GraphicalText.cpp \
	client/GraphicalLetter.cpp \
\
	common/Map.cpp \
	common/Mutex.cpp \
	common/ScopedLock.cpp \
	common/Poll.cpp \
	common/ConnexionHandler.cpp \
	common/Exception.cpp \
	common/Signal.cpp \
	client/ThreadUI.cpp \
	client/UI.cpp \
\
	server/Server.cpp \
	server/Server_adminCommand.cpp	\
	server/Server_filter.cpp	\
	server/Server_peerConnexion.cpp \
	server/Game.cpp \
	server/Player.cpp

OBJ =	$(SRC:.cpp=.o)

$(NAME): all

all: $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(LXXFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
