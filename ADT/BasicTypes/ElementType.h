#ifndef _ELEMENTTYPE_H
#define _ELEMENTTYPE_H

typedef enum
{
    Tint,
    Ttriple,
    Tpointer,
    Tnone
} type;
typedef struct
{
    void *content;
    type t;
} ElementType;//a struct 

//public
void InitiateElement(ElementType *e, type t); //malloc content
void DestroyElement(ElementType *e);          //free content
void PrintElement(ElementType t);
int CmpElement(ElementType a, ElementType b);
void CopyElement(ElementType copy, ElementType a);
void SetValue(ElementType t, void *value);

//for eachtype

#include "Triple.h"
#include "Int.h"
#include"Pointer.h"
//function list
static void (*print[])(void *) = {
    PrintInt, PrintTriple,PrintPointer};
static int (*Cmp[])(void *, void *) =
    {
        CmpInt, CmpTriple,CmpPointer};
static void (*Copy[])(void *, void *) = {
    CopyInt, CopyTriple,CopyPointer};
static void (*Initiate[])(void *) = {
    InitiateInt, InitiateTriple,InitiatePointer};
static void (*Destroy[])(void *) = {
    DestroyInt, DestroyTriple,DestroyPointer};
static int Esize[] = {sizeof(int), sizeof(Triple),sizeof(void*)};

#endif