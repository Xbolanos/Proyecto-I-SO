#include "threadpool.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>


#include "http.h"
#include "../functions.c"
#include "structs.h"
#include "fifo.c"
#include "fork.c"
#include "thread.c"
#include "pthread.c"

void * SendFileToClient(Process p);
extern void fifoImplementation(int argc, char *argv[]);
extern void forkImplementation(int argc, char *argv[]);
extern void threadImplementation(int argc, char *argv[]);
extern void pthreadImplentation(int argc, char *argv[]);


int main(int argc, char *argv[])
{
   
    if(argv[1]!= NULL){
    	
    	switch (atoi(argv[1])){
    		case 0:
    			printf("Sería Fifo\n");
                fifoImplementation(argc, argv); 
    			break;
    		case 1:
    			printf("Sería FORK\n");
                forkImplementation(argc, argv);
    			break;
    		case 2:
    			printf("Sería Thread\n");
                threadImplementation(argc, argv);
    			break;
    		case 3:
    			printf("Sería P-Thread\n");
                pthreadImplementation(argc, argv);
    			break;
    		default:
    			printf("Sería Fifo\n");
                fifoImplementation(argc, argv); 
    	}
    				


    }else{
    	printf("Instrucciones\n");
    } 
    return 0;
}


    
    
    
     
    
    
