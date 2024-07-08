Multi Client Chat Server using TCP
Exp No 6*/
server.c

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
void main(){
char *ip = "127.0.0.1";
max_words=25;
char buffer[1024];
int n,word_count=0;
ssize_t recv_size;
struct sockaddr_in server_addr, client_addr;
server_addr.sin_family = AF_INET;
server_addr.sin_addr.s_addr = inet_addr(ip);
server_addr.sin_port = htons(5000);

int server_sock = socket(AF_INET,SOCK_STREAM,0);
if(server_sock<0) {
printf("socket creation failed\n”);
exit(1);
}
printf("socket created \n");
if((n = bind(server_sock,(struct sockaddr*)&server_addr,sizeof(server_addr)))<0) {printf("Binding failed\n");
exit(1);
}
printf(" Binding successful\n");

if((listen(server_sock,5))<0) {
printf("listening failed\n");
exit(1);
}
printf("Listening....\n");
fflush(stdout);

int client_sock;
socklen_t clientaddr_len = sizeof(client_addr);
client_sock = accept(server_sock,(struct sockaddr*)&client_addr,&clientaddr_len);
if(client_sock<0) {
printf("Accept failed");
exit(1);
}
printf("Connection accepted\n");
while (1) {
recv_size = recv(client_sock, buffer, sizeof(buffer), 0);
if (recv_size > 0) {
buffer[recv_size] = '\0';
printf("Message recived: %s\n", buffer);
if (strcmp(buffer, "start") == 0) {
send(client_sock, "Welcome! You can start sending messages.\n", strlen(" Welcome! You
can start sending messages.\n"), 0);} else if (strcmp(buffer, "stop") == 0) {
printf("closing connection.\n");
break;
} else {
if (word_count >= max_words) {
send(client_sock, "Daily word limit exceeded", strlen("Daily word limit exceeded\n"), 0);
} else {
word_count++;
send(client_sock, "Message received", strlen("Message received"), 0);
}
}
} else if (recv_size == 0) {
printf("Client disconnected\n");
break;
} else {
perror("Receive error");
break;
}
}
close(client_sock);
close(server_sock);
}

client.c

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
void main(){
char *ip = "127.0.0.1";
char message[1024];
int n;
struct sockaddr_in server_addr;
server_addr.sin_family = AF_INET;
server_addr.sin_addr.s_addr = inet_addr(ip);
server_addr.sin_port = htons(5000);
//sock creation
int client_sock = socket(AF_INET, SOCK_STREAM, 0);
if(client_sock < 0) {
printf("socket creation failed");
exit(1);
}
printf(“ socket created\n");
if(connect(client_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
printf("Connection failed");
exit(1);
}
printf("Connected to server\n");
while(1) {
printf("Enter message: ");fgets(message, sizeof(message), stdin);
message[strcspn(message, "\n")] = 0;

if(send(client_sock, message, strlen(message), 0) < 0) {
perror("Send failed");
break;
}

if(strcmp(message, "stop") == 0) {
printf("Stopped\n");
break;
}

char ack[1024];
if(recv(client_sock, ack, sizeof(ack), 0) < 0) {
printf("Receive failed\n");
break;
}
printf("%s\n", ack);
}
close(client_sock);
}
