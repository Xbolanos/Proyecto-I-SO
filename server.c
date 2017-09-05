#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void error(char *msg)
{
	perror(msg);
	exit(1);
}
int main(int argc, char *argv[])
{
	int sockfd, newsockfd, portno, clilen;
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;
	int n; 
	if (argc < 2)
	{
		fprintf(stderr, "ERROR, no port provided\n");
		exit(1);
	}

	sockfd= socket(AF_INET, SOCK_STREAM,0);

	if (sockfd < 0)
	{
		error("ERROR opening socket");
	}

	bzero((char *) &serv_addr, sizeof(serv_addr));

	portno= atoi(argv[1]);

	serv_addr.sin_family= AF_INET;
	serv_addr.sin_addr.s_addr= INADDR_ANY;
	serv_addr.sin_port= htons(portno);

	if(bind(sockfd,(struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
	{

		error("ERROR on binding");

	}

	listen(sockfd, 5);
	clilen= sizeof(cli_addr);

	while(1){
		newsockfd= accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

		if( newsockfd < 0)
		{
			error("ERROR on accept");
		}

		bzero(buffer, 256);
		n= read(newsockfd, buffer, 255);

		if( n < 0 )
		{
			error("ERROR reading from socket");
		}

		printf("Here is the message: %s\n", buffer);
		char str[] = "";
		strcpy(str, buffer); 
		const char *a[100];
		char * pch;
		pch = strtok (str," ");
		  int i = 0; 
		  while (pch != NULL)
		  {
		    a[i] = pch; 
		    i++; 
		    pch = strtok (NULL, " ");
		  }
		printf("si pasa el get\n");
		printf("%s\n", a[1]); // aqui ya toma del http del browser que quiere despues del puerto
	
		n= write(newsockfd, "I got your message",18);

		if (n < 0)
		{
			error("ERROR writing to socket");
		}
	}

	return 0;
}
