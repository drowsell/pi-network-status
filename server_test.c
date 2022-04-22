#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "Server.h"

void launch(struct Server *server)
{
    // File with html page
    char buffer[30000];

    char http_header[30000] = "HTTP/1.1 200 OK\r\n\n";
    char response_data[1024];

    // Grab HTML data
    FILE *html_data;
    html_data = fopen("index.html", "r");
    char line[1024];
    while (fgets(line, sizeof(line), html_data))
    {
        strcat(response_data, line);
    }

    strcat(http_header, response_data);

    while (1)
    {

        // write(client_socket, http_header, sizeof(http_header));
        printf("Waiting...\n");

        int address_length = sizeof(server->address);

        int client_socket = accept(server->socket,
                                   (struct sockaddr *)&server->address,
                                   (socklen_t *)&address_length);
        printf("6\n");

        read(client_socket, buffer, 30000);
        printf("%s\n", buffer);
        write(client_socket, http_header, sizeof(http_header));
        printf("%s\n", http_header);
        close(client_socket);
        printf("Done...\n");
    }
}

int main()
{
    struct Server server = server_constructor(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 8002, 10, launch);
    server.launch(&server);
}