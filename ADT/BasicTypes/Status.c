#include <stdio.h>
#include "status.h"
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <stdbool.h>

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
        EXIT(ERROR, strcat("no space when", errorinfo));
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

int RANDOM(int min, int max)
{
    static bool _setrandom = FALSE;
    if (!_setrandom)
    {
        srand(time(NULL));
        _setrandom = true;
    }
    return (rand() % (max - min) + min);
}

int *GetIntArray(int n, int min, int max)
{
    int *xs = MALLOC(sizeof(int), n, "no space when GetIntArray");
    for (int i = 0; i < n; i++)
    {
        xs[i] = RANDOM(min, max);
    }
    return xs;
}

void PrintIntArray_Tool(int ints[],int n,char* s)
{
    printf("%s\n",s);
    for(int i=0;i<n;i++)
    {
        printf("\t%d\n",ints[i]);
    }
    printf("\n");
}