CC = gcc

all: main

main: main.c
	@echo "Compliling HTTP server."
	${CC} webpage.c Server.c main.c -o main

clean:
	@echo "Cleaning up..."
	rm -rvf main.o main
