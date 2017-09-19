#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdio.h>
#include <string.h>

 const char * delim=" \n.";
 struct sockaddr_in c_addr;


 char * pch;
 int indexProcess = 0; 
 char * split_string(char * str, char *delimiter, int index);


typedef struct
{
	int id;
	char file[100];
	int connfd; 
	int browser; 
    //struct sockaddr_in c_addr;
} Process;

void * SendFileToClient(Process p);

void * getRequest(int * arg){
    int browser = 0; 
    char buffer[256];
    char * pch;
    char str[] = ""; 
    const char *a[100]; // para separar chonquitos
    int connfd=(int)*arg;
       
    //-----------the real action --------------
    bzero(buffer,256); 
    read(connfd, buffer, 256); //1     printf("#1 : lo que el read recibe: #%s#\n", buffer);
    // disminusa
    if (!strcmp(split_string(buffer, " ", 0), "GET")){
        browser = 1; 
        pch = split_string(buffer, " ", 1); 
        bzero(buffer,256);
        strcpy(buffer, pch);  
        pch = strdup(makeSpaceHTTP(buffer, "%20")); 
        bzero(buffer,256);
        strcat(buffer, ".");
        strcat(buffer, pch);  
        pch = buffer; 
        printf("PCHHHHHHHHHHHHHH: %s\n", buffer); 
    }
    else{
       printf("entra al else de los splits y el valor es #%s#\n", buffer);
       pch = split_string(buffer,"\n",0); 
       bzero(buffer,256);
       strcat(buffer, "./");
       strcat(buffer, pch);
       pch = buffer; 
    }
    strcpy(buffer, pch); 
    printf("File Name: %s\n", buffer);
    //verificar si vale la pena meterlo
    FILE * file;
    file = fopen(buffer, "r");
    printf("meme\n");
    if (!file){
        printf("no hay archivo D:\n");
        printf("Closing Connection for id: %d\n",connfd);
        if(browser == 1){
            printf("booii\n");
           int len = strlen(http_error);
           send(connfd, http_error, len, 0); 
        }
    close(connfd); 
    shutdown(connfd,SHUT_WR);
        
       return; 
    }
    //digamos que aqui se tienen que hacer los processes
    Process p; 
    p.id = 1; 
    strcpy(p.file, buffer); 
    p.connfd = connfd;
    p.browser = browser;  
    SendFileToClient(p); 

}


void * SendFileToClient(Process pr)
{
    Process p=(Process)pr;
    char * pch;
    char buffer[256];   
    char bigbuffer[10000]; 
    int connfd= p.connfd;
    int n = 0; //este n lo uso para saber si salio bien el send write 

  
   /*----------------------------*/

    if(p.browser== 0){ // le mando esto para que sepa cual es el archivo a crear 
        char * name = split_string(p.file, "/", -1); 
        n = write(connfd, name,256); //2
        if (n <= 0){
            printf("Error: en enviar el nombre al socket\n");
            return 0; 
        }
    } 
   //resumidamente toooodo este bloque es para averiguar la extension, y por ello se redirecciona a los ifs de abajo
    else{ 
        struct stat st;
        stat(p.file, &st); //esto viene de una libreria que magicamente me saca el tama;o del archivo 
        int size =0;
        size = st.st_size;
        strcpy(buffer, p.file); 
        pch = split_string(buffer,".",-1); 

        
        printf("Tipo de archivo #%s#\n", pch);
        printf("Tamanno: %d\n", size);
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
        int len = strlen(bigbuffer);
        send(p.connfd, bigbuffer, len, 0);     // le manda el http
   }

    /*hasta aqui de verdad le manda el archivo*/
    FILE *fp = fopen(p.file,"rb");
    if(fp==NULL)
    {
        printf("File opern error");
        return 0 ;   
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
            n = send(p.connfd, buff, nread, MSG_NOSIGNAL); //3
            if (n <= 0){
                printf("Warning: Connection for id: %d closed before spected\n", connfd);
                printf("Waiting\n");
                return 0; 
            }
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
        sleep(1);
    }
    
    fclose(fp);
    printf("Closing Connection for id: %d\n",p.connfd);
    close(p.connfd);
    shutdown(p.connfd,SHUT_WR);
    return 1;  
    
}
#endif