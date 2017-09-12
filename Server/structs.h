#include <stdio.h>
#include <string.h>

struct Process
{
	int id;
	char file[100];
	int connfd; 
	int browser; 
    //struct sockaddr_in c_addr;
};
