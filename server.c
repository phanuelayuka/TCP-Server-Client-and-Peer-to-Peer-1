 #include<stdio.h>  
 #include<sys/types.h>  
 #include<sys/socket.h>  
 #include<netinet/in.h>  
 #include<stdlib.h>  
 #include<string.h>  

int main(int argc,char *argv[])  
{  

	char array[1024];

	 int sockfd,newsockfd,portno,clilen,k, t = 0, i, check;  
	 char buffer[256];  
	 struct sockaddr_in serv_addr,cli_addr;  
	 int n; 
	 int registered_clients[100];

	strcpy(array," ");
	//constructing socket
	 sockfd=socket(AF_INET,SOCK_STREAM,0);  
	 if(sockfd<0)  
		  perror("error opening socket");  
	else printf("Socket creation..........\n");

	//constructing server address
	bzero((char *)&serv_addr,sizeof(serv_addr)); 
	serv_addr.sin_family=AF_INET;  
	serv_addr.sin_addr.s_addr=INADDR_ANY;
	serv_addr.sin_port=htons(9000); 
 
	//bind socket
 	if(bind(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) <0)  
	    error("error on binding");  
	else printf("Binding the server socket........\nThe server is waiting for connections\n");
		
	k=listen(sockfd,5);  
	 for (;;) 
	{  //infinite loop to continually wait for connections 
		check = 0;
	 	if(k<0) 
	 	{  
		 	error("error on handling the network");  
		 	exit(1);  
		}  

		/*accept connections*/ 
		clilen=sizeof(cli_addr);   
	 	newsockfd=accept(sockfd,(struct sockaddr*)&cli_addr,&clilen); 

		 if(newsockfd<0)  
		 {  
			 error("error on accepting connections");  
		 }  
	    printf("\n");   
 
		bzero(buffer,sizeof(buffer));   
		
		n=read(newsockfd,buffer, 256);  
		printf("A new incoming connecting request from client listening at port:\t%s\n", buffer); 

		if(n<0)  
		{  
		 	error("error reading from socket");  
		}  
		else  
		{  
			printf("Client registration check in progress......\n");
			sscanf(buffer, "%d", &portno);

			/*check is client had registered with the server*/
			for( i = 0; i < t; i++){
				/*if registered print the registered message*/
				if(registered_clients[i] == portno)
				{
					check = -1;
					printf("Client had been registered\n");
					break;
				}
			}

			/*if not registered, register the client and store port no*/
			if(check != -1)
			{
				registered_clients[t] = portno;
				strcat(array,buffer);
				strcat(array, " ");
				t++;
				printf("client registered successfully!\n");
			}
		} 
		
		bzero(buffer,sizeof(buffer));  
		strcpy(buffer, array);
		printf("Client registered are:%s\n", array);
		n=write(newsockfd,buffer,strlen(buffer));  
		if(n<0)  
		{  
		error("error writing socket");  
		}  
  
	}   
	close(newsockfd);   
  
}
