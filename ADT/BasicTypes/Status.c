#include <stdio.h>
#include "status.h"
#include <stdlib.h>

void EXIT(int x, char s[])
{
    printf("%s\n", s);
    getchar();
    exit(x);
}
void TEST(char content[], int level)
{
    if (level == 0)
    {
        printf("TEST %s", content);
        printf("-------------------\n");
    }
    else
    {
        for(int i=0;i<level;i++)
        {
            printf("\t");
        }
        printf("TEST %s\n", content);
    }
}
