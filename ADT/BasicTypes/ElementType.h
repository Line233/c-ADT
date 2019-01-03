#ifndef _ELEMENTTYPE_H
#define _ELEMENTTYPE_H

typedef enum
{
    Tint,
    Ttriple,
    None
} type;
typedef struct
{
    void *content;
    type t;
} ElementType;

//public
void InitiateElement(ElementType *e, type t);
void DestroyElement(ElementType *e);
void PrintElement(ElementType t);
int CmpElement(ElementType a, ElementType b);
void CopyElement(ElementType *copy, ElementType a);
void SetElement(ElementType t, void *value);

//for eachtype


#include "Triple.h"
#include"Int.h"
//function list
static void (*print[])(void *) = {
    PrintInt, PrintTriple};
static int (*Cmp[])(void *, void *) =
    {
        CmpInt, CmpTriple};
static void (*Copy[])(void *, void *) = {
    CopyInt, CopyTriple};
static void (*Initiate[])(void *) = {
    InitiateInt, InitiateTriple};
static void(*Destroy[])(void*)={
    DestroyInt,InitiateTriple
};
static int Esize[] = {sizeof(int), sizeof(Triple)};


#endif