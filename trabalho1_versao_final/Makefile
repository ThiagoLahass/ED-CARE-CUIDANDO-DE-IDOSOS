APPS = ./apps
BIN = ./bin
INCLUDE = ./include
LIB = ./lib
OBJ = ./obj
SRC = ./src

FLAGS = -pedantic -Wall
LIBS = -lm -led -L $(LIB)



all: libed myapps

libed: \
	$(OBJ)/idoso.o \
	$(OBJ)/cuidador.o \
	$(OBJ)/lista_idoso.o \
	$(OBJ)/lista_cuidador.o
	@ ar -rcs $(LIB)/libed.a $(OBJ)/*.o


myapps: clean_apps \
	$(BIN)/main

$(OBJ)/%.o: $(SRC)/%.c $(INCLUDE)/%.h
	@ echo "\033[1;32m"
	@ echo "Compiling $< ..."
	@ gcc $(FLAGS) -c $< -I $(INCLUDE) -lm -o $@
	@ echo "\033[0m"

$(BIN)/%: $(APPS)/%.c
	@ echo "\033[1;32m"
	@ echo "Creating executable $@ ..."
	@ gcc $(FLAGS) $< $(LIBS) -I $(INCLUDE) -lm -o $@
	@ echo "\033[0m"

run:
	@ echo "\033[1;32m"
	@ echo "Running program with $(X) readings ..."
	@ $(BIN)/main $(X)
	@ echo "\033[0m"

clean:
	@ echo "\033[1;35m"
	@ echo "Removing all temporaries files ..."
	@ rm -rf $(BIN)/* $(LIB)/* $(OBJ)/*
	@ echo "\033[0m"

clean_apps:
	@ echo "\033[1;35m"
	@ echo "Removing all bins ..."
	@ @ rm -rf $(BIN)/*
	@ echo "\033[0m"
