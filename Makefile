############################################################
# Makefile template for small/medium C projects with GTK3.
# Please follow recommended project layout in README.
# Author : Alex Cândido
############################################################

# Configuração de Diretórios
APPS = ./apps
BIN = ./bin
DATA = ./data
DOC = ./doc
INCLUDE = ./include
LIB = ./lib
OBJ = ./obj
SERVICES = ./services
VIEWS = ./views

# Subdiretórios de Views
DASHBOARD = $(VIEWS)/dashboard
LAYOUTS = $(VIEWS)/layouts
PRODUCT_VIEWS = $(VIEWS)/product
STOCK_VIEWS = $(VIEWS)/stock

# Configuração do GTK3
GTK_CFLAGS = $(shell pkg-config --cflags gtk+-3.0)
GTK_LIBS = $(shell pkg-config --libs gtk+-3.0)

GTK_LIBS += -lm -lz -lpangocairo-1.0 -lpango-1.0 -lharfbuzz -latk-1.0 -lcairo-gobject -lcairo -lgdk_pixbuf-2.0 -lgio-2.0 -lgobject-2.0 -lglib-2.0

# Flags e Bibliotecas
CC = gcc
CFLAGS = -O3 -Wall -Wextra $(GTK_CFLAGS) -I$(INCLUDE)
LDFLAGS = -lm -L$(LIB) -led $(GTK_LIBS)

# Arquivos Fonte
APPS_SRC = $(wildcard $(APPS)/*.c)
SERVICES_SRC = $(wildcard $(SERVICES)/*.c)
DASHBOARD_SRC = $(wildcard $(DASHBOARD)/*.c)
LAYOUTS_SRC = $(wildcard $(LAYOUTS)/*.c)
PRODUCT_VIEWS_SRC = $(wildcard $(PRODUCT_VIEWS)/*.c)
STOCK_VIEWS_SRC = $(wildcard $(STOCK_VIEWS)/*.c)

# Estrutura de diretórios para objetos
OBJ_DIRS = $(OBJ)/services \
           $(OBJ)/views/dashboard \
           $(OBJ)/views/layouts \
           $(OBJ)/views/product \
           $(OBJ)/views/stock

# Objetos
SERVICES_OBJ = $(patsubst $(SERVICES)/%.c, $(OBJ)/services/%.o, $(SERVICES_SRC))
DASHBOARD_OBJ = $(patsubst $(DASHBOARD)/%.c, $(OBJ)/views/dashboard/%.o, $(DASHBOARD_SRC))
LAYOUTS_OBJ = $(patsubst $(LAYOUTS)/%.c, $(OBJ)/views/layouts/%.o, $(LAYOUTS_SRC))
PRODUCT_VIEWS_OBJ = $(patsubst $(PRODUCT_VIEWS)/%.c, $(OBJ)/views/product/%.o, $(PRODUCT_VIEWS_SRC))
STOCK_VIEWS_OBJ = $(patsubst $(STOCK_VIEWS)/%.c, $(OBJ)/views/stock/%.o, $(STOCK_VIEWS_SRC))

ALL_OBJ = $(SERVICES_OBJ) $(DASHBOARD_OBJ) $(LAYOUTS_OBJ) $(PRODUCT_VIEWS_OBJ) $(STOCK_VIEWS_OBJ)

# Lista de aplicativos (compilação de múltiplos aplicativos)
APPS_BIN = $(patsubst $(APPS)/%.c, $(BIN)/%, $(APPS_SRC))

# Garantir que os diretórios existam
DIRS = $(BIN) $(OBJ) $(LIB) $(OBJ_DIRS)
$(shell mkdir -p $(DIRS))

# Alvo principal
all: check-gtk3 libed myapps

# Regra para criar a biblioteca libed.a
libed: $(ALL_OBJ)
	ar -rcs $(LIB)/libed.a $(ALL_OBJ)

# Regras específicas para compilação de objetos
$(OBJ)/services/%.o: $(SERVICES)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/views/dashboard/%.o: $(DASHBOARD)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/views/layouts/%.o: $(LAYOUTS)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/views/product/%.o: $(PRODUCT_VIEWS)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/views/stock/%.o: $(STOCK_VIEWS)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para compilar os aplicativos
myapps: clean_apps $(APPS_BIN)

$(BIN)/%: $(APPS)/%.c $(LIB)/libed.a
	$(CC) $(CFLAGS) $< $(LDFLAGS) -o $@

# Geração automática de dependências de cabeçalhos
DEPENDENCIES = $(OBJ)/.dependencies
-include $(DEPENDENCIES)

# Gera as dependências de cabeçalhos
$(DEPENDENCIES): $(ALL_OBJ)
	@mkdir -p $(OBJ)
	@$(CC) -MM $(SERVICES_SRC) $(DASHBOARD_SRC) $(LAYOUTS_SRC) $(PRODUCT_VIEWS_SRC) $(STOCK_VIEWS_SRC) \
		-I $(INCLUDE) $(GTK_CFLAGS) | sed 's|^\(.*\)\.o:|$(OBJ)/\1.o:|' > $(DEPENDENCIES)

# Executar o aplicativo
run:
	$(BIN)/app

clean:
	rm -rf $(BIN)/* $(LIB)/* $(OBJ)/* $(DEPENDENCIES)

clean_apps:
	rm -rf $(BIN)/*

check-gtk3:
	@pkg-config --exists gtk+-3.0 || (echo "Error: GTK3 development files not found. Please install libgtk-3-dev (Linux) or gtk+3 (macOS)." && exit 1)

# Debug
print-%:
	@echo $* = $($*)

# Compilação paralela
.PHONY: all libed myapps clean clean_apps run-cli run-gtk check-gtk3 print-%
