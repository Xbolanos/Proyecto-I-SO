#include  <stdio.h>
#include  <sys/types.h>
#include "structs.h"

void * SendFileToClient(Process p);
void fifo(){
	pid_t  pid;
    
    pid = fork();
	if(process[0]!=NULL){
		printf("Entro a FIFO\n");
		Process p = *process[0]; 
		printf("PID:%d\n", pid);
		printf("#fifo p.file %s\n", p.file);
		printf("#browser pbrowser %d\n", p.browser);
		SendFileToClient(*process[0]);

		
		delete();
		printf("%d\n", sizeof(process));
		
		printf("Sale de FIFO\n");
		
	}
}
