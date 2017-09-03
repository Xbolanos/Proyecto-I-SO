#include <stdio.h>

#include <pthread.h>

typedef struct parameter_t{

	int attr1;
	int attr2;
}parameter_t;

void* thread_func(void* parameter)
{
    int i =0;
    parameter_t *p=(parameter_t*)parameter;
    for(i=0;i<3;i++){
    	printf("%d attr1 %d attr2 %d\n", i, p->attr1, p->attr2);
    	sleep(1);
    }
    return 0;
}
 
int main(int argc, char **argv)
{

	pthread_t thread_handle;
	parameter_t my_parameter={1.2};
	int ret = pthread_create(&thread_handle,0,thread_func,(void*)&my_parameter);
	if (ret != 0){
		printf("Create thread failed! error: %d\n", ret);
		return 1;
	}
	pthread_join(thread_handle, 0);
    return 0;
}
