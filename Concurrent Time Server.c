Concurrent Time Server
Exp No 8*/

server.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <time.h>
#include <string.h>
void main() {
    int server_fd, code;
    struct sockaddr_in serv_addr, cli_addr;
    
    if((server_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
   	 printf("Socket creation failed\n");
   	 exit(1);
    }
    else
    {
    	printf("Socket Created\n");
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(5000);
    
    if(bind(server_fd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0)
    {
   	 printf("Binding failed\n");
   	 exit(1);
    }
    else
    {
    	printf("Binding Success\n");
    }
    int len = sizeof(cli_addr),i=0;
    if(recvfrom(server_fd, &code, sizeof(int), 0, (struct sockaddr*) &cli_addr, &len) < 0)
   		 {
   			 printf("Receive failed\n");
   		 	exit(1);
   	 	}
   	 	else
   	 	{
	   		 printf("Received request for time.\n");
	   		
	   		 time_t now = time(0);
	   		 char* str = ctime(&now);
	   		
	   		 if(sendto(server_fd, str, (strlen(str) + 1) * sizeof(char), 0, (struct sockaddr*) &cli_addr, len) < 0)
	   		 {
	   			 printf("Sending failed\n");
	   			 exit(1);
	   		 }
	   		 else
	   		 {
	   			 printf("Time sent successfully\n");
		    		i++;
	   		 }
	   		
	   		 return;
   		 }
   close(server_fd);
   	
}

client.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
void main() {
    struct sockaddr_in serv_addr;
    int client_fd, len = sizeof(serv_addr),buffer = 101,i=0;
    char time[30];
   
    if((client_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
	   	 printf("Socket creation failed\n");
	   	 exit(1);
	}
	 else
	 {
	 	printf("Socket Created\n");
	}
	serv_addr.sin_family = AF_INET;
   	 serv_addr.sin_addr.s_addr = INADDR_ANY;
   	 serv_addr.sin_port = htons(5000);
   	
   	 if(sendto(client_fd, &buffer, sizeof(int), 0, (struct sockaddr*) &serv_addr, len) < 0)
   	 {
   		 printf("Sending failed\n");
   		 exit(1);
   	 }
   	 else {
   		 if(recvfrom(client_fd, time, 30 * sizeof(char), 0, (struct sockaddr*) &serv_addr, &len) < 0)
   		 {
   				 printf("Receive failed\n");
   			 	exit(1);
   		 } else
   		 {
   			 printf("Received time from Time Server : %s", time);
            		i++;
   		}
   	 }
   
    close(client_fd);
}
