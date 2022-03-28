#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

int main(void){

    char server_message[256] = "You have reached the server!";

    // create the server socket
    int server_socket;
    server_socket = socket (AF_INET, SOCK_STREAM, 0);

    // define the server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // bind the socket to our specified IP and port
    int server_status = bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));

    //
    listen(server_socket, 1); // 2nd param == max clients

    //
    int client_socket;
    client_socket = accept(server_socket, NULL, NULL); // 2: struct sockaddr*, 3: struct sockaddr* length

    // send message to client_socket
    send(client_socket, server_message, strlen(server_message), 0); // 3: optional flag param

    // close the socket
    close(server_socket);
}
