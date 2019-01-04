#include"Int.h"
#include"Status.h"
#include<stdio.h>

void initiate_int(void *e)
{
    *((int*)e)=0;
}
void print_int(void *k)
{
    printf("%d", *(int *)k);
}
int cmp_int(void *a, void *b)
{
    return *(int *)a - *(int *)b;
}
void copy_int(void *copy, void *a)
{
    *((int *)copy) = *((int *)a);
}
void destroy_int(void* e)
{

}