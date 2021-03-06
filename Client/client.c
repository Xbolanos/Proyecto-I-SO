#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

void gotoxy(int x,int y)
 {
 printf("%c[%d;%df",0x1B,y,x);
 }


void connection(char *argv[], char * fileName) {
    system("clear");
    int n =0;
    int sockfd = 0;
    int bytesReceived = 0;
    char recvBuff[1024];
    char buffer[256]; 
    char * pch; 
    memset(recvBuff, '0', sizeof(recvBuff));
    struct sockaddr_in serv_addr;

    /* Create a socket first */
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0))< 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    }

    /* Initialize sockaddr_in data structure */
    serv_addr.sin_family = AF_INET;
    int port = atoi(argv[2]); 
    serv_addr.sin_port = htons(port); // port
    char ip[50];

    strcpy(ip,argv[1]);

    serv_addr.sin_addr.s_addr = inet_addr(ip);

    /* Attempt a connection */
    if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0)
    {
        printf("Error : Connect Failed \n");
    }

    printf("Connected to ip: %s : %d\n",inet_ntoa(serv_addr.sin_addr),ntohs(serv_addr.sin_port));
    /*sending name*/
    bzero(buffer,256);
    pch = strdup(fileName); 
    strcpy(buffer,pch); 
    n= write(sockfd,buffer,strlen(buffer)); //1 
    if( n < 0 )
    {
        error("ERROR, writing to socket");
    }
    bzero(buffer,256);

    /*end of sending name*/

     /* Create file where data will be stored */
    FILE *fp;
    char fname[256];
    read(sockfd, fname, 256); //2
     
    //strcat(fname,"AK");
    printf("File Name: %s\n",fname);
    printf("Receiving file...\n");
     fp = fopen(fname, "ab"); 
        if(NULL == fp)
        {
         printf("Error opening file");
         return 1;
        }
    long double sz=1;
    /* Receive data in chunks of 256 bytes */
    while((bytesReceived = n= recv(sockfd,recvBuff,1024,0)) > 0) //3 
    { 
        //printf("### lo que recibe: %s\n", recvBuff);
        sz++;
        gotoxy(0,4);
        printf("Received: %llf Mb",(sz/1024));
    fflush(stdout);
        // recvBuff[n] = 0;
        fwrite(recvBuff, 1,bytesReceived,fp);
        // printf("%s \n", recvBuff);
    }

    if(bytesReceived < 0)
    {
        printf("\n Read Error \n");
    }
    printf("\nFile OK....Completed\n");
    return 0;
}

void connectForFiles(int argc, char * argv[]){
    char buffer[256]; 
    bzero(buffer, 256); 
    char *token, *string, *tofree;
    int i = 3; 
    strcat(buffer, argv[3]); //todo esto hasta donde indique es para agarrar todo lo de la linea de comando 
    i++;
    while (argc > i){
        strcat(buffer, " "); 
        strcat(buffer, argv[i]); 
        i++; 
    }
    //string = strdup(argv[3]);
    string = buffer; 
    tofree = string;
    while ((token = strsep(&string, ",")) != NULL)
      {
        connection(argv, token);
        printf("connectionForFiles\n");
      } 
}

int main(int argc, char *argv[])
{
    
    if (argc < 3) 
    {
        printf("*Para la ejecución del programa se debe ingresar:\n");
        printf("  	-Como segundo parámetro ingresar el número de IP \n");
        printf("	-Como tercer parámetro el número de puerto. \n");
        printf("	-Como cuarto parámetro el nombre de los archivos. (si desea varios archivos, debe separarlos por coma.)\n");
        printf("*Ejemplo:\n");
        printf("	./client 127.0.0.1 5000 minion.jpg \n");
    }else{
    	char *endptr;
   		int value1 = strtol(argv[2], &endptr, 10);
   
	
    	if(*endptr == '\0'){
    		connectForFiles(argc, argv); 
    	}else{
    		printf("**ERROR: El puerto debe de ser un número de 4 dígitos**\n");
    	}
    }     
    return 0;
}
