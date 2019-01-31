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
    printf("  bf:%d\n", bt->bf);
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

    //test avl
    TEST("avl test", 1);
    BTree avl = NULL;
    fscanf(f, "%d", &n);
    for (int i = 0; i < n; i++)
    {
        fscanf(f, "%d", &x);
        SetValue(e, &x);
        InsertElement_avl_BT(&avl, e, CmpElement);
        avl->parent = NULL;
        avl->depth = 0;
    }
    PreOrderTraverse_BT(avl, visit_bt);

    //public
    fclose(f);
    printf("closed file\n");
    getchar();
}
void print_pcodenode(ElementType e)
{
    codenode *c;
    GetValue(e, &c);
    print_codenode(c);
    printf("\n");
}
void print_pcodenode_inBT(BTree bt)
{
    for (int i = 0; i < bt->depth; i++)
    {
        printf(".");
    }
    print_pcodenode(bt->e);
}
void HuffmanTreeTest()
{
    BTree bt = NULL;
    CreateAlpabetTree("./TestData/HuffmanTreeTest.txt", &bt);
    PreOrderTraverse_BT(bt, print_pcodenode_inBT);
    BTree huffmantree = NULL;
    CreateHuffmanTree(&bt, &huffmantree);
    //
    printf("close successfully\n\n\n");

    HuffmanCode(bt, "./TestData/HuffmanTreeTest.txt", "./TestData/huffmanout.txt");
    printf("HuffmanCode over\n\n");
    HuffmanDecode(huffmantree, "./TestData/huffmanout.txt", "./TestData/huffmantreeHuffmanDecode.txt");
    printf("HuffmanDecode over\n\n");

    SaveAlphaTreetoFile(bt, "./TestData/AlphaTree_Huffman.txt");
    printf("print alphatree over\n");
    getchar();
}
int main()
{
    BinaryTreeTest();

    HuffmanTreeTest();
}