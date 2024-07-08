Array Manipulation using Socket Programming
Exp No 4*/

TCP
server.c

#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
int main()
{
	int n;
	int sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd<0)
	{
		printf("Socket not created\n");
		return(0);
	}
	printf("Socket created\n");
	struct sockaddr_in server,clientaddr;
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	server.sin_port=htons(5000);

	int bind_status=bind(sockfd, (struct sockaddr *)&server,sizeof(server));
	if(bind_status==0)
	{
		printf("Bind successful\n");
	}
	else
	{
		printf("Bind Unsuccessful\n");
	}
	
	listen(sockfd,1);
	printf("waiting for connections\n");
	
	int c=sizeof(clientaddr);
	int clientsock=accept(sockfd,(struct sockaddr *)&clientaddr,(socklen_t *)&c);
	
	if(clientsock<0)
	{
		printf("Connection not estabilshed\n");
	}
	else
	{
		printf("Connection established\n");
	}
	
	if(recv(clientsock,&n,sizeof(int),0)<0)
	{
		printf("Array count not received\n");
		
	}
	else
	{
		printf("Array count received\n");
	}
	
	int arr[n];
	
	if(recv(clientsock,&arr,n*sizeof(int),0)<0)
	{
		printf("Array not received\n");
		
	}
	else
	{
		printf("Array received\n");
	}
	
	int max=arr[0],min=arr[0],sum=0;
	float avg;
	for(int i=1;i<n;i++)
	{
		if(arr[i]<min)
		{
			min=arr[i];
		}
		if(arr[i]>max)
		{
			max=arr[i];
		}
		sum=sum+arr[i];
	}
	avg=(float)sum/n;
	
	if(send(clientsock,&max,sizeof(int),0)<0)
	{
		printf("Error in sending max value\n");
	}
	else
	{
		printf("Max value send to the client\n");
	}
	if(send(clientsock,&min,sizeof(int),0)<0)
	{
		printf("Error in sending min value\n");
	}
	else
	{
		printf("Min value send to the client\n");
	}
	if(send(clientsock,&avg,sizeof(float),0)<0)
	{
		printf("Error in sending average value\n");
	}
	else
	{
		printf("average value send to the client\n");
	}
	
	close(clientsock);
	close(sockfd);
}

client.c

#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
int main()
{
	int n;
	printf("Enter the no of values\n");
	scanf("%d",&n);
	int arr[n];
	printf("Enter the values\n");
	
	for(int i=0;i<n;i++)
	{
		scanf("%d",&arr[i]);
	}
	int sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd<0)
	{
		printf("Socket not created\n");
		return(0);
	}
	printf("Socket Created\n");
	
	struct sockaddr_in clientaddr;
	
	clientaddr.sin_family=AF_INET;
	clientaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	clientaddr.sin_port=htons(5000);
	
	int status=connect(sockfd,(struct sockaddr *)&clientaddr,sizeof(clientaddr));
	
	if(status==0)
	{
		printf("Connected to the server\n");
	}
	else
	{
		printf("Not connected to the server\n");
	}
	
	if(send(sockfd,&n,sizeof(int),0)<0)
	{
		printf("Error in sending array count\n");
		close(sockfd);
	}
	else
	{
		printf("Array count send to the server\n");
	}
	
	if(send(sockfd,&arr,n*sizeof(int),0)<0)
	{
		printf("Error in sending array values\n");
		close(sockfd);
	}
	else
	{
		printf("Array send to the server\n");
	}
	
	int min ,max;
	float avg;
	if(recv(sockfd,&max,sizeof(int),0)<0)
	{
		printf("Max value not received\n");
		
	}
	else
	{
		printf("Max value = %d\n",max);
	}
	
	if(recv(sockfd,&min,sizeof(int),0)<0)
	{
		printf("Min value not received\n");
		
	}
	else
	{
		printf("Min value = %d\n",min);
	}
	
	if(recv(sockfd,&avg,sizeof(float),0)<0)
	{
		printf("Average value not received\n");
		
	}
	else
	{
		printf("Average value = %0.2f\n",avg);
	}
	close(sockfd);
}

