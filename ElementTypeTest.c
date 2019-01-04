#include "ElementType.h"
#include <stdio.h>
#include "Triple.h"

void testInt()
{
    printf("test Int______________________");
    //test initiate print
    //generic type
    ElementType a;
    InitiateElement(&a, Tint);
    printf("test initiate:a is\n\t");
    PrintElement(a);
    printf("\n");

    //test setvalue
    printf("test set value:a should be x/5\n\t");
    int x = 5;
    SetElement(a, &x);
    PrintElement(a);
    printf("\n");

    //test copy cmp
    printf("test copy:b should equal a\n\t");
    ElementType b;
    InitiateElement(&b, Tint);
    CopyElement(b, a);
    PrintElement(b);
    printf("\n");

    //test cmp
    printf("test cmp:result should be zero");
    x = CmpElement(a, b);
    printf("\n\t%d\n", x);
    printf("\n");

    //test Destroy
    DestroyElement(&a);
    printf("destroy%s successfully", a.content ? " not" : "");
    printf("test Int______________________\n\n");
}
void TestTriple()
{
    printf("test triple____________________________\n");

    //initiate
    printf("test initiate:t is\n\t");
    ElementType t;
    InitiateElement(&t, Ttriple);
    PrintElement(t);
    printf("\n");

    //test set value
    printf("test set value:t should be 1 2 3\n\t");
    Triple tx;
    InitiateTriple(&tx);
    tx.a=1;tx.b=2,tx.c=3;
    SetElement(t, &tx);
    PrintElement(t);
    printf("\n");
}
int main()
{
    TestTriple();
    testInt();
    //over
    getchar();
}
