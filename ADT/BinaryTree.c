#include "BinaryTree.h"
#include <malloc.h>

void InitiateBTree(BTree *bt, ElementType e)
{
    *bt = (BTree)malloc(sizeof(struct btree));
    if (!bt)
        EXIT(ERROR, "no space when initiate bt");
    InitiateElement(&(*bt)->e, e.t);
    CopyElement(&(*bt)->e, e);
    (*bt)->depth = 0;
    (*bt)->left = (*bt)->right = NULL;
}

void OrderInsertBT(BTree bt, ElementType e)
{
    int c = CmpElement(bt->e, e);
    if (c < 0)
    {
        if (bt->right == NULL)
        {
            BTree btc;
            InitiateBTree(&btc, e);
            bt->right = btc;
        }
        else
        {
            OrderInsertBT(bt->right, e);
        }
    }
    else
    {
        if (bt->left == NULL)
        {
            BTree btc;
            InitiateBTree(&btc, e);
            bt->left = btc;
        }
        else
        {
            OrderInsertBT(bt->left, e);
        }
    }
}
void PrintBTree(BTree bt)
{
    if (bt == NULL)
        return;
    else
    {
        PrintBTree(bt->left);
        PrintElement(bt->e);
        printf("\n");
        PrintBTree(bt->right);
    }
}