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
   	char *endptr;
   	int value1 = strtol(argv[1], &endptr, 10);
   
	
	  
    if(argc>=3){ 	
    	if (*endptr == '\0'){
	        int value2= strtol(argv[2], &endptr, 1);
	        if (*endptr == '\0'){
	   			//
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
		    			if(argc>=4){
		    				int value3= strtol(argv[3], &endptr, 10);
		    				if (*endptr == '\0'){
				    			printf("Sería P-Thread\n");
    			                pthreadImplementation(argc, argv);
    			            }else{
    			            	printf("**ERROR:Debe ingresar un número para la cantidad de hilos**\n");
    			            }
			             }else{
			             	printf("**ERROR:No ingreso la cantidad de hilos.**\n");
			             }
		    			break;
		    		default:
		    			printf("Sería Fifo\n");
		                fifoImplementation(argc, argv); 
	           }}else{
	           	 	printf("**ERROR:El puerto debe de ser un número de 4 dígitos.**\n");
	           }
	   
    	}else{
    		printf("**ERROR:Debe tomar en cuenta que los tipos son números.**\n");
    	}
    				


    }else{
    	
    	printf("*Para la ejecución del programa, se debe de utilizar el siguiente formato a la hora de su ejecución: \n");
    	printf("         ./server #tipo #puerto #threads(únicamente con PThreads)\n");
    	printf("*Número de tipos:\n");
    	printf("	-FIFO:0\n");
    	printf("	-FORK:1\n");
    	printf("	-THREAD:2\n");
    	printf("	-PTHREAD:3\n");
    	printf("**Tome en cuenta que por default va a estar el FIFO.**\n");
    } 
    return 0;
}


    
    
    
     
    
    
