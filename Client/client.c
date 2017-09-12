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

 void sendRequestFNames(int * arg, char *argv[]){
    /* Sends the files that he wants*/
    int sockfd=(int)*arg;
    char buffer[256];
    bzero(buffer,256);
    strcpy(buffer, argv[2]);
    write(sockfd,buffer,strlen(buffer));   
 }


void recieveFile(int * arg, char *argv[]){
    int sockfd=(int)*arg;
    int bytesReceived = 0;
    char recvBuff[1024];
    memset(recvBuff, '0', sizeof(recvBuff));
     /* Create file where data will be stored */
    char fname[256];
    bzero(fname, 256); 
    read(sockfd, fname, 256);
    FILE *fp;
    printf("File Name: %s\n",fname);
    /* -------------------------------------- */
    printf("Receiving file...");
    fp = fopen(fname, "ab"); 
    long double sz=1;
    /* Receive data in chunks of 256 bytes */
    while((bytesReceived =  recv(sockfd,recvBuff,1024,0)) > 0 && strcmp(recvBuff, "Next!!!") &&  strcmp(recvBuff, "Done!!!"))
    { 
        sz++;
        gotoxy(0,4);
        printf("Received: %llf Mb",(sz/1024));
        fflush(stdout);
        fwrite(recvBuff, 1,bytesReceived,fp);
    }
    /* In case that the same client is going to recieve other file*/
    if(!strcmp(recvBuff, "Next!!!")){
        printf("\nFile OK....Completed\n");
        recieveFile(&sockfd, argv);
    }
    printf("\nFile OK....Completed -> END\n");
    return 0;
}

void connectClient(int argc, char *argv[]){
    system("clear");
    int sockfd = 0;
    int err = 0; 
    struct sockaddr_in serv_addr;
    /* Create a socket first */
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0))< 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    }

    /* Initialize sockaddr_in data structure */
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000); // port
    char ip[50];
    if (argc < 3) 
    {
        printf("Enter IP address to connect: ");
        gets(ip);
        printf("Missing IP or files\n");
    }
    else{
      strcpy(ip,argv[1]);

      //strcpy(files,argv[3]); 
    }

    serv_addr.sin_addr.s_addr = inet_addr(ip);

    /* Attempt a connection */
    if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0)
    {
        printf("\n Error : Connect Failed \n");
        return 1;
    }
    printf("Connected to ip: %s : %d\n",inet_ntoa(serv_addr.sin_addr),ntohs(serv_addr.sin_port));
    sendRequestFNames(&sockfd, argv);
    recieveFile(&sockfd, argv);
    
} 

int main(int argc, char *argv[])
{
    connectClient(argc, argv); 
    return 0; 
    
}
