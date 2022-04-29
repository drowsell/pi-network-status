CC = gcc

all: webserver database

webserver: main.o Server.o webpage.o
	@echo "Compliling HTTP server."
	${CC} main.o Server.o webpage.o -pthread -l sqlite3 -o pi_net_status 

database: insert_connection_db.o
	@echo "Compliling Connection Database functions"
	${CC} insert_connection_db.o -l sqlite3 -o database/insert

main.o: main.c
	${CC} -c server/webpage.c server/Server.c main.c 

Server.o: server/Server.c
	${CC} -c server/Server.c

webpage.o: server/webpage.c
	${CC} -c server/webpage.c 

insert_connection_db.o: database/insert_connection_db.c
	${CC} -c database/insert_connection_db.c -l sqlite3

clean:
	@echo "Cleaning up..."
	rm -rvf *.o main database/insert
