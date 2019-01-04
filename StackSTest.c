#include <stdio.h>
#include "status.h"
#include "StackS.h"
#include <stdlib.h>
// //APPLICATION-conversion of Numeral System
// void Conversion(int ten, int aim)
// {
//     StackS stack;
//     InitiateStackS(&stack);
//     int r = ten;
//     do
//     {
//         PushSS(r % aim, &stack);
//         r = r / aim;
//     } while (r != 0);
//     printf("%d is ", ten);
//     while (!IsEmptySS(stack))
//     {
//         printf("%d", PopSS(&stack));
//     }
//     printf("\n");
// }
// //conversion end

// //APPLICATION HANOI
// void move(int n, StackS *a, StackS *b, StackS *c)
// {
//     if (n == 1)
//     {
//         if (!IsEmptySS(*a))
//             PushSS(PopSS(a), c);
//         else
//             EXIT(ERROR,"Error in move");
//     }
//     else
//     {
//         move(n - 1, a, c, b);
//         move(1, a, b, c);
//         move(n - 1, b, a, c);
//     }
// }
// void hanoi() //a,b,c three stack
// {
//     FILE *f = fopen("hanoi.txt", "r");
//     int n = 0;
//     if (fscanf(f, "%d", &n) != 1)
//     {
//         fclose(f);
//         EXIT(ERROR, "hanoi,input error");
//     }
//     else
//     {
//         fclose(f);
//         //
//         StackS a, b, c;
//         InitiateStackS(&a);
//         InitiateStackS(&b);
//         InitiateStackS(&c);
//         for (int i = n; i > 0; i--) //n to 1
//         {
//             PushSS(i, &a);
//         }
//         PrintStackS("origin-a:",a);
//         PrintStackS("origin-b:",b);
//         PrintStackS("origin-c:",c);
//         move(n, &a, &b, &c);
//         PrintStackS("moved-a:",a);
//         PrintStackS("moved-b:",b);
//         PrintStackS("moved-c:",c);
//     }
// }
//HANOI END
int main(void)
{
    // hanoi();
    // //read data from in.txt to a list
    FILE *r;
    r = fopen("TestData/StackTest.txt", "r");
    if (r == NULL)
    {
        printf("error:open failed");
        return ERROR;
    }
    feof(r);

    //test InitiateStackS, PrintStackS
    
    StackS stack;
    ElementType e;
    InitiateElement(&e, Tint);
    InitiateStackS(&stack, Tint);
    PrintStackS("an empty stacks", stack);
    

    //test PushSS, IncreaseSS
    int n;
    fscanf(r, "%d", &n);
    for (int i = 0; i < n; i++)
    {
        int x;
        fscanf(r, "%d", &x);
        SetElement(e, &x);
        PushSS(e, &stack);
        // PrintStackS("had pushed stack", stack);//debug
    }
    PrintStackS("had pushed stack", stack);
    int n2;
    fscanf(r, "%d", &n2);
    for (int i = 0; i < n2; i++)
    {
        int x;
        fscanf(r, "%d", &x);
        SetElement(e, &x);
        PushSS(e, &stack);
    }
    PrintStackS("test increase", stack);

    //test GetTopSS
    GetTopSS(stack, &e);
    printf("top is ");
    PrintElement(e);
    printf("\n\n");
    //test PopSS
    while (stack.top - stack.base > 0)
    {
        PopSS(&stack, &e);
        printf("pop ");
        PrintElement(e);
        printf("\n");
    }
    PrintStackS("empty stack:", stack);

    //test
    ElementType e2;
    InitiateElement(&e2,Tpointer);
    StackS stack2;
    InitiateStackS(&stack2,Tpointer);
    int array[10];
    int array2[5];
    for(int i=0;i<10;i++){
        void* v=&array[i];
        SetElement(e2,&v);
        PushSS(e2,&stack2);
    }
    PrintStackS("stack2",stack2);
     for(int i=0;i<5;i++){
        void* v=&array2[i];
        SetElement(e2,&v);
        PopSS(&stack2,&e2);
        printf("\n");
        PrintElement(e2);
    }
    PrintStackS("ff",stack2);
 for(int i=0;i<10;i++){
        void* v=&array[i];
        SetElement(e2,&v);
        PushSS(e2,&stack2);
    }
    PrintStackS("stack2",stack2);

    // //top get error
    // printf("top is %d\n\n", GetTopSS(stack));

    //use conversion num
    // int n3;
    // fscanf(r, "%d", &n3);
    // Conversion(n3, 2);
    int x = fclose(r);
    printf("close file successfully %d", x);
    getchar();
}
