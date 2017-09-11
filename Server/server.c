#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>


struct sockaddr_in c_addr;
char fname[100];
char buffer[256]; 
int browser = 0; 


void * SendFileToClient(int *arg)
{
      int connfd=(int)*arg;
      printf("Connection accepted and id: %d\n",connfd);
      printf("Connected to Clent: %s:%d\n",inet_ntoa(c_addr.sin_addr),ntohs(c_addr.sin_port));
      read(connfd, buffer, 256);
      char str[] = "";
        strcpy(str, buffer); 
        const char *a[100];
        char * pch;
        pch = strtok (str," ");
        if (!strcmp(pch, "GET")){
            browser = 1; 
            int i = 0; 
              while (pch != NULL)
              {
                a[i] = pch; 
                i++; 
                pch = strtok (NULL, " ");
              }
              pch = a[1];
            //estos print se pueden unificar a futuro
            printf("Here is the file from browser: %s\n", pch); // aqui ya toma del http del browser que quiere despues del puerto  
        }
        strcpy(fname, pch);  
        pch = strtok (fname,"\n");
        strcpy(fname, pch); 
        if (browser == 1){
            pch = strtok (fname,"/");
            strcpy(fname, pch);  
        }
        
        
        write(connfd, fname,256); //2 
       
        FILE *fp = fopen(fname,"rb");
        printf("Nombre:%s\n", fname);
        if(fp==NULL)
        {
            printf("File opern error");
            perror(fp);
            return 1;   
        }   

        /* Read data from file and send it */
        while(1)
        {
            /* First read file in chunks of 256 bytes */
            unsigned char buff[1024]={0};
            int nread = fread(buff,1,1024,fp);
            printf("Bytes read %d \n", nread);        

            /* If read was success, send data. */
            if(nread > 0)
            {
                printf("Sending \n");
                write(connfd, buff, nread);
            }
            if (nread < 1024)
            {
                if (feof(fp))
                {
                    printf("End of file\n");
                    printf("File transfer completed for id: %d\n",connfd);
                    break;

                }
                if (ferror(fp))
                    printf("Error reading\n");
                    return 0; 
            }
        }
    if (browser != 1){
        fclose(fp);
        printf("Closing Connection for id: %d\n",connfd);
        close(connfd);
        shutdown(connfd,SHUT_WR);
        printf("end ari socket client\n");   
    }
    
    return 1;  
    
}


int main(int argc, char *argv[])
{
    int connfd = 0,err;
    pthread_t tid; 
    struct sockaddr_in serv_addr;
    int listenfd = 0,ret;
    char sendBuff[1025];
    int numrv;
    size_t clen=0;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(listenfd<0)
	{
	  printf("Error in socket creation\n");
	  exit(2);
	}

    printf("Socket retrieve success\n");

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5001);

    ret=bind(listenfd, (struct sockaddr*)&serv_addr,sizeof(serv_addr));
    if(ret<0)
    {
      printf("Error in bind\n");
      exit(2);
    }

    if(listen(listenfd, 10) == -1)
    {
        printf("Failed to listen\n");
        return -1;
    }

    while(1)
    {   
        printf("hola volvi\n");
        clen=sizeof(c_addr);
        printf("Waiting...\n");
        connfd = accept(listenfd, (struct sockaddr*)&c_addr,&clen);
        if(connfd<0)
        {
    	  printf("Error in accept\n");
    	  continue;	
    	}
        //err = pthread_create(&tid, NULL, &SendFileToClient, &connfd);
        SendFileToClient(&connfd); 
        
        printf("termino\n");
   }
    close(connfd);
    return 0;
}
