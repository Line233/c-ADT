//status
#ifndef _STATICLIST_H
#define _STATICLIST_H

#include "Status.h"
#include "ElementType.h"
#include <stdbool.h>

#define STATICLIST_INIT_SIZE 5
#define STATICLIST_INCREACEMENT 5

//for maze
// #define _Maze

typedef struct
{
    ElementType *base;
    int last;
    int space;
    int used;
    type t;
} StaticList;

Status Initiate_SList(StaticList *s, type e);

//insert
void InsertatEnd_Slist(StaticList *s, ElementType e);

void Increase_SList(StaticList *slist);

void Travserse_SList(StaticList slist, void (*visit)(ElementType));

void Locate_Slist(StaticList slist,int i,ElementType* e);

void Destory_SList(StaticList *slist);

bool IsEmpty_SList(StaticList slist);
#endif