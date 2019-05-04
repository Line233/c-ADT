//status
#ifndef _CI_H
#define _CI_H

typedef struct{
    char c;
    int a;
} ci;

void print_ci(void *k);
int cmp_ci(void *a, void *b);
void copy_ci(void *copy, void *a);
void initiate_ci(void *e);
void destroy_ci(void* e );

#endif