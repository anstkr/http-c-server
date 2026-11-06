#include <stdio.h> //common C utils
#include <stdlib.h> //other common C utils
#include <sys/types.h> // common types
#include <sys/socket.h> // socket utils
#include <unistd.h> // unix api
#include <netinet/in.h> // protocol utils

void handle_response(const int *network_socket, const struct sockaddr_in *server_address);

int main(){
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(6969);
    server_address.sin_addr.s_addr = INADDR_ANY;

    int network_socket;
    network_socket = socket(AF_INET, SOCK_STREAM, 0);

    if(network_socket < 0) {
        perror("Creating the socket failed");
    }

    handle_response(&network_socket, &server_address);
    close(network_socket);

    return 0;
}

void handle_response(const int *network_socket, const struct sockaddr_in *server_address) {
    int connection_status = connect(*network_socket, (const struct sockaddr*) server_address, sizeof(*server_address));
    
    if (connection_status < 0) {
        perror("connection_status");
    }

    char http_request[] = "GET / HTTP/1.1";
    send(*network_socket, http_request, sizeof(http_request), 0);

    char server_response[256];
    ssize_t response = recv(*network_socket, server_response, sizeof(server_response), 0);

    if (response < 0) {
        perror("response");
    }

    printf("response: %s\n", server_response);

    return;
}