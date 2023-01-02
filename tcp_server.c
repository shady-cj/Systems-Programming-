#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>

int main ()
{
	char server_msg[256] = "You have reached the server";
	int server_socket;
	server_socket = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(9000);
	server_addr.sin_addr.s_addr = INADDR_ANY;

	// Bind the socket to our specified ip and port
	
	bind(server_socket, (struct sockaddr *) &server_addr,
			sizeof(server_addr));
	listen(server_socket, 5);

	int client_socket;
	client_socket = accept(server_socket, NULL, NULL);

	//send message
	send(client_socket, server_msg, sizeof(server_msg), 0);
	close(server_socket);
	return (0);
}
