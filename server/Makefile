CC = gcc-11

all: server_test

server_test: server_test.c
	@echo "Compliling test HTTP server."
	${CC} Server.c server_test.c -o server_test

clean:
	@echo "Cleaning up..."
	rm -rvf server_test.o server_test