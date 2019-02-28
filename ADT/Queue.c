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
    return queue.first == NULL;
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
            queue->first = queue->last = NULL;
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
int QueueLength(Queue queue)
{
    PQnode p = queue.first;
    int i;
    for (i = 0; p != NULL; i++, p = p->next)
        ;
    return i;
}

Status InitiateStaticQueue(StaticQueue *queue, type t, int n)
{
    queue->e = MALLOC(sizeof(ElementType), n, "no space when InitiateStaticQueue");
    for (int i = 0; i < n; i++)
        InitiateElement(queue->e + i, t);
    queue->front = 0;
    queue->rear = 0;
    queue->size = n;
    queue->used = 0;
}

Status PrintStaticQueue(StaticQueue queue, char info[])
{
    printf("%s:\n", info);
    int p = queue.front;
    for (int p = queue.front; p != queue.rear;)
    {
        printf("\t");
        PrintElement(queue.e[p]);
        printf("\n");
        if (p + 1 < queue.size)
            p++;
        else
            p = 0;
    }
    printf("\n");
    return OK;
}
Status EnStaticQueue(StaticQueue *queue, ElementType e)
{
    if (!IsFullStaticQueue(*queue))
    {
        CopyElement(queue->e[queue->rear], e);
        if (queue->rear + 1 < queue->size)
            queue->rear++;
        else
            queue->rear = 0;
        queue->used++;
    }
    else
    {
        EXIT(ERROR, "staticqueue is full when EnStaticQueue");
    }
}
Status DeStaticQueue(StaticQueue *queue, ElementType *e)
{
    if (!IsEmptyStaticQueue(*queue))
    {
        CopyElement(*e, queue->e[queue->front]);
        if (queue->front + 1 < queue->size)
            queue->front++;
        else
            queue->front = 0;
        queue->used++;
    }
    else
        EXIT(ERROR, "staticqueue is empty when DeStaticQueue");
}
bool IsEmptyStaticQueue(StaticQueue queue)
{
    return queue.used == 0;
}
Status DestroyStaticQueue(StaticQueue *queue)
{
    for (int i = 0; i < queue->size; i++)
        DestroyElement(queue->e + i);
    free(queue->e);
    queue->e = NULL;
    queue->front = queue->rear = queue->size = queue->used = 0;
}
int StaticQueueLength(StaticQueue queue)
{
    return queue.used;
}
bool IsFullStaticQueue(StaticQueue queue)
{
    return queue.used == queue.size;
}