#include "CodeNode.h"
#include "Status.h"
#include <stdio.h>
#include <malloc.h>

void print_codenode(void *k)
{
    codenode *t = (codenode *)k;
    printf("%c\t%d\t%s", t->c, t->a, t->code?t->code:"");
};

int cmp_codenode(void *a, void *b)
{
    codenode *t1 = (codenode *)a;
    codenode *t2 = (codenode *)b;
    return t1->c - t2->c;
}

void copy_codenode(void *copy, void *a)
{
    codenode *t1 = (codenode *)a;
    codenode *t2 = (codenode *)copy;
    t2->c = t1->c;
    t2->a = t1->a;
    if (t2->code)
        free(t2->code);
    int i;
    for (i = 0; t1->code[i] != '\0'; i++)
        ;
    t2->code = (char *)malloc(sizeof(char) * (i + 1));
    if (!t2)
        EXIT(ERROR, "no space when copy_codenode");
    for (int j = 0; j < i + 1; j++)
        t2->code[j] = t1->code[j];
}

void initiate_codenode(void *e)
{
    codenode *t = (codenode *)e;
    t->c = '\0';
    t->a = 0;
    t->code = NULL;
}

void destroy_codenode(void *e)
{
    codenode *t = (codenode *)e;
    t->c = '\0';
    t->a = 0;
    if (t->c)
        free(t->code);
    t->code = NULL;
}