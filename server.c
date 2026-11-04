#include <stdio.h> //common C utils
#include <stdlib.h> //other common C utils
#include <sys/types.h> // common types
#include <sys/socket.h> // socket utils
#include <unistd.h> // unix api
#include <netinet/in.h> // protocol utils

void handle_connection(const int *server_socket);

int main(){
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(6969);
    server_address.sin_addr.s_addr = INADDR_ANY;

    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    if(server_socket < 0) {
        printf("Creating the socket failed (%d)\n\n", server_socket);
        exit(EXIT_FAILURE);
    }

    bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));
    listen(server_socket, 5);
    
    handle_connection(&server_socket);
    close(server_socket);

    return 0;
}

void handle_connection(const int *server_socket) {
    int client_socket = accept(*server_socket, NULL, NULL);
    char server_message[256] = "Connected to server!";
    send(client_socket, server_message, sizeof(server_message), 0);
    close(client_socket);
    return; 
}
