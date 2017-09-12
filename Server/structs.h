#include <stdio.h>
#include <string.h>

struct Process
{
	int id;
	char file[100];
    struct sockaddr_in c_addr;
};
