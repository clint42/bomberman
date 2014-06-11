##
## Makefile for bomberman in /home/prieur_b/tek2/cpp/bomberman/client
## 
## Made by aurelien prieur
## Login   <prieur_b@epitech.net>
## 
## Started on  Mon May 19 14:27:29 2014 aurelien prieur
## Last update Wed Jun 11 10:26:07 2014 aurelien prieur
##

CXX =	clang++

CXXFLAGS += -I/home/prieur_b/LibBomberman_linux_x64/includes -I../common -Imenu -Werror -Wall -Wextra

LXXFLAGS =  -L/home/prieur_b/LibBomberman_linux_x64/libs -lgdl_gl -lGL -lGLEW -ldl -lrt -lfbxsdk -lSDL2 -lpthread -lssl -lcrypto

NAME =	client

SRC =   main.cpp \
	MenuHandler.cpp \
	menu/AMenu.cpp \
	menu/MainMenu.cpp \
	menu/CreateMenu.cpp \
	menu/MenuInput.cpp \
	menu/MenuButton.cpp \
	menu/MenuScroll.cpp \
	menu/MenuBackground.cpp \
	MapRender.cpp \
	AObject.cpp \
	GameEntities.cpp \
	GraphicEngine.cpp \
	EventsHandler.cpp \
	ClientCore.cpp \
	Parser.cpp \
	Player.cpp \
	Floor.cpp \
	Block.cpp \
	Bomb.cpp \
	Fire.cpp \
	Chrono.cpp \
	Score.cpp \
	FpsDisplay.cpp \
	GraphicalText.cpp \
	GraphicalLetter.cpp \
	../common/Map.cpp \
	../common/Mutex.cpp \
	../common/ScopedLock.cpp \
	../common/Poll.cpp \
	../common/ConnexionHandler.cpp \
	../common/Exception.cpp \
	../common/Signal.cpp \
	ThreadUI.cpp \
	UI.cpp \
	../server/Server.cpp \
	../server/Game.cpp \
	../server/Player.cpp

OBJ =	$(SRC:.cpp=.o)

$(NAME): all

all: $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(LXXFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
