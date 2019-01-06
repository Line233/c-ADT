#include "Char.h"
#include "Status.h"
#include <stdio.h>

void initiate_char(void *e)
{
    *((char *)e) = '\0';
}
void print_char(void *k)
{
    printf("%c", *(char *)k);
}
int cmp_char(void *a, void *b)
{
    return *(char *)a - *(char *)b;
}
void copy_char(void *copy, void *a)
{
    *((char *)copy) = *((char *)a);
}
void destroy_char(void *e)
{
    *((char *)e) = '\0';
}