#include "CII.h"
#include <stdio.h>
#include "Status.h"

void print_cii(void *k)
{
    cii *t = (cii *)k;
    printf("%c\t%d\t%d", t->c, t->a, t->b);
};

int cmp_cii(void *a, void *b)
{
    cii *t1 = (cii *)a;
    cii *t2 = (cii *)b;
    return t1->c - t2->c;
}

void copy_cii(void *copy, void *a)
{
    cii *t1 = (cii *)a;
    cii *t2 = (cii *)copy;
    t2->c = t1->c;
    t2->a = t1->a;
    t2->b = t1->b;
}

void initiate_cii(void *e)
{
    cii *t = (cii *)e;
    t->c = '\0';
    t->a = t->b = 0;
}

void destroy_cii(void *e)
{
    cii *t = (cii *)e;
    t->c = '\0';
    t->a = t->b = 0;
}