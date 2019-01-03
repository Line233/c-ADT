#include"Int.h"
#include"Status.h"
#include<stdio.h>

void InitiateInt(void *e)
{
    *((int*)e)=0;
}
void PrintInt(void *k)
{
    printf("%d", *(int *)k);
}
int CmpInt(void *a, void *b)
{
    return *(int *)a - *(int *)b;
}
void CopyInt(void *copy, void *a)
{
    *((int *)copy) = *((int *)a);
}
void DestroyInt(void* e)
{

}