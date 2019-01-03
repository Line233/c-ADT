#include "BinaryTree.h"
#include <stdio.h>
#include"BinaryTree.h"
#include"ElementType.h"
int main()
{
    //public
    FILE *f = fopen("BTTEST.txt", "r");
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
        SetElement(e,&x);
        if(bt==NULL)
        {
            InitiateBTree(&bt,e);
        }
        else{
            OrderInsertBT(bt,e);
        }
    }
    PrintBTree(bt);

    //public
    fclose(f);
    printf("closed file\n");
    getchar();
}