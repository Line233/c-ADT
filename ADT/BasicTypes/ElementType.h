#ifndef _ELEMENTTYPE_H
#define _ELEMENTTYPE_H

typedef enum
{
    Tint,
    Ttriple,
    Tpointer,
    Tchar,
    Tcii,
    Tci,
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
#include "Char.h"
#include"CII.h"
#include"CI.h"
//function list
static void (*print_e[])(void *) =
    {print_int, print_triple, print_pointer,print_char,print_cii,print_ci};
static int (*cmp_e[])(void *, void *) =
    {cmp_int, cmp_triple, cmp_pointer,cmp_char,cmp_cii,cmp_ci};
static void (*copy_e[])(void *, void *) = {
    copy_int, copy_triple, copy_pointer,copy_char,copy_cii,copy_ci};
static void (*initiate_e[])(void *) = {
    initiate_int, initiate_triple, initiate_pointer,initiate_char,initiate_cii,initiate_ci};
static void (*destroy_e[])(void *) = {
    destroy_int, destroy_triple, destroy_pointer,destroy_char,destroy_cii,destroy_ci};
static int Esize[] = {sizeof(int), sizeof(Triple), sizeof(void *),sizeof(char),sizeof(cii),sizeof(ci)};

#endif