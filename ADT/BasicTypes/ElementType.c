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
    (*Initiate[t])(e->content);
}
void DestroyElement(ElementType *e)
{
    e->t = Tnone;
    (*Destroy)(e->content);
    if (e->content)
        free(e->content);
    e->content = NULL;
}
void PrintElement(ElementType e)
{
    (*print[e.t])(e.content);
}
int CmpElement(ElementType a, ElementType b)
{
    if (a.t != b.t)
        EXIT(ERROR, "differrent type can't compare");
    return (*Cmp[a.t])(a.content, b.content);
}
void CopyElement(ElementType copy, ElementType a)
{
    if (copy.t != a.t)
        EXIT(ERROR, "differrent type can't compare");
    (*Copy[copy.t])(copy.content, a.content);
}
void SetValue(ElementType e, void *value)
{
    (*Copy[e.t])(e.content, value);
}
void GetValue(ElementType e, void *value)
{
    (*Copy[e.t])(value, e.content);
}

//for each type
//for int

//for a triple