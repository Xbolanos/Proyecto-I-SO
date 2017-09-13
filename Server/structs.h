#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdio.h>
#include <string.h>

 const char * delim=" \n.";
 struct sockaddr_in c_addr;


 char * pch;
 int indexProcess = 0; 
 


typedef struct
{
	int id;
	char file[100];
	int connfd; 
	int browser; 
    //struct sockaddr_in c_addr;
} Process;
#define MAX 50
Process *process[MAX];
int rear = - 1;
int front = - 1;
void insert(Process p)
{
    
    if (rear == MAX - 1)
    printf("Queue Overflow \n");
    else
    {
        if (front == - 1)
        /*If queue is initially empty */
        front = 0;
        
        rear = rear + 1;
        process[rear] = &p;
    }
} /*End of insert()*/
 
void delete()
{
    if (front == - 1 || front > rear)
    {
        printf("Queue Underflow in delete \n");
        return ;
    }
    else
    {
        printf("Element deleted from queue is : %d\n", process[front]);
        front = front + 1;
    }
} /*End of delete() */
#endif