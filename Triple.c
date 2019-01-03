#include "Triple.h"
#include "Status.h"

void PrintTriple(void *k)
{
    Triple *t = (Triple *)k;
    printf("%d %d %d", t->a, t->b, t->c);
};

int CmpTriple(void *a, void *b)
{
    Triple *t1 = (Triple *)a;
    Triple *t2 = (Triple *)b;
    return t1->a - t1->b;
}

void CopyTriple(void *copy, void *a)
{
    Triple *t1 = (Triple *)a;
    Triple *t2 = (Triple *)copy;
    t2->a = t1->a;
    t2->b = t1->b;
    t2->c = t1->c;
}

void InitiateTriple(void *e)
{
    Triple *t = (Triple *)e;
    t->a = t->b = t->c = 0;
}

void DestroyTriple(void* e)
{
    
}