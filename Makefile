############################################################
# Makefile for stock-sys project with GTK3.
############################################################

# Directory Configuration
APPS = ./apps
BIN = ./bin
DATA = ./data
DOC = ./doc
INCLUDE = ./include
LIB = ./lib
OBJ = ./obj
SERVICES = ./services
VIEWS = ./views

# Services subdirectories
PRODUCT_SERVICES = $(SERVICES)/product
STOCK_SERVICES = $(SERVICES)/stock
UTILS_SERVICES = $(SERVICES)/utils
REPORT_SERVICES = $(SERVICES)/report

# Views subdirectories
DASHBOARD = $(VIEWS)/dashboard
LAYOUTS = $(VIEWS)/layouts
PRODUCT_VIEWS = $(VIEWS)/product
STOCK_VIEWS = $(VIEWS)/stock

# GTK3 Configuration
GTK_CFLAGS = $(shell pkg-config --cflags gtk+-3.0)
GTK_LIBS = $(shell pkg-config --libs gtk+-3.0)

# Compiler flags and libraries
CC = gcc
CFLAGS = -O3 -Wall -Wextra $(GTK_CFLAGS) -I$(INCLUDE)
LDFLAGS = -lm -L$(LIB) -led $(GTK_LIBS)

# Source files
APPS_SRC = $(wildcard $(APPS)/*.c)
PRODUCT_SERVICES_SRC = $(wildcard $(PRODUCT_SERVICES)/*.c)
STOCK_SERVICES_SRC = $(wildcard $(STOCK_SERVICES)/*.c)
UTILS_SERVICES_SRC = $(wildcard $(UTILS_SERVICES)/*.c)
REPORT_SERVICES_SRC = $(wildcard $(REPORT_SERVICES)/*.c)

# Seed target
seed: $(BIN)/app
	@echo "Creating seed data directory..."
	@mkdir -p data/seeds
	@echo "Please ensure your CSV files (products.csv and stocks.csv) are in the data/seeds directory"
	@echo "Running seeds..."
	$(BIN)/app --seed
DASHBOARD_SRC = $(wildcard $(DASHBOARD)/*.c)
LAYOUTS_SRC = $(wildcard $(LAYOUTS)/*.c)
PRODUCT_VIEWS_SRC = $(wildcard $(PRODUCT_VIEWS)/*.c)
STOCK_VIEWS_SRC = $(wildcard $(STOCK_VIEWS)/*.c)
REPORT_VIEWS_SRC = $(wildcard $(VIEWS)/report/*.c)

# Object directories
OBJ_DIRS = $(OBJ)/services/product \
           $(OBJ)/services/stock \
           $(OBJ)/services/utils \
           $(OBJ)/services/report \
           $(OBJ)/views/dashboard \
           $(OBJ)/views/layouts \
           $(OBJ)/views/product \
           $(OBJ)/views/stock \
           $(OBJ)/views/report

# Object files
PRODUCT_SERVICES_OBJ = $(patsubst $(PRODUCT_SERVICES)/%.c, $(OBJ)/services/product/%.o, $(PRODUCT_SERVICES_SRC))
STOCK_SERVICES_OBJ = $(patsubst $(STOCK_SERVICES)/%.c, $(OBJ)/services/stock/%.o, $(STOCK_SERVICES_SRC))
UTILS_SERVICES_OBJ = $(patsubst $(UTILS_SERVICES)/%.c, $(OBJ)/services/utils/%.o, $(UTILS_SERVICES_SRC))
REPORT_SERVICES_OBJ = $(patsubst $(REPORT_SERVICES)/%.c, $(OBJ)/services/report/%.o, $(REPORT_SERVICES_SRC))
SERVICES_OBJ = $(PRODUCT_SERVICES_OBJ) $(STOCK_SERVICES_OBJ) $(UTILS_SERVICES_OBJ) $(REPORT_SERVICES_OBJ)

DASHBOARD_OBJ = $(patsubst $(DASHBOARD)/%.c, $(OBJ)/views/dashboard/%.o, $(DASHBOARD_SRC))
LAYOUTS_OBJ = $(patsubst $(LAYOUTS)/%.c, $(OBJ)/views/layouts/%.o, $(LAYOUTS_SRC))
PRODUCT_VIEWS_OBJ = $(patsubst $(PRODUCT_VIEWS)/%.c, $(OBJ)/views/product/%.o, $(PRODUCT_VIEWS_SRC))
STOCK_VIEWS_OBJ = $(patsubst $(STOCK_VIEWS)/%.c, $(OBJ)/views/stock/%.o, $(STOCK_VIEWS_SRC))
REPORT_VIEWS_OBJ = $(patsubst $(VIEWS)/report/%.c, $(OBJ)/views/report/%.o, $(REPORT_VIEWS_SRC))

ALL_OBJ = $(SERVICES_OBJ) $(DASHBOARD_OBJ) $(LAYOUTS_OBJ) $(PRODUCT_VIEWS_OBJ) $(STOCK_VIEWS_OBJ) $(REPORT_VIEWS_OBJ)

# Applications binaries
APPS_BIN = $(patsubst $(APPS)/%.c, $(BIN)/%, $(APPS_SRC))

# Create directories
DIRS = $(BIN) $(OBJ) $(LIB) $(OBJ_DIRS)
$(shell mkdir -p $(DIRS))

# Main targets
all: check-gtk3 libed myapps

# Create static library
libed: $(ALL_OBJ)
	ar -rcs $(LIB)/libed.a $(ALL_OBJ)

# Compilation rules
$(OBJ)/services/product/%.o: $(PRODUCT_SERVICES)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/services/stock/%.o: $(STOCK_SERVICES)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/views/dashboard/%.o: $(DASHBOARD)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/views/layouts/%.o: $(LAYOUTS)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/views/product/%.o: $(PRODUCT_VIEWS)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/views/stock/%.o: $(STOCK_VIEWS)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/views/report/%.o: $(VIEWS)/report/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/services/utils/%.o: $(UTILS_SERVICES)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/services/report/%.o: $(REPORT_SERVICES)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Build applications
myapps: clean_apps $(APPS_BIN)

$(BIN)/%: $(APPS)/%.c $(LIB)/libed.a
	$(CC) $(CFLAGS) $< $(LDFLAGS) -o $@

# Run application
run:
	$(BIN)/app

# Clean targets
clean:
	rm -rf $(BIN)/* $(LIB)/* $(OBJ)/*

clean_apps:
	rm -rf $(BIN)/*

# Check GTK3
check-gtk3:
	@pkg-config --exists gtk+-3.0 || (echo "Error: GTK3 development files not found. Please install libgtk-3-dev (Linux) or gtk+3 (macOS)." && exit 1)

.PHONY: all libed myapps clean clean_apps run check-gtk3
