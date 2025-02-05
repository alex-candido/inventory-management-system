############################################################
# Makefile template for small/medium C projects.
# Please follow recommended project layout in README.
# Author : Alex Cândido
############################################################

# Configuração de Diretórios e Variáveis
APPS = ./apps
BIN = ./bin
INCLUDE = ./include
LIB = ./lib
OBJ = ./obj
SRC = ./src

# Definição de Flags e Bibliotecas
FLAGS = -O3 -Wall
LIBS = -lm -led -L $(LIB)

# Lista de aplicativos (compilação de múltiplos aplicativos)
APPS_SRC = $(wildcard $(APPS)/*.c)
APPS_BIN = $(patsubst $(APPS)/%.c, $(BIN)/%, $(APPS_SRC))

# Lista de arquivos objeto da biblioteca
LIB_OBJ = $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(wildcard $(SRC)/*.c))

all: libed myapps

libed: $(LIB_OBJ)
	ar -rcs $(LIB)/libed.a $(LIB_OBJ)

# Regra para compilar múltiplos aplicativos
myapps: clean_apps $(APPS_BIN)

$(OBJ)/%.o: $(SRC)/%.c $(INCLUDE)/%.h libed
	gcc $(FLAGS) -c $< -I $(INCLUDE) -o $@

$(BIN)/%: $(APPS)/%.c libed
	gcc $(FLAGS) $< $(LIBS) -I $(INCLUDE) -o $@

# Geração automática de dependências de cabeçalhos
DEPENDENCIES = $(OBJ)/.dependencies

# Inclui as dependências geradas automaticamente
-include $(DEPENDENCIES)

# Gera as dependências de cabeçalhos
$(DEPENDENCIES): $(SRC)/*.c
	@mkdir -p $(OBJ)
	@gcc -MM $(SRC)/*.c -I $(INCLUDE) > $(DEPENDENCIES)

run:
	$(BIN)/app

clean:
	rm -rf $(BIN)/* $(LIB)/* $(OBJ)/*

clean_apps:
	rm -rf $(BIN)/*

# Compilação paralela
.PHONY: all libed myapps clean clean_apps run
