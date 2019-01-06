#include "Triple.h"
#include "Status.h"

void print_triple(void *k)
{
    Triple *t = (Triple *)k;
    printf("%d %d %d", t->a, t->b, t->c);
};

int cmp_triple(void *a, void *b)
{
    Triple *t1 = (Triple *)a;
    Triple *t2 = (Triple *)b;
    return t1->a - t2->a;
}

void copy_triple(void *copy, void *a)
{
    Triple *t1 = (Triple *)a;
    Triple *t2 = (Triple *)copy;
    t2->a = t1->a;
    t2->b = t1->b;
    t2->c = t1->c;
}

void initiate_triple(void *e)
{
    Triple *t = (Triple *)e;
    t->a = t->b = t->c = 0;
}

void destroy_triple(void* e)
{
    
}