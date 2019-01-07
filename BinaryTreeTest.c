#include "BinaryTree.h"
#include <stdio.h>
#include "BinaryTree.h"
#include "ElementType.h"
#include "Char.h"

void visit_bt(BTree bt)
{
    for (int i = 0; i < bt->depth; i++)
    {
        printf(". ");
    }
    PrintElement(bt->e);
    printf("\n");
}
void BinaryTreeTest()
{
    //public
    TEST("BINARYTREE", 0);
    FILE *f = fopen("TestData/BTTEST.txt", "r");
    if (!f)
        EXIT(ERROR, "open file failed");
    int n, x;
    ElementType e;
    InitiateElement(&e, Tint);
    char c;
    ElementType chars[255];
    for (int i = 0; i < 255; i++)
    {
        InitiateElement(&chars[i], Tchar);
    }
    BTree bt, btforc;

    //test initiate and order insert
    TEST("OrderInsert and Traverse", 1);
    bt = NULL;
    fscanf(f, "%d", &n);
    for (int i = 0; i < n; i++)
    {
        fscanf(f, "%d", &x);
        SetValue(e, &x);
        if (bt == NULL)
        {
            TEST("bt with only one element(in three traverse order)", 2);
            InitiateBTree(&bt, e.t);
            CopyElement((bt->e), e);
            InOrderTraverse(bt, visit_bt);
            PreOrderTraverse(bt, visit_bt);
            PostOrderTraverse(bt, visit_bt);
        }
        else
        {
            OrderInsertBT(&bt, e);
        }
    }
    TEST("print bt in order(InOrderTraverse)", 2);
    InOrderTraverse(bt, visit_bt);
    TEST("PreOrderTraverse", 2);
    PreOrderTraverse(bt, visit_bt);
    TEST("PostOrderTraverse", 2);
    PostOrderTraverse(bt, visit_bt);

    //test create inorder
    TEST("Create in order", 1);
    fscanf(f, "%c", &c);
    fscanf(f, "%c", &c);
    for (n = 0; n < 255; n++)
    {
        fscanf(f, "%c", &c);
        if (c != '\n')
        {
            SetValue(chars[n], &c);
        }
        else
        {
            break;
        }
    }
    for (int i = 0; i < n; i++)
    {
        PrintElement(chars[i]);
        printf("\t");
    }
    ElementType *charss = chars;
    CreateInorderBT(&btforc, &charss, &n, 0);
    PreOrderTraverse(btforc, visit_bt);

    //public
    fclose(f);
    printf("closed file\n");
    getchar();
}
void HuffmanTreeTest()
{
    //read
    FILE *f = fopen("./TestData/HuffmanTreeTest.txt", "r");
    if (!f)
        EXIT(ERROR, "open file error");
    char c;
    ElementType e;
    InitiateElement(&e, Tcii);
    BTree bt = NULL;
    c = fgetc(f);
    while (c != EOF)
    {
        // printf("%c",c);//debug
        cii ci = {c, 1, notHT};
        SetValue(e, &ci);
        BTree find = NULL;
        FindinBTree(bt, e, &find);
        if (find == NULL)
        {
            OrderInsertBT(&bt, e);
        }
        else
        {
            ((cii *)find->e.content)->a++;
        }
        c = fgetc(f);
        // PreOrderTraverse(bt, visit_bt); //debug
        // getchar();//debug
    }
    printf("bt is\n");
    PreOrderTraverse(bt, visit_bt);
    printf("huffmantree is\n");

    ConverttoHuffmanTree(&bt);
    PreOrderTraverse(bt, visit_bt);
    //
    fclose(f);
    printf("close successfully\n\n\n");
    getchar();
}
int main()
{
    HuffmanTreeTest();
    BinaryTreeTest();
}