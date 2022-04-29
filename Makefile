CC = gcc

OBJDIR = obj
BINDIR = bin
MODULES := database network server
OBJDIRS := $(patsubst %, $(OBJDIR)/%, $(MODULES))
BINDIRS := $(patsubst %, $(BINDIR)/%, $(MODULES))

all: webserver database

webserver: build obj/main.o obj/server/Server.o obj/server/webpage.o
	@echo "Compliling HTTP server:"
	${CC} obj/main.o obj/server/Server.o obj/server/webpage.o -pthread -l sqlite3 -o bin/pi_net_status 

database: build obj/database/insert_connection_db.o
	@echo "Compliling Connection Database functions:"
	${CC} obj/database/insert_connection_db.o -l sqlite3 -o bin/insert

obj/%.o: src/%.c
	${CC} -c $< -o $@

obj/server/%.o: src/server/%.c
	${CC} -c $< -o $@

obj/database/%.o: src/database/%.c
	${CC} -c $< -o $@

build: $(OBJDIRS) $(BINDIRS) ping
	@echo $^

$(OBJDIRS):
	mkdir -p $@ 

$(BINDIRS):
	mkdir -p $@ 

ping: 
	cp src/network/ping.sh bin/network/ping.sh

clean:
	@echo "Cleaning up..."
	rm -rvf *.o main database/insert
