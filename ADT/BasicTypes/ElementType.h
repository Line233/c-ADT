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
} ElementType; //a struct

//public
void InitiateElement(ElementType *e, type t); //malloc content
void DestroyElement(ElementType *e);          //free content
void PrintElement(ElementType t);
int CmpElement(ElementType a, ElementType b);
void CopyElement(ElementType copy, ElementType a);
void SetValue(ElementType e, void *value);
void GetValue(ElementType e, void *value);

//for eachtype

#include "Triple.h"
#include "Int.h"
#include "Pointer.h"
//function list
static void (*print_e[])(void *) =
    {print_int, print_triple, print_pointer};
static int (*cmp_e[])(void *, void *) =
    {cmp_int, cmp_triple, cmp_pointer};
static void (*copy_e[])(void *, void *) = {
    copy_int, copy_triple, copy_pointer};
static void (*initiate_e[])(void *) = {
    initiate_int, initiate_triple, initiate_pointer};
static void (*destroy_e[])(void *) = {
    destroy_int, destroy_triple, destroy_pointer};
static int Esize[] = {sizeof(int), sizeof(Triple), sizeof(void *)};

#endif