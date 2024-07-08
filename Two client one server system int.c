Exp No Two client one server system
5.2
*/
server.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
int square(int num) {
	return num * num;
}
void main() {
	int server_fd, client_fd1, client_fd2;
	struct sockaddr_in address, cli_addr;
	int opt, addrlen = sizeof(address);
	int num;
	printf("Enter 1 for TCP\n");
	printf("Enter 2 for UDP\n");
	scanf("%d", &opt);
	if(opt == 1)
		printf("TCP Server\n");
	else if(opt == 2)
		printf("UDP Server\n");
	else {
		printf("Invalid input!\n");
		exit(1);
	}
	if(opt == 1)
	{
		server_fd = socket(AF_INET, SOCK_STREAM, 0);
		if(server_fd < 0) {
			printf("Socket not created\n");
			exit(1);
		}
		printf("Client socket created.\n");
	}
	else
	{
		server_fd = socket(AF_INET, SOCK_DGRAM, 0);
		if(server_fd < 0)
		{
			printf("Socket not created\n");
			exit(1);
		}
		printf("Client socket created.\n");
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(5000);
	if(bind(server_fd, (struct sockaddr*) &address, addrlen) < 0)
	{
		printf("Socket binding failed\n");
		exit(1);
	}
	printf("Socket binded\n");
	if(opt == 1) {
		if(listen(server_fd, 5) < 0)
		{
			printf("Listening failed\n");
			exit(1);
		}
		printf("Server listening\n");
		
		if((client_fd1 = accept(server_fd, (struct sockaddr*) &address, (socklen_t*) &addrlen)) < 0)
		{
			printf("Connection failed\n");
			exit(1);
		}
		printf("Connected to client 1\n");
	f((client_fd2 = accept(server_fd, (struct sockaddr*) &address, (socklen_t*) &addrlen)) < 0)
		{
			printf("Connection failed\n");
			exit(1);
		}
		printf("Connected to client 2\n");
		if(recv(client_fd1, &num, sizeof(int), 0) < 0) {
			printf("Receive failed\n");
			exit(1);
		} else {
			printf("Received integer from client 1: %d\n", num);
		}
		int result = square(num);
		if(send(client_fd2, &result, sizeof(int), 0) < 0) {
			printf("Send failed\n");
			exit(1);
		} else {
			printf("Squared integer sent to client 2.\n");
		}
	}
	else {
		int len = sizeof(address);
		int len1 = sizeof(cli_addr);
		
		cli_addr.sin_port = htons(5001);
		
		if(recvfrom(server_fd, &num, sizeof(int), 0, (struct sockaddr*) &address, &len) < 0) {
			printf("Receive failed!\n");
			exit(1);
		}
		printf("Received integer from client 1: %d\n", num);
		int result = square(num);
		if(sendto(server_fd, &result, sizeof(int), 0, (struct sockaddr*) &cli_addr, len1) < 0) {
			printf("Send failed!\n");
			exit(1);
		}
		printf("Squared integer sent to client 2.\n");
		
	}
	close(server_fd);
	close(client_fd1);
	close(client_fd2);
}

client1.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
void main() {
	int client_fd;
	struct sockaddr_in serv_addr;
	int num, opt;
	printf("Enter 1 for TCP\n");
	printf("Enter 2 for UDP\n");
	scanf("%d", &opt);
	if(opt == 1)
		printf("TCP Client\n");
	else if(opt == 2)
		printf("UDP Client\n");
	else
	{
		printf("Invalid input!\n");
		exit(1);
	}
	if(opt == 1)
	{
		client_fd = socket(AF_INET, SOCK_STREAM, 0);
		if(client_fd < 0) {
			printf("Socket not created\n");
			exit(1);
		}
		printf("Client socket created.\n");
	}
	else
	{
		client_fd = socket(AF_INET, SOCK_DGRAM, 0);
		if( client_fd < 0)
		{
			printf("Socket not created\n");
			exit(1);
		}
		printf("Client socket created.\n");
	}
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv_addr.sin_port = htons(5000);
	if(opt == 1) {
		int status=connect(client_fd, (struct sockaddr*) &serv_addr, sizeof(serv_addr));
		if( status < 0)
		{
			printf("Connection failed\n");
			exit(1);
		}
		printf("Connection established\n");
	}
	printf("Enter integer: ");
	scanf("%d", &num);
	if(opt == 1) {
		if(send(client_fd, &num, sizeof(int), 0) < 0) {
			printf("Send failed!\n");
			exit(1);
		} else {
			printf("Integer sent\n");
		}
	} else {
		if(sendto(client_fd, &num, sizeof(int), 0, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0) {
			printf("Send failed!\n");
			exit(1);
		} else {
			printf("Integer sent\n");
		}
	}
	
	close(client_fd);
}

client2.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
void main() {
	int client_fd;
	struct sockaddr_in serv_addr,cli_addr;
	int num, opt, len = sizeof(serv_addr);
	
	printf("Enter 1 for TCP\n");
	printf("Enter 2 for UDP\n");
	scanf("%d", &opt);
	
	if(opt == 1)
		printf("TCP Client\n");
	else if(opt == 2)
		printf("UDP Client\n");
	else
	{
		printf("Invalid input!\n");
		exit(1);
	}
	if(opt == 1)
	{
		client_fd = socket(AF_INET, SOCK_STREAM, 0);
		if(client_fd < 0) {
			printf("Socket not created\n");
			exit(1);
		}
		printf("Client socket created.\n");
	}  
	else
	{
		client_fd = socket(AF_INET, SOCK_DGRAM, 0);
		if( client_fd < 0)
		{
			printf("Socket not created\n");
			exit(1);
		}
		printf("Client socket created.\n");
	}
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv_addr.sin_port = htons(5000);
	cli_addr.sin_family = AF_INET;
	cli_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	cli_addr.sin_port = htons(5001);
	if(opt == 1) {
		int status=connect(client_fd, (struct sockaddr*) &serv_addr, sizeof(serv_addr));
		if( status < 0)
		{
			printf("Connection failed\n");
			exit(1);
		}
		printf("Connection established\n");
	}
	if(opt == 1) {
		if(recv(client_fd, &num, sizeof(int), 0) < 0) {
			printf("Receive failed\n");
			exit(1);
		}
			printf("Squared number received: %d\n", num);
		
	}
	else {
		if(bind(client_fd, (struct sockaddr*) &cli_addr, sizeof(cli_addr)) < 0) {
			printf("Socket binding failed\n");
			exit(1);
		}
		printf("Socket binded.\n");
		if(recvfrom(client_fd, &num, sizeof(int), 0, (struct sockaddr*) &serv_addr, &len) < 0) {
			printf("Receive failed!\n");
			exit(1);
		}
		printf("Squared number received: %d\n", num);
		
	}
	close(client_fd);
}
