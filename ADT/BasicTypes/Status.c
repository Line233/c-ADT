#include <stdio.h>
#include "status.h"
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

void EXIT(int x, char s[])
{
    printf("%s\n", s);
    getchar();
    exit(x);
}
void TEST(char content[], int level)
{
    printf("\n");
    if (level == 0)
    {
        printf("TEST %s", content);
        printf("-------------------\n");
    }
    else
    {
        for (int i = 0; i < level; i++)
        {
            printf("\t");
        }
        printf("TEST %s\n", content);
    }
}
void *MALLOC(int size, int num, char *errorinfo)
{
    void *p = malloc(size * num);
    if (!p)
        EXIT(ERROR, strcat("no space", errorinfo));
    else
        return p;
}
void IntiateIntArray(int *array, int n, int defaulti)
{
    for (int i = 0; i < n; i++)
        array[i] = defaulti;
}
// int GetArrayIndex(int d, ...)
// {
//     va_list args;
//     va_start(args, d);
//     for (int i = 0; i < d; i++)
//     {
        
//     }
//     va_end(args);
// }