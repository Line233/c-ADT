
#include "status.h"
#include <malloc.h>
#include "StaticList.h"
#include "ElementType.h"

Status Initiate_SList(StaticList *s, type e)
{
    if (!s)
    {
        s = (StaticList *)malloc(sizeof(StaticList));
        if (!s)
            EXIT(ERROR, "no space when initiate slist");
    }
    s->base = malloc(sizeof(ElementType) * STATICLIST_INIT_SIZE);
    if (!s->base)
        EXIT(ERROR, "no space when initiate slist");
    s->last = 0;
    s->space = STATICLIST_INIT_SIZE;
    s->used = 0;
    s->t = e;
    for (int i = 0; i < s->space; i++)
        InitiateElement(s->base + i, e);
}

void InsertatEnd_Slist(StaticList *s, ElementType e)
{
    if (s->used == s->space)
    {
        Increase_SList(s);
    }
    CopyElement(*(s->base + s->last), e);
    s->last++;
    s->used++;
}

void Increase_SList(StaticList *slist)
{
    slist->base = (ElementType *)realloc(slist->base, (slist->space + STATICLIST_INCREACEMENT) * sizeof(ElementType));
    if (!slist->base)
        EXIT(ERROR, "increase space failed when Increase_SList");
    slist->space += STATICLIST_INCREACEMENT;
}

void Travserse_SList(StaticList slist, void (*visit)(ElementType))
{
    for (int i = 0; i < slist.used; i++)
    {
        (*visit)(*(slist.base + i));
    }
}

void Locate_Slist(StaticList slist, int i, ElementType *e)
{
    if (e->t != slist.t || i < 0 || i > slist.last - 1)
        EXIT(ERROR, "argument error when Locate_Slist");
    CopyElement(*e, *(slist.base + i));
}
void Destory_SList(StaticList *slist);

bool IsEmpty_SList(StaticList slist);