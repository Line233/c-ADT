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
void InOrderTraverse(BTree bt, void (*visit)(ElementType))
{
    if (bt == NULL)
        return;
    //variables
    StackS stack;
    InitiateStackS(&stack, Tpointer);
    ElementType e;
    InitiateElement(&e, Tpointer);
    //traverse
    BTree p = bt;
    for (; p != NULL; p = p->left)
    {
        SetValue(e, &p);
        PushSS( &stack,e);
    } //go to left to end
    while (!IsEmptySS(stack))
    {
        PopSS(&stack, &e); //each pop which's left should had been read
        GetValue(e,&p);
        (*visit)(p->e);
        for (BTree q = p->right; q != NULL; q = q->left)
        {
            SetValue(e, &q);
            PushSS( &stack,e);
        } //go to left to end
    }
}
void InOrderTraverseR(BTree bt, void (*visit)(ElementType))
{
    if (bt == NULL)
        return;
    else
    {
        InOrderTraverseR(bt->left,(*visit));
        (*visit)(bt->e);
        InOrderTraverseR(bt->right,(*visit));
    }
    printf("\n");
}