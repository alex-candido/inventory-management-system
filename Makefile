############################################################
# Makefile template for small/medium C projects.
# Please follow recommended project layout in README.
# Author : Alex Cândido
############################################################

APPS = ./app
BIN = ./bin
DATA = ./data
INCLUDE = ./include
LIB = ./lib
OBJ = ./obj
SRC = ./src

FLAGS = -O3 -Wall
LIBS = -lm -led -L $(LIB)

run:
	$(BIN)/app

clean:
	rm -rf $(BIN)/* $(LIB)/* $(OBJ)/*

clean_apps:
	rm -rf $(BIN)/*
