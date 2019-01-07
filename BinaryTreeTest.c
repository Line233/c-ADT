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
            InOrderTraverse_BT(bt, visit_bt);
            PreOrderTraverse_BT(bt, visit_bt);
            PostOrderTraverse_BT(bt, visit_bt);
        }
        else
        {
            OrderInsertElement_BT(&bt, e, CmpElement);
        }
    }
    TEST("print bt in order(InOrderTraverse_BT)", 2);
    InOrderTraverse_BT(bt, visit_bt);
    TEST("PreOrderTraverse_BT", 2);
    PreOrderTraverse_BT(bt, visit_bt);
    TEST("PostOrderTraverse_BT", 2);
    PostOrderTraverse_BT(bt, visit_bt);

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
    PreOrderTraverse_BT(btforc, visit_bt);

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
    InitiateElement(&e, Tci);
    BTree bt = NULL;
    c = fgetc(f);
    while (c != EOF)
    {
        // printf("%c",c);//debug
        ci cix = {c, 1};
        SetValue(e, &cix);
        BTree find = NULL;
        Find_BT(bt, e, &find);
        if (find == NULL)
        {
            OrderInsertElement_BT(&bt, e, CmpElement);
        }
        else
        {
            ((ci *)find->e.content)->a++;
        }
        c = fgetc(f);
    }
    printf("alpha binarytree is(pre order)\n");
    PreOrderTraverse_BT(bt, visit_bt);

    //convert bt sort by ci.a
    BTree btbya = NULL;
    Newstruct_BT(&bt, &btbya, Cmp_ci_a);
    printf("\n\nweight binarytree is(in order)\n");
    InOrderTraverse_BT(btbya, visit_bt);

    //construct huffmantree
    printf("\n\nhuffmantree  is(level order)\n");
    ConverttoHuffmanTree(&btbya);
    LevelOrderTraverse_BT(btbya, visit_bt, 1);
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