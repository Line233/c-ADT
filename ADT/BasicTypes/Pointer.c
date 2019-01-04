
#include"Pointer.h"
#include<stdio.h>


void PrintPointer(void *k)
{
    printf("%p",*(void**)k);
}
int CmpPointer(void *a, void *b)
{
    return *(void**)a-*(void**)b;
}
void CopyPointer(void *copy, void *a)
{
    *(void**)copy=*(void**)a;
}
void InitiatePointer(void *e)
{
    *(void**)e=NULL;
}
void DestroyPointer(void* e)
{
    *(void**)e=NULL;
}
