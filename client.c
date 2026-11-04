#include <stdio.h> //common C utils
#include <stdlib.h> //other common C utils
#include <sys/types.h> // common types
#include <sys/socket.h> // socket utils
#include <unistd.h> // unix api
#include <netinet/in.h> // protocol utils

void handle_response(const int *network_socket);

int main(){
    int network_socket;
    network_socket = socket(AF_INET, SOCK_STREAM, 0);

    if(network_socket < 0) {
        printf("Creating the socket failed (%d)\n\n", network_socket);
        exit(EXIT_FAILURE);
    }

    handle_response(&network_socket);
    close(network_socket);

    return 0;
}

void handle_response(const int *network_socket) {
    int connection_status = connect(*network_socket, (struct sockaddr*) &server_address, sizeof(server_address));
    char server_response[256];
    recv(*network_socket, &server_response, sizeof(server_response), 0);

    printf("response: %s\n", server_response);

    return;
}