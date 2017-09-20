
void * getRequest(int * arg);
//onnectServerPTr
void pthreadImplementation(int argc, char *argv[]){
    
    struct sockaddr_in serv_addr;
    int listenfd = 0,ret;
    size_t clen=0;
    int numthread=atoi(argv[3]);
    struct threadpool *pool;
    int i = 0;
    static int connfd = 0,err;
   

    if ((pool = threadpool_init(numthread)) == NULL) {
        printf("Error! Failed to create a thread pool struct.\n");
        exit(EXIT_FAILURE);
    }

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(listenfd<0)
    {
      printf("Error in socket creation\n");
      exit(2);
    }

    printf("Socket retrieve success\n");

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    int port = atoi(argv[2]); 
    serv_addr.sin_port = htons(port);

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
        
        clen=sizeof(c_addr);
        printf("Waiting...\n");
        
        connfd = accept(listenfd, (struct sockaddr*)&c_addr,&clen);
      
        
        if(connfd<0)
        {
          printf("Error in accept\n");
          continue; 
        }
         
        if (i % numthread == 0) {
           
            ret = threadpool_add_task(pool,&getRequest,&connfd,1);
            i=0;
        }
        else {
         
            ret = threadpool_add_task(pool,&getRequest,&connfd,0);
            i++;
        }  
       
        sleep(2); 
   }
   threadpool_free(pool,1);
}

