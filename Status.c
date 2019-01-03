#include<stdio.h>
#include"status.h"
#include<stdlib.h>

void EXIT(int x,char s[]){
    printf("%s\n",s);
    getchar();
    exit(x);
}
