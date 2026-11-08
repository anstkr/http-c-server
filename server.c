#include <stdio.h> //common C utils
#include <stdlib.h> //other common C utils
#include <sys/types.h> // common types
#include <sys/socket.h> // socket utils
#include <unistd.h> // unix api
#include <netinet/in.h> // protocol utils
#include <string.h>

void handle_connection(const int *server_socket);
void create_http_response(char *response, const char *request);
char *get_requested_page_html(const char *request);
void get_page_from_request(char *page, const char *request);
void get_method();
char *get_file_context(char *filename);

int main(){
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(6969);
    server_address.sin_addr.s_addr = INADDR_ANY;

    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    printf("Creating the socket...\n");
    if(server_socket < 0) {
        printf("Creating the socket failed (%d)\n\n", server_socket);
        exit(EXIT_FAILURE);
    }
    printf("Socket created.\n");

    printf("Binding the socket...\n");
    bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));
    listen(server_socket, 5);
    
    for(;;){
        handle_connection(&server_socket);
    }

    close(server_socket);
    return 0;
}

void handle_connection(const int *server_socket) {
    int client_socket = accept(*server_socket, NULL, NULL);

    char http_request[256];
    ssize_t request = recv(client_socket, http_request, sizeof(http_request), 0);
    printf("HTTP request: %s\n\n", http_request);

    if (request < 0) {
        perror("request");
    }

    char http_response[1024] = "";
    create_http_response(http_response, http_request);
    send(client_socket, http_response, sizeof(http_response), 0);

    close(client_socket);
    return; 
}

void create_http_response(char *response, const char *request) {
    char response_data[] = "HTTP/1.1 200 OK\r\n"
    "Date: Mon, 27 Jul 2009 12:28:53 GMT\r\n"
    "Server: http-c-server\r\n"
    "Content-Type: text/html\r\n"
    "\r\n";

    strcat(response, response_data);

    // TODO: handle method
    // char method[] = get_method();

    char *html = get_requested_page_html(request);
    strcat(response, html);
}

char *get_requested_page_html(const char *request) {
    // TODO: actually receiving and parsing the page
    char page[256] = "";
    get_page_from_request(page, request);

    char *html = get_file_context("html/index.html");
    return html;
}

char *get_file_context(char *filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("error while opening the file.\n");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    int length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *data = malloc(sizeof(char) * (length+1));
    char c;
    int i = 0;

    while ((c = fgetc(file)) != EOF) {
        data[i] = c;
        i++;
    }
    data[i] = '\0';
    fclose(file);
    return data;
}

void get_page_from_request(char *page, const char *request) {
    strcat(page,"/");
}

void get_method() {
}
