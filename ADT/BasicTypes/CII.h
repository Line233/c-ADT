//status
#ifndef _CHARINT_H
#define _CHARINT_H

typedef struct{
    char c;
    int a;
    int b;
} cii;

void print_cii(void *k);
int cmp_cii(void *a, void *b);
void copy_cii(void *copy, void *a);
void initiate_cii(void *e);
void destroy_cii(void* e);

#endif