#include  <stdio.h>
#include  <sys/types.h>
#include "structs.h"

void * SendFileToClient(Process p);
void fifo(){
	pid_t  pid;
    
    pid = fork();
	if(process[0]!=NULL){
		printf("Entro a FIFO\n");
		
		printf("PID:%d\n", pid);
		SendFileToClient(*process[0]);
		
		delete();
		printf("%d\n", sizeof(process));
		
		printf("Sale de FIFO\n");
		
	}
}