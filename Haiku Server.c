Haiku Server
Exp No 9*/

server.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
void main() {
	int sock_fd, conn_fd, len;
	char haiku[100] = "Delightful display\nSnowdrops bow their pure white heads\nTo the sun's glory.\n";
	struct sockaddr_in servaddr, client;
    	sock_fd=socket(AF_INET, SOCK_STREAM, 0);
	if (sock_fd< 0)
	{
    	printf("Socket creation failed");
    	exit(1);
	}
	printf("Socket successfully created.\n");
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htons(INADDR_ANY);
	servaddr.sin_port = htons(5575);
	if (bind(sock_fd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
	{
	    	printf("Socket bind failed");
	    	exit(1);
	}
	printf("Socket successfully binded.\n");

	if (listen(sock_fd, 5) < 0)
	{
	    	printf("Listen failed");
	    	exit(1);
	}
	printf("Server listening...\n");

	len = sizeof(client);
	conn_fd = accept(sock_fd, (struct sockaddr*)&client, &len);
	if (conn_fd < 0)
	{
	    	printf("Server accept failed");
	    	exit(1);
	}
	printf("Accepted successfully\n");
	if (send(conn_fd, haiku, strlen(haiku), 0) < 0)
	{
	    	printf("Failed to send haiku.\n");
	    	exit(1);
	}
	else
	{
		printf("Haiku sent successfully\n");
	}
	close(sock_fd);
}

client.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
void main() {
	int sock_fd;
	struct sockaddr_in servaddr;
	char b[100];

	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_fd < 0) {
	    	printf("Socket creation failed");
	    	exit(1);
	}
	printf("Socket created.\n");
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(5575);
	
	if (connect(sock_fd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
	{
	    	printf("Connection to server failed");
	    	exit(1);
	}
	printf("Connected to the server.\n");
	
	if (recv(sock_fd, b, sizeof(b), 0) < 0) {
	    	printf("Receiving failed");
	    	exit(1);
	}
	printf("Haiku Received: %s\n", b);

	close(sock_fd);
}
