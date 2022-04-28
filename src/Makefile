CC = gcc

all: main

main: main.c
	@echo "Compliling HTTP server."
	${CC} server/webpage.c server/Server.c main.c -l sqlite3 -o main

clean:
	@echo "Cleaning up..."
	rm -rvf main.o main
