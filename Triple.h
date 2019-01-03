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
void PrintTriple(void *k);
int CmpTriple(void *a, void *b);
void CopyTriple(void *copy, void *a);
void InitiateTriple(void* e);
void InitiateTriple(void* e);
void DestroyTriple(void* e);
//
#endif