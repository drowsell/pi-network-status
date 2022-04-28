#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "Server.h"
#include "server_config.h"
#include "webpage.h"

// Launches the http server
// Server will listen for a client
// Sends an HTML Dashboard page when requested
// After each request, the HTML page is checked for changes
void launch(struct Server *server) 
{
    while (1) 
    {
    	// Buffer to read client response
	int client_buffer_size = 5000;
    	char buffer_client[client_buffer_size];

	int http_buffer_size = 30000;
	char http_buffer[http_buffer_size];

	update_webpage("index.html");

	retrieve_webpage("index.html", http_buffer, http_buffer_size);

        printf("Waiting for client...\n");

        int address_length = sizeof(server->address);

        int client_socket = accept(server->socket,
                                   (struct sockaddr *)&server->address,
                                   (socklen_t *)&address_length);

        read(client_socket, buffer_client, http_buffer_size);
        printf("%s\n", buffer_client);
        write(client_socket, http_buffer, sizeof(http_buffer));
        close(client_socket);
        printf("Complete...\n");
    }
}

int main() 
{
    struct Server server = server_constructor(DOMAIN, SERVICE, PROTOCOL, INTERFACE, PORT, BACKLOG, launch);
    server.launch(&server);
}
