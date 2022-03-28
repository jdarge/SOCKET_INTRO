#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

int main(void) {

    // create a socket
    int network_socket;
    network_socket = socket(AF_INET, SOCK_STREAM, 0);

    // specify an address for the socket
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080); // int -> port number format
    server_address.sin_addr.s_addr = INADDR_ANY; // address we want

    // connect to the address
    int connect_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));

    // check for errors
    if(connect_status < 0) {
        printf("Error: Unable to connect to remote host.\n");

    }

    // recieve data from the server
    char server_response[256];
    recv(network_socket, server_response, sizeof(server_response), 0);

    // print out the server's server_response
    printf("The server sent out: %s\n", server_response);

    close(network_socket);
}
