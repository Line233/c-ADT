#include "status.h"
#include <malloc.h>
#include "StackS.h"
#include "ElementType.h"

Status InitiateStackS(StackS *s, type e)
{
    s->base = (ElementType *)malloc(STACKS_INIT_SIZE * sizeof(ElementType));
    if (!s->base)
        EXIT(ERROR, "no space when initiate stack");
    s->top = s->base;
    for (int i = 0; i < STACKS_INIT_SIZE; i++)
    {
        InitiateElement(s->base + i, e);
    }
    s->size = STACKS_INIT_SIZE;
    s->t=e;
}
Status PrintStackS(char info[], StackS stack)
{
    printf("%s:\n", info);
    printf("\ttotal space:%d\n", stack.size);
    printf("\tused size is %d\n",stack.top-stack.base);
    ElementType *p = stack.top;
    while (p - stack.base > 0)
    {
        printf("\t"); //modified
        PrintElement(*(p - 1));
        printf("\n"); //modified
        p--;
    }
    printf("\n");
}
Status PushSS(ElementType e, StackS *stack) //if you want to change this struct you have to use a pointer
{
    if(e.t!=stack->t) EXIT(ERROR,"different type when pushss");
    if (stack->top - stack->base >= stack->size)
    {
        //don't have enough space
        IncreaseSS(stack);
    }
    CopyElement(*(stack->top),e);
    stack->top++;

}
Status IncreaseSS(StackS *stack)
{
    stack->base = (ElementType *)realloc(stack->base, sizeof(ElementType) * (stack->size + STACKS_INCREACEMENT));
    if (!stack->base)
        exit(OVERFLOW);
    (*stack).top = (*stack).base + stack->size;
    for (int i = 0; i < STACKS_INCREACEMENT; i++)
    {
        InitiateElement((*stack).top+i,stack->base->t);
    }
    stack->size += STACKS_INCREACEMENT;
}
void GetTopSS(StackS stack,ElementType* e)
{
    if(e->t!=stack.t) EXIT(ERROR,"different type when gettopss");

    if (stack.top - stack.base > 0)
    {
        // *e= *(stack.top - 1);
        CopyElement(*e,*(stack.top-1));
    }
    else
    {
        exit(OVERFLOW);
    }
}
void PopSS(StackS *stack,ElementType* e)
{
    if(e->t!=stack->t) EXIT(ERROR,"different type when popss");

    if (stack->top - stack->base > 0)
    {
        // *e= *(stack->top - 1);
        CopyElement(*e,*(stack->top-1));
        stack->top--;
    }
    else
    {
        exit(OVERFLOW);
    }
}
bool IsEmptySS(StackS stack)
{
    return !(stack.top - stack.base > 0);
}
void DestorySS(StackS* stack)
{
    for(int i=0;i<stack->size;i++)
    {
        DestroyElement(stack->base+i);
    }
    if(stack->base)
        free(stack->base);
    stack->base=stack->top=NULL;
    stack->size=0;
    stack->t=Tnone;
}