#include "ElementType.h"
#include "Status.h"
#include <stdio.h>
#include <malloc.h>
//public
void InitiateElement(ElementType *e, type t)
{
    e->t = t;
    e->content = (void *)malloc(Esize[t]);
    if (!e->content)
        EXIT(ERROR, "no space when initiate element");
    (*initiate_e[t])(e->content);
}
void DestroyElement(ElementType *e)
{
    e->t = Tnone;
    (*destroy_e)(e->content);
    if (e->content)
        free(e->content);
    e->content = NULL;
}
void PrintElement(ElementType e)
{
    (*print_e[e.t])(e.content);
}
int CmpElement(ElementType a, ElementType b)
{
    if (a.t != b.t)
        EXIT(ERROR, "differrent type can't compare");
    return (*cmp_e[a.t])(a.content, b.content);
}
void CopyElement(ElementType copy, ElementType a)
{
    if (copy.t != a.t)
        EXIT(ERROR, "differrent type can't copy");
    (*copy_e[copy.t])(copy.content, a.content);
}
void SetValue(ElementType e, void *value)
{
    (*copy_e[e.t])(e.content, value);
}
void GetValue(ElementType e, void *value)
{
    (*copy_e[e.t])(value, e.content);
}

void CopyElementReferrence(ElementType *copy, ElementType a)
{
    if (copy->t != a.t)
        EXIT(ERROR, "error type when CopyElementReferrence");
    copy->content = a.content;
}

void GetContentPointer(ElementType e, void **p)
{
    *p = e.content;
}
void SetContentPointer(ElementType *e, void *p)
{
    if (!e)
        EXIT(ERROR, "null cant be set when SetContentPointer");
    e->content = p;
}
//for each type
//for int

//for a triple