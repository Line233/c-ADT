#include "ElementType.h"
#include <stdio.h>
#include"Triple.h"

void testInt()
{
    //test initiate print and set
    //generic type
    ElementType a;
    InitiateElement(&a, Tint);
    PrintElement(a);
    printf("\n");
    int x = 5;
    SetElement(a, &x);
    PrintElement(a);

    //test copy and cmp
    ElementType b;
    InitiateElement(&b, Tint);
    x = 10;
    SetElement(b, &x);
    x = CmpElement(a, b);
    printf("\n%d\n", x);
    CopyElement(&b, a);
    PrintElement(b);
    printf("\n");

    //test Destroy
    DestroyElement(&a);
    printf("destroy%s successfully", a.content ? " not" : "");
}
void TestTriple()
{
    ElementType t;
    InitiateElement(&t, Ttriple);
    Triple tx;
    InitiateTriple(&tx);
    SetElement(t,&tx);
    PrintElement(t);
    printf("\n\n");
}
int main()
{
    TestTriple();
    testInt();
    //over
    getchar();
}
