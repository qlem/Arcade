##
## Makefile for arcade in /home/dommer_c/rendu/cpp_arcade
## 
## Made by dommer_c
## Login   <clement.dommerc@epitech.eu>
## 
## Started on  Thu Mar 23 14:27:24 2017 dommer_c
## Last update Thu May  4 01:55:46 2017 dommer_c
##

CC		:=	g++

RM		:=	rm -f

CXXFLAGS	:=	-std=c++11 ## -W -Wextra -Wall -Werror -ansi -pedantic

LIB_DIR		:=	lib
LIB_SRC_DIR	:=	lib_src
LIB_OBJ_DIR	:=	lib_obj
GAMES_DIR	:=	games
GAMES_OBJ_DIR	:=	games_obj
ARCADE_SRC_DIR	:=	arcade_src
ARCADE_OBJ_DIR	:=	arcade_obj
PACMAN_SRC_DIR	:=	games_src/Pacman
SNAKE_SRC_DIR	:=	games_src/Snake
SOLAR_SRC_DIR	:=	games_src/Solar_Fox

ARCADE		:=	arcade
CACA		:=	caca.so
CACA		:=	$(addprefix $(LIB_DIR)/, $(CACA))
SFML		:=	sfml.so
SFML		:=	$(addprefix $(LIB_DIR)/, $(SFML))
PACMAN		:=	pacman.so
PACMAN		:=	$(addprefix $(GAMES_DIR)/, $(PACMAN))
SNAKE		:=	snake.so
SNAKE		:=	$(addprefix $(GAMES_DIR)/, $(SNAKE))
SOLAR		:=	solar_fox.so
SOLAR		:=	$(addprefix $(GAMES_DIR)/, $(SOLAR))

## sources

SRC_ARCADE	:=	main.cpp	\
			Core.cpp	\
			LibLoader.cpp	\
			GraphicLib.cpp	\
			GameLib.cpp	\
			Scoring.cpp
SRC_ARCADE	:=	$(addprefix $(ARCADE_SRC_DIR)/, $(SRC_ARCADE))

SRC_CACA	:=	libCaca.cpp
SRC_CACA	:=	$(addprefix $(LIB_SRC_DIR)/, $(SRC_CACA))

SRC_SFML	:=	libSFML.cpp
SRC_SFML	:=	$(addprefix $(LIB_SRC_DIR)/, $(SRC_SFML))

SRC_PACMAN	:=	Pacman.cpp	\
			PacEntities.cpp	\
			PacDirection.cpp	\
			PacPosition.cpp
SRC_PACMAN	:=	$(addprefix $(PACMAN_SRC_DIR)/, $(SRC_PACMAN))

SRC_SNAKE	:=	SnaDirection.cpp	\
			SnaFood.cpp		\
			SnaGame.cpp		\
			SnaMap.cpp		\
			SnaPlayer.cpp		\
			SnaPos.cpp		\
			SnaScore.cpp		\
			Snake.cpp		\
			SnaTailSection.cpp
SRC_SNAKE	:=	$(addprefix $(SNAKE_SRC_DIR)/, $(SRC_SNAKE))

SRC_SOLAR	:=	SolDirection.cpp	\
			SolEnemy.cpp		\
			SolEntity.cpp		\
			SolGame.cpp		\
			SolCreateLevels.cpp	\
			SolMap.cpp		\
			SolPlayer.cpp		\
			SolPos.cpp		\
			SolPowerUp.cpp		\
			SolScore.cpp		\
			SolShot.cpp		\
			SolWall.cpp
SRC_SOLAR	:=	$(addprefix $(SOLAR_SRC_DIR)/, $(SRC_SOLAR))

## objs

OBJ_ARCADE	:=	$(SRC_ARCADE:.cpp=.o)
OBJ_ARCADE	:=	$(patsubst $(ARCADE_SRC_DIR)/%.cpp, $(ARCADE_OBJ_DIR)/%.o, $(SRC_ARCADE))

