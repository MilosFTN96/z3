#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

int main()
{
	int sockfd, newsockfd, portno, clilen;
	char buffer[256];
	char *token1;
	char *token2;
	char *token3;
	double rezultat;
	struct sockaddr_in serv_addr, cli_addr;
	double  n;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
		perror("ERROR opening socket");
		exit(1);
	}
	bzero((char *) &serv_addr, sizeof(serv_addr));
	portno = 5001;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
	{
		perror("ERROR on binding");
		exit(1);
	}
	printf("Server started.. waiting for clients ...\n");
	listen(sockfd,5);
	clilen = sizeof(cli_addr);
	while (1)
	{
		newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr, &clilen);
		printf("Client connected...\n");
		if (newsockfd < 0)
		{
			perror("ERROR on accept");
			exit(1);
		}
		int  pid = fork();
		if (pid < 0)
		{
			perror("ERROR on fork");
			exit(1);
		}

		if (pid == 0)
		{
	     		bzero(buffer,256);
	     		n = read(newsockfd,buffer,255);
			if (n < 0)
				printf("Error reading from port");

	     		token1 = strtok(buffer," ");
	     		token2 = strtok(NULL," ");
	     		token3 = strtok(NULL," ");
	     		if (strcmp(token2,"+") == 0)
			{
	     			rezultat = atof(token1) + atof(token3);
			}
	     		else if (strcmp(token2,"-") == 0)
	     			rezultat = atof(token1) - atof(token3);
	     		else if (strcmp(token2,"/") == 0)
	     			rezultat = atof(token1) / atof(token3);
	     		else if (strcmp(token2,"*") == 0)
	     			rezultat = (atof(token1)) * atof(token3);
	     		else
	     		{
	     			printf("pogresno unesen znak");
	     			return 0;
	     		}	
	     		n = write(newsockfd,&rezultat,sizeof(rezultat));
	     		if (n < 0)
				printf("ERROR writing to socket");
			close(sockfd);
			exit(0);
		}
		else
		{
			close(newsockfd);
		}
	}
}
 
 

