
#include"Pointer.h"
#include<stdio.h>


void print_pointer(void *k)
{
    printf("%p",*(void**)k);
}
int cmp_pointer(void *a, void *b)
{
    return *(void**)a-*(void**)b;
}
void copy_pointer(void *copy, void *a)
{
    *(void**)copy=*(void**)a;
}
void initiate_pointer(void *e)
{
    *(void**)e=NULL;
}
void destroy_pointer(void* e)
{
    *(void**)e=NULL;
}
