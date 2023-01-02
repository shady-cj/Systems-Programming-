#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>


int main(int argc, char *argv[])
{

	char *address;
	address = argv[1];

	int client_socket;
	client_socket = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(80);
	inet_aton(address, &server_addr.sin_addr.s_addr);
	connect(client_socket, (struct sockaddr *) &server_addr,
			sizeof(server_addr));

	char request[] = "GET / HTTP/1.1\r\n\r\n";
	char response[4096];

	send(client_socket, request, sizeof(request), 0);
	recv(client_socket, &response, sizeof(response), 0);

	printf("response from the server: \n %s \n", response);
	close(client_socket);
}
