#include "Queue.h"
#include <malloc.h>
#include <stdio.h>
#include <stdbool.h>

Status InitiateQueue(Queue *queue, type t)
{
    // // queue = (Queue*)malloc(sizeof(Queue));
    // // if (!queue)
    // //     EXIT("Initiate Error", OVERFLOW);
    // queue->first = (PQnode)malloc(sizeof(struct Qnode));
    // if (!queue->first)
    //     EXIT(OVERFLOW, "Initiate Error");
    // InitiateElement(&queue->first->data,t);
    // queue->first->next = NULL; //head node
    // queue->last = queue->first;
    // return OK;
    queue->first = queue->last = NULL;
    queue->t = t;
}
Status PrintQueue(Queue queue, char info[])
{
    printf("%s:\n", info);
    PQnode p = queue.first;
    while (p)
    {
        printf("\t");
        PrintElement(p->data);
        printf("\n");
        p = p->next;
    }
    printf("\n");
    return OK;
}
Status EnQueue(Queue *queue, ElementType e) //add in tail
{
    if (e.t != queue->t)
        EXIT(ERROR, "different type when EnQueue");
    PQnode p = (PQnode)malloc(sizeof(struct Qnode));
    if (!p)
        EXIT(OVERFLOW, "No Space when EnQueue");
    InitiateElement(&p->data, e.t);
    CopyElement(p->data, e);
    p->next = NULL;
    if (!queue->last) //empty queue
    {
        queue->first = queue->last = p;
    }
    else
    {
        queue->last->next = p;
        queue->last = queue->last->next;
    }
    return OK;
}
bool IsEmptyQ(Queue queue)
{
    return queue.first==NULL;
}
Status DeQueue(Queue *queue, ElementType *e) //out in first
{
    if (e->t != queue->t)
        EXIT(ERROR, "different type when pushss");
    if (!IsEmptyQ(*queue))
    {
        PQnode p = queue->first;
        if (queue->first == queue->last) //only one element
        {
            queue->first=queue->last= NULL;
        }
        else
        {
            queue->first = p->next;
        }
        CopyElement(*e, p->data);
        DestroyElement(&p->data);
        free(p);
    }
    else
    {
        EXIT(OVERFLOW, "Queue is empty when DeQueue");
    }
    return OK;
}
Status DestroyQueue(Queue *queue)
{
    PQnode p = queue->first; //pre
    PQnode q = p->next;
    while (q)
    {
        DestroyElement(&p->data);
        free(p);
        p = q;
        q = q->next;
    }
    queue->first = NULL;
    queue->last = NULL;
    queue->t = Tnone;
    return OK;
}