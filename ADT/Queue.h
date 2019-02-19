//status
#ifndef _QUEUE_H
#define _QUEUE_H

#include<stdio.h>
#include"Status.h"
#include<stdbool.h>
#include"ElementType.h"



typedef struct Qnode{
    ElementType data;
    struct Qnode* next;
}* PQnode;

typedef struct{
    PQnode first;
    PQnode last;
    type t;
}Queue;

Status InitiateQueue(Queue* queue,type t);

Status PrintEelement(ElementType);
Status PrintQueue(Queue queue,char info[]);
Status EnQueue(Queue* queue,ElementType e);
Status DeQueue(Queue* queue,ElementType* e);
bool IsEmptyQ(Queue queue);
Status DestroyQueue(Queue* queue);
int QueueLength(Queue queue);
#endif