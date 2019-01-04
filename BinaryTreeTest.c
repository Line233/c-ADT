#include "BinaryTree.h"
#include <stdio.h>
#include"BinaryTree.h"
#include"ElementType.h"

void visit_bt(BTree bt)
{
    for(int i=0;i<bt->depth;i++)
    {
        printf(".");
    }
    PrintElement(bt->e);
    printf("\n");
}
int main()
{
    //public
    TEST("BINARYTREE",0);
    FILE *f = fopen("TestData/BTTEST.txt", "r");
    if (!f)
        EXIT(ERROR, "open file failed");
    int n, x;
    ElementType e;
    InitiateElement(&e,Tint);

    //test initiate and order insert
    TEST("OrderInsert and InOrderTraverse",1);
    TEST("bt should be in order from small to big",2);
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
    InOrderTraverse(bt,visit_bt);

    //
    TEST("PreOrderTraverse",1);
    PreOrderTraverse(bt,visit_bt);

    getchar();
    TEST("PostOrderTraverse",1);
    PostOrderTraverse(bt,visit_bt);

    //public
    fclose(f);
    printf("closed file\n");
    getchar();
}