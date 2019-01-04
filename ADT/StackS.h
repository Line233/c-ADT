//status
#ifndef _STACKS_H
#define _STACKS_H

#include "Status.h"
#include "ElementType.h"
#include <stdbool.h>

#define STACKS_INIT_SIZE 5
#define STACKS_INCREACEMENT 5

//for maze
// #define _Maze

typedef struct
{
    ElementType *top;
    ElementType *base;
    int size;
    type t;
} StackS;


Status InitiateStackS(StackS *s,type e);
Status PrintStackS(char info[], StackS stack);
Status PushSS(ElementType e, StackS *stack);
Status IncreaseSS(StackS *stack);
void GetTopSS(StackS stack,ElementType* e);
void PopSS(StackS *stack,ElementType* e);
bool IsEmptySS(StackS stack);
#endif