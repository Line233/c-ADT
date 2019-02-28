#include "Queue.h"
#include <stdio.h>
#include "ElementType.h"
#include "Status.h"

void FullQueue(StaticQueue *queue, int *xs, int n)
{
    ElementType e;
    InitiateElement(&e, Tint);
    for (int i = 0; i < n; i++)
    {
        SetValue(e, &(xs[i]));
        EnStaticQueue(queue, e);
    }
    DestroyElement(&e);
}
bool checksq(StaticQueue *queue, int *xs, int n)
{
    ElementType e;
    InitiateElement(&e, Tint);
    int x;
    bool right = true;
    for (int i = 0; i < n; i++)
    {
        DeStaticQueue(queue, &e);
        GetValue(e, &x);
        if (x != xs[i])
            right == false;
    }
    DestroyElement(&e);
    return right;
}
#define squeuesize 10000000
int main()
{
    while (true)
    {
        StaticQueue queue;
        InitiateStaticQueue(&queue, Tint, squeuesize);
        int *xs = GetIntArray(squeuesize, 0, squeuesize);
        FullQueue(&queue, xs, squeuesize);
        bool right = checksq(&queue, xs, squeuesize);
        printf("queue is %s\n",right?"correct":"error");

        free(xs);
        DestroyStaticQueue(&queue);
    }
}