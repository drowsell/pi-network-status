CC = gcc

all: main.o

main.o: insert_connection_db.o main.c
	@echo "Compliling HTTP server."
	${CC} server/webpage.c server/Server.c main.c -pthread -l sqlite3 -o main

insert_connection_db.o: database/insert_connection_db.c
	@echo "Compliling Connection Database function.s"
	${CC} database/insert_connection_db.c -l sqlite3 -o database/insert
clean:
	@echo "Cleaning up..."
	rm -rvf main.o main
	rm -rvf database/insert.o database/insert