OBJ_CACA	:=	$(SRC_CACA:.cpp=.o)
OBJ_CACA	:=	$(patsubst $(LIB_SRC_DIR)/%.cpp, $(LIB_OBJ_DIR)/%.o, $(SRC_CACA))

OBJ_SFML	:=	$(SRC_SFML:.cpp=.o)
OBJ_SFML	:=	$(patsubst $(LIB_SRC_DIR)/%.cpp, $(LIB_OBJ_DIR)/%.o, $(SRC_SFML))

OBJ_PACMAN	:=	$(SRC_PACMAN:.cpp=.o)
OBJ_PACMAN	:=	$(patsubst $(PACMAN_SRC_DIR)/%.cpp, $(GAMES_OBJ_DIR)/%.o, $(SRC_PACMAN))

OBJ_SNAKE	:=	$(SRC_SNAKE:.cpp=.o)
OBJ_SNAKE	:=	$(patsubst $(SNAKE_SRC_DIR)/%.cpp, $(GAMES_OBJ_DIR)/%.o, $(SRC_SNAKE))

OBJ_SOLAR	:=	$(SRC_SOLAR:.cpp=.o)
OBJ_SOLAR	:=	$(patsubst $(SOLAR_SRC_DIR)/%.cpp, $(GAMES_OBJ_DIR)/%.o, $(SRC_SOLAR))

$(ARCADE_OBJ_DIR)/%.o:	$(ARCADE_SRC_DIR)/%.cpp
	$(CC) -c $(CXXFLAGS) $< -o $@

$(LIB_OBJ_DIR)/%.o:	$(LIB_SRC_DIR)/%.cpp
	$(CC) -c $(CXXFLAGS) -fPIC $< -o $@

$(GAMES_OBJ_DIR)/%.o:	$(PACMAN_SRC_DIR)/%.cpp
	$(CC) -c $(CXXFLAGS) -fPIC $< -o $@

$(GAMES_OBJ_DIR)/%.o:	$(SNAKE_SRC_DIR)/%.cpp
	$(CC) -c $(CXXFLAGS) -fPIC $< -o $@

$(GAMES_OBJ_DIR)/%.o:	$(SOLAR_SRC_DIR)/%.cpp
	$(CC) -c $(CXXFLAGS) -fPIC $< -o $@

## règles

all:		$(CACA) $(SFML) $(ARCADE) $(PACMAN) $(SNAKE) $(SOLAR)

caca:		$(CACA)

sfml:		$(SFML)

pacman:		$(PACMAN)

snake:		$(NAKE)

solar:		$(SOLAR)

main:		$(ARCADE)

$(CACA):	$(OBJ_CACA)
	$(CC) -shared -o $(CACA) $(OBJ_CACA) -lcaca

$(SFML):	$(OBJ_SFML)
	$(CC) -shared -o $(SFML) $(OBJ_SFML) -lsfml-graphics -lsfml-window -lsfml-system

$(PACMAN):	$(OBJ_PACMAN)
	$(CC) -shared -o $(PACMAN) $(OBJ_PACMAN)

$(SNAKE):	$(OBJ_SNAKE)
	$(CC) -shared -o $(SNAKE) $(OBJ_SNAKE)

$(SOLAR):	$(OBJ_SOLAR)
	$(CC) -shared -o $(SOLAR) $(OBJ_SOLAR)

$(ARCADE):	$(OBJ_ARCADE)
	$(CC) -o $(ARCADE) $(OBJ_ARCADE) -ldl

clean:
		$(RM) *~
		$(RM) #*#
		$(RM) $(OBJ_ARCADE) $(OBJ_CACA) $(OBJ_SFML) $(OBJ_PACMAN) $(OBJ_SNAKE) $(OBJ_SOLAR)

fclean:		clean
		$(RM) $(ARCADE) $(CACA) $(SFML) $(PACMAN) $(SNAKE) $(SOLAR)

re:		fclean all