UDP
server.c

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
int main() {
  
   int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        printf("Socket not created\n");
        return 0;
    }
    printf("Socket Created\n");
    struct sockaddr_in serveraddr, clientaddr;

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serveraddr.sin_port = htons(5000);

    clientaddr.sin_family = AF_INET;
    clientaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    clientaddr.sin_port = htons(5001);

    
    int bind_status=bind(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    
    if (bind_status< 0) {
        printf("Bind failed\n");
        close(sockfd);
        return 0;
    }
    else
    {
    	printf("Bind unsuccessful\n");
    }

    printf("Server listening on port 5000...\n");

   int c= sizeof(clientaddr);

    int n;
    if (recvfrom(sockfd, &n, sizeof(int), 0, (struct sockaddr *)&clientaddr,(socklen_t *)&c) < 0)
    {
        printf("Error in receiving array count\n");
        close(sockfd);
        return 0;
    }
    else
    {
        printf("Array count received from client\n");
    }

	int arr[n];
   if (recvfrom(sockfd, &arr, n * sizeof(int), 0, (struct sockaddr *)&clientaddr,(socklen_t *)&c) < 0)
    {
        printf("Error in receiving array values\n");
        close(sockfd);
        return 0;
    }
    else
    {
        printf("Array received from client\n");
    }
    int min = arr[0], max = arr[0], sum = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
        if (arr[i] > max) {
            max = arr[i];
        }
        sum += arr[i];
    }

    float avg = (float)sum / n;

    	if(sendto(sockfd, &max, sizeof(int), 0, (struct sockaddr *)&clientaddr, sizeof(clientaddr))<0)
	{
		printf("Error in sending max value\n");
	}
	else
	{
		printf("Max value send to the client\n");
	}
	if(sendto(sockfd, &min, sizeof(int), 0, (struct sockaddr *)&clientaddr, sizeof(clientaddr))<0)
	{
		printf("Error in sending min value\n");
		
	}
	else
	{
		printf("Min value send to the client\n");
	}
	if(sendto(sockfd, &avg, sizeof(float), 0, (struct sockaddr *)&clientaddr,sizeof(clientaddr))<0)
	{
		printf("Error in sending average value\n");
	}
	else
	{
		printf("average value send to the client\n");
	}
   
    	close(sockfd);
	return 0;
}

client.c

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
int main() {
    int n;
    printf("Enter the no of values\n");
    scanf("%d", &n);
    int arr[n];
    printf("Enter the values\n");

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        printf("Socket not created\n");
        return 0;
    }
    printf("Socket Created\n");

    struct sockaddr_in clientaddr,serveraddr;

    clientaddr.sin_family = AF_INET;
    clientaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
   clientaddr.sin_port = htons(5001);
   
   serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serveraddr.sin_port = htons(5000);

    	if(sendto(sockfd, &n, sizeof(int), 0, (struct sockaddr *)&serveraddr, sizeof(serveraddr))<0)
	{
		printf("Error in sending array count\n");
		close(sockfd);
	}
	else
	{
		printf("Array count send to the server\n");
	}
	
	if(sendto(sockfd, &arr, n * sizeof(int), 0, (struct sockaddr *)&serveraddr ,sizeof(serveraddr))<0)
	{
		printf("Error in sending array values\n");
		close(sockfd);
	}
	else
	{
		printf("Array send to the server\n");
	}
    

	int min, max;
	float avg;
	 int s =sizeof(serveraddr);
	 	if(recvfrom(sockfd,&max,sizeof(int),0,(struct sockaddr *)&serveraddr, (socklen_t *)&s)<0)
	{
		printf("Max value not received\n");
		
	}
	else
	{
		printf("Max value = %d\n",max);
	}
	
	if(recvfrom(sockfd,&min,sizeof(int),0,(struct sockaddr *)&serveraddr, (socklen_t *)&s)<0)
	{
		printf("Min value not received\n");
		
	}
	else
	{
		printf("Min value = %d\n",min);
	}
	
	if(recvfrom(sockfd,&avg,sizeof(float),0,(struct sockaddr *)&serveraddr, (socklen_t *)&s)<0)
	{
		printf("Average value not received\n");
		
	}
	else
	{
		printf("Average value = %0.2f\n",avg);
	}
    
    /*recvfrom(sockfd, &max, sizeof(int), 0, NULL, NULL);
    recvfrom(sockfd, &min, sizeof(int), 0, NULL, NULL);
    recvfrom(sockfd, &avg, sizeof(float), 0, NULL, NULL);

    printf("Received from server:\n");
    printf("Max value: %d\n", max);
    printf("Min value: %d\n", min);
    printf("Average value: %0.2f\n", avg);*/

    close(sockfd);
	return 0;
}
