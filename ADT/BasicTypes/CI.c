#include "CI.h"
#include <stdio.h>
#include "Status.h"

void print_ci(void *k)
{
    ci *t = (ci *)k;
    printf("%c\t%d", t->c, t->a);
};

int cmp_ci(void *a, void *b)
{
    ci *t1 = (ci *)a;
    ci *t2 = (ci *)b;
    return t1->c - t2->c;
}

void copy_ci(void *copy, void *a)
{
    ci *t1 = (ci *)a;
    ci *t2 = (ci *)copy;
    t2->c = t1->c;
    t2->a = t1->a;
}

void initiate_ci(void *e)
{
    ci *t = (ci *)e;
    t->c = '\0';
    t->a  = 0;
}

void destroy_ci(void *e)
{
    ci *t = (ci *)e;
    t->c = '\0';
    t->a  = 0;
}