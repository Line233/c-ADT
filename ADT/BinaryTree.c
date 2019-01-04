#include "BinaryTree.h"
#include <malloc.h>
#include "StackS.h"

void InitiateBTree(BTree *bt, type t)
{
    *bt = (BTree)malloc(sizeof(struct btree));
    if (!bt)
        EXIT(ERROR, "no space when initiate bt");
    InitiateElement(&(*bt)->e, t);
    (*bt)->depth = 0;
    (*bt)->left = (*bt)->right = NULL;
    (*bt)->t = t;
}

void OrderInsertBT(BTree bt, ElementType e)
{
    if (bt->t != e.t)
        EXIT(ERROR, "type different when orderInsertBT");
    int c = CmpElement(bt->e, e);
    if (c < 0)
    {
        if (bt->right == NULL)
        {
            BTree btc;
            InitiateBTree(&btc, e.t);
            CopyElement((btc->e), e);
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
            InitiateBTree(&btc, e.t);
            CopyElement((btc->e), e);
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
    // else
    // {
    //     PrintBTree(bt->left);
    //     PrintElement(bt->e);
    //     printf("\n");
    //     PrintBTree(bt->right);
    // }
    // printf("\n");

    //inplement by stack
    StackS stack;
    InitiateStackS(&stack, Tpointer);
    ElementType e;
    InitiateElement(&e, Tpointer);
    void *tmp;
    //
    BTree p = bt;
    for (; p != NULL; p = p->left)
    {
        tmp = p;
        SetElement(e, &tmp);
        PushSS(e, &stack);
    } //go to left to end
    while (!IsEmptySS(stack))
    {
        PopSS(&stack, &e); //each pop which's left should had been read
        p = *((BTree *)e.content);
        PrintElement(p->e);
        printf("\n");
        for (BTree q = p->right; q != NULL; q = q->left)
        {
            SetElement(e, &q);
            PushSS(e, &stack);
        } //go to left to end
    }
}