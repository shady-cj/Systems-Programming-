#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main ()
{
	// Create a socket
	int network_socket;
	network_socket = socket(AF_INET, SOCK_STREAM, 0);

	// specify an address for the socket
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9000);
	server_address.sin_addr.s_addr = INADDR_ANY;

	int connect_status;
	connect_status = connect(network_socket,
			(struct sockaddr *) &server_address,
			sizeof(server_address));
	if (connect_status == -1)
	{
		perror("Error in making connection");
	}
	
	// send server message
	char server_msg[256] = "HELLO FROM C CLIENT";
	send(network_socket, server_msg, sizeof(server_msg), 0);
	// recieve data from the server
	char server_response[256];
	recv(network_socket, &server_response, sizeof(server_response), 0);
	// print out server's response
	printf("The server sent the data: %s", server_response);

	close(network_socket);
	return (0);
}
