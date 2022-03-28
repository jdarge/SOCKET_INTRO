#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// $ ping google.com -4
// -> THIS RETURNS THE IPV4 ADDRESS OF A WORKING GOOGLE SERVER
// COMPILE -> ./http_client [FOUND IPV4]

int main(int argc, char* argv[]){

    char* address;
    address = argv[1];

    int client_socket;
    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    // connect to an address
    struct sockaddr_in remote_address;
    remote_address.sin_family = AF_INET;
    remote_address.sin_port = htons(80); // 80?
    inet_aton(address, (struct in_addr *) &remote_address.sin_addr.s_addr);

    int client_status = connect(client_socket, (struct sockaddr *) &remote_address, sizeof(remote_address));

    char request[] = "GET / HTTP/1.1\r\n\r\n";
    char response[4096];

    send(client_socket, request, sizeof(request), 0);
    recv(client_socket, &response, sizeof(response), 0);

    printf("Response from the server: %s\n", response);

    close(client_socket);
}
