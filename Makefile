EXEC = pseudo-shell
FLAGS = -g -o
CC = gcc

all: pseudo-shell

pseudo-shell: main.o string_parser.o command.o helper_command.o
	gcc -g -o pseudo-shell main.o string_parser.o command.o helper_command.o

main.o: main.c
	gcc -c main.c

string_parser.o: string_parser.c string_parser.h
	gcc -c string_parser.c

command.o: command.c command.h
	gcc -c command.c

helper_command.o: helper_command.c helper_command.h
	gcc -c helper_command.c

clean:
	rm -f *.o pseudo-shell

