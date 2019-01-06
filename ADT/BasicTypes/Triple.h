//status
#ifndef _TRIPLE_H
#define _TRIPLE_H

#include<stdio.h>
#include"Status.h"
#include<malloc.h>

typedef struct{
    int a;
    int b;
    int c;
}Triple;

//
void print_triple(void *k);
int cmp_triple(void *a, void *b);
void copy_triple(void *copy, void *a);
void initiate_triple(void* e);
void initiate_triple(void* e);
void destroy_triple(void* e);
//
#endif