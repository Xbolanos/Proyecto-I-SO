#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "structs.h"
#include "http.h"
#include "fifo.c"

extern const char * delim;
extern struct sockaddr_in c_addr;


extern char * pch;
extern int indexProcess; 
extern Process *process[50];



void * getRequest(int * arg){
    int browser = 0; 
    char buffer[256];
    char * pch;
    char str[] = ""; 
    const char *a[100]; // para separar chonquitos
    int connfd=(int)*arg;
    ///extra ------------------
    printf("Connection accepted and id: %d\n",connfd);
    printf("Connected to Clent: %s:%d\n",inet_ntoa(c_addr.sin_addr),ntohs(c_addr.sin_port));       
    //-----------the real action --------------

    read(connfd, buffer, 256); //1 
    printf("#1 : lo que el read recibe: %s\n", buffer);
    // disminusa
    strcpy(str, buffer); 
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
    
    strcpy(buffer, pch);  
    pch = strtok (buffer,"\n");

    strcpy(buffer, pch); 

    if (browser == 1){
        pch = strtok (buffer,"/");
        strcpy(buffer, pch);  
    }
    printf("here is file normal: %s\n", buffer);
    //digamos que aqui se tienen que hacer los processes
    Process p; 
    p.id = 1; 
    strcpy(p.file, buffer); 
    printf("#p.file %s\n", p.file);
    p.connfd = connfd; 
    p.browser = browser; 
    insert(p); 
    indexProcess++;

}


void * SendFileToClient(Process pr)
{
    Process p=(Process)pr;
    char * pch;
    char buffer[256];   
    char bigbuffer[10000]; 
    const char *b[100]; // para separar chonquitos
    int connfd= p.connfd;

  
   /*----------------------------*/

    if(p.browser== 0){ // le mando esto para que sepa cual es el archivo a crear 
        
        write(connfd, p.file,256); //2
        printf("#2 %s\n", p.file);
    } 
   /*//resumidamente toooodo este bloque es para averiguar la extension, y por ello se redirecciona a los ifs de abajo*/
    else{ 
        struct stat st;
        stat(p.file, &st); //esto viene de una libreria que magicamente me saca el tama;o del archivo 
        int size =0;
        size = st.st_size;
        strcpy(buffer, p.file); 
        pch = strtok (buffer,"."); // esto saca chonquitos
        int i = 0; 
        while (pch != NULL)
        {
            b[i] = pch; 
            i++; 
            pch = strtok (NULL, ".");
        }
        i = i - 1; 
        pch = b[i];
        printf("tipo de archivo #%s#\n", pch);
        printf("la i es: %d\n", i);

        printf("el tama;o es de: %d\n", size);
        bzero(bigbuffer, 10000); 
   
        if (!strcmp(pch, "jpg") || !strcmp(pch, "jpeg")){ // escoje el http response correspondiente
            sprintf(bigbuffer, "%s%d\r\n\r\n", http_image_jpeg, size);
        }
        else if(!strcmp(pch,"png")){
            sprintf(bigbuffer, "%s%d\r\n\r\n", http_image_png, size);
        }
        else if (!strcmp(pch, "gif")){
            sprintf(bigbuffer, "%s%d\r\n\r\n", http_image_gif, size);
        }
        else{
            sprintf(bigbuffer, "%s%d\r\n\r\n", http_text_html, size);  
            printf("entro auqi\n"); 
        }
        
        printf("%s\n", bigbuffer);
        int len = strlen(bigbuffer);
        send(p.connfd, bigbuffer, len, 0);     // le manda el http
       }
        

        /*hasta aqui de verdad le manda el archivo*/
        FILE *fp = fopen(p.file,"rb");
        printf("Nombre:%s\n", p.file);
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
                
                send(p.connfd, buff, nread, 0);
            }
            if (nread < 1024)
            {
                if (feof(fp))
                {
                    printf("End of file\n");
                    printf("File transfer completed for id: %d\n",p.connfd);
                    break;

                }
                if (ferror(fp))
                    printf("Error reading\n");
                    return 0; 
            }
        }
        
        fclose(fp);
        printf("Closing Connection for id: %d\n",p.connfd);
        close(p.connfd);
        shutdown(p.connfd,SHUT_WR);
        printf("end ari socket client\n");   
    
    printf("pasa por aqui?\n");
    
    return 1;  
    
}
void connectServer(int argc, char *argv[]){
	int connfd = 0,err;
    struct sockaddr_in serv_addr;
    int listenfd = 0,ret;
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
        getRequest(&connfd);        
        fifo();
        
        printf("termino\n");
   }
    close(connfd);
}

int main(int argc, char *argv[])
{
   
    if(argv[1]!= NULL){
    	
    	switch (atoi(argv[1])){
    		case 0:
    			printf("Sería Fifo\n");
    			break;
    		case 1:
    			printf("Sería FORK\n");
    			break;
    		case 2:
    			printf("Sería Thread\n");
    			break;
    		case 3:
    			printf("Sería P-Thread\n");
    			break;
    		default:
    			printf("Sería Fifo\n");
    	}
    	connectServer(argc, argv);			


    }else{
    	printf("Instrucciones\n");
    } 
    return 0;
}


    
    
    
     
    
    
