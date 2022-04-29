CC = gcc

OBJDIR = obj
BINDIR = bin
MODULES := build database network server
OBJDIRS := $(patsubst %, $(OBJDIR)/%, $(MODULES))
BINDIRS := $(patsubst %, $(BINDIR)/%, $(MODULES))

all: webserver database

install: 
	./src/build/pi_network_status_install.sh
	sudo mv pi-network-status.service /etc/systemd/system/pi-network-status.service
	sudo systemctl enable pi-network-status


uninstall: 
	sudo systemctl disable pi-network-status
	sudo rm /etc/systemd/system/pi-network-status.service

webserver: build obj/main.o obj/server/Server.o obj/server/webpage.o
	@echo "Compliling HTTP server:"
	${CC} obj/main.o obj/server/Server.o obj/server/webpage.o -pthread -l sqlite3 -o bin/pi_network_status 

database: build obj/database/insert_connection_db.o
	@echo "Compliling Connection Database functions:"
	${CC} obj/database/insert_connection_db.o -l sqlite3 -o bin/database/insert

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
	rm -rvf bin obj pi_network_status
