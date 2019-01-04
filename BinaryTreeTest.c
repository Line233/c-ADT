#include "BinaryTree.h"
#include <stdio.h>
#include"BinaryTree.h"
#include"ElementType.h"

void visitInt(ElementType e)
{
    PrintElement(e);
    printf("\n");
}
int main()
{
    //public
    FILE *f = fopen("TestData/BTTEST.txt", "r");
    if (!f)
        EXIT(ERROR, "open file failed");
    int n, x;
    ElementType e;
    InitiateElement(&e,Tint);

    //test initiate and order insert
    BTree bt=NULL;
    fscanf(f, "%d", &n);
    for (int i = 0; i < n; i++)
    {
        fscanf(f,"%d",&x);
        SetValue(e,&x);
        if(bt==NULL)
        {
            InitiateBTree(&bt,e.t);
            CopyElement((bt->e),e);
        }
        else{
            OrderInsertBT(bt,e);
        }
    }
    InOrderTraverse(bt,visitInt);

    //public
    fclose(f);
    printf("closed file\n");
    getchar();
}