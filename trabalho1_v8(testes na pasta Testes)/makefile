NAME_PROGRAM = final.exe
CC = gcc
FLAGS = -lm -pedantic -Wall 
C_FILES = $(wildcard *.c)
O_FILES = $(patsubst %.c, %.o, $(C_FILES))

all: $(O_FILES) create_executable

main.o: main.c
	@ echo "\033[1;32m"
	@ echo "Compiling main.c ..."
	@ $(CC) -c $< $(FLAGS)
	@ echo "\033[0m"

%.o: %.c %.h
	@ echo "\033[1;32m"
	@ echo "Compiling $< ..."
	@ $(CC) -c $< $(FLAGS)
	@ echo "\033[0m"

create_executable: 
	@ echo "\033[1;32m"
	@ echo "Creating executable..."
	@ $(CC) -o $(NAME_PROGRAM) $(O_FILES) $(FLAGS)
	@ echo "\033[0m"

run: 
	@ echo "\033[1;32m"
	@ echo "Running program ..."
	@ ./$(NAME_PROGRAM) Testes/Teste1/ 10
	@ ./$(NAME_PROGRAM) Testes/Teste2/ 4
	@ ./$(NAME_PROGRAM) Testes/Teste3/ 16
	@ ./$(NAME_PROGRAM) Testes/Teste4/ 4
	@ ./$(NAME_PROGRAM) Testes/Teste5/ 4
	@ ./$(NAME_PROGRAM) Testes/Teste6/ 15
	@ echo "\033[0m"

test: clean all run

valgrind: 
	@ echo "\033[1;32m"
	@ echo "Running valgrind ...\n"
	@ echo "Test 1:"
	@ echo "\033[0m"
	@ valgrind ./$(NAME_PROGRAM) Testes/Teste1/ 10
	@ echo "\033[1;32m"
	@ echo "Test 2:"
	@ echo "\033[0m"
	@ valgrind ./$(NAME_PROGRAM) Testes/Teste2/ 4
	@ echo "\033[1;32m"
	@ echo "Test 3:"
	@ echo "\033[0m"
	@ valgrind ./$(NAME_PROGRAM) Testes/Teste3/ 16
	@ echo "\033[1;32m"
	@ echo "Test 4:"
	@ echo "\033[0m"
	@ valgrind ./$(NAME_PROGRAM) Testes/Teste4/ 4
	@ echo "\033[1;32m"
	@ echo "Test 5:"
	@ echo "\033[0m"
	@ valgrind ./$(NAME_PROGRAM) Testes/Teste5/ 4
	@ echo "\033[1;32m"
	@ echo "Test 6:"
	@ echo "\033[0m"
	@ valgrind ./$(NAME_PROGRAM) Testes/Teste6/ 15
	@ echo "\033[1;32m"
	@ echo "\033[0m"

clean: 
	@ echo "\033[1;35m"
	@ echo "Removing temporary files ..."
	@ rm -rf $(NAME_PROGRAM) $(O_FILES)
	@ echo "\033[0m"
