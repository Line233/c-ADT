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
            btc->depth = bt->depth + 1;
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
            btc->depth = bt->depth + 1;
        }
        else
        {
            OrderInsertBT(bt->left, e);
        }
    }
}
void InOrderTraverse(BTree bt, void (*visit)(BTree))
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
        PushSS(&stack, e);
    } //go to left to end
    while (!IsEmptySS(stack))
    {
        PopSS(&stack, &e); //each pop which's left should had been read
        GetValue(e, &p);
        (*visit)(p);
        for (BTree q = p->right; q != NULL; q = q->left)
        {
            SetValue(e, &q);
            PushSS(&stack, e);
        } //go to left to end
    }
}
void PreOrderTraverse(BTree bt, void (*visit)(BTree))
{
    if (bt == NULL)
        return;
    //variables
    StackS stack;
    InitiateStackS(&stack, Tpointer);
    ElementType e;
    InitiateElement(&e, Tpointer);
    //pre order traverse
    BTree p = bt;
    SetValue(e, &p);
    PushSS(&stack, e);

    while (!IsEmptySS(stack))
    {
        PopSS(&stack, &e);
        GetValue(e, &p);
        (*visit)(p);
        if (p->right)
        {
            SetValue(e, &(p->right));
            PushSS(&stack, e);
        }
        if (p->left)
        {
            SetValue(e, &(p->left));
            PushSS(&stack, e);
        }
    }
}
void PostOrderTraverse(BTree bt, void (*visit)(BTree))
{
    if (bt == NULL)
        return;
    //variables
    StackS stack;
    InitiateStackS(&stack, Tpointer);
    ElementType e;
    InitiateElement(&e, Tpointer);
    //pre order traverse
    BTree pre = NULL;
    BTree p = bt;
    SetValue(e, &p);
    PushSS(&stack, e);

    //
    while (!IsEmptySS(stack))
    {
        GetTopSS(stack, &e);
        GetValue(e, &p);
        if ((p->left == NULL && p->right == NULL) || (p->right != NULL && p->right == pre) || (p->right == NULL && p->left == pre))
        {
            PopSS(&stack, &e);
            (*visit)(p);
            pre = p;
        }
        else
        {
            if (p->right)
            {
                SetValue(e, &(p->right));
                PushSS(&stack, e);
            }
            if (p->left)
            {
                SetValue(e, &(p->left));
                PushSS(&stack, e);
            }
        }
    }
}
void InOrderTraverseR(BTree bt, void (*visit)(BTree))
{
    if (bt == NULL)
        return;
    else
    {
        InOrderTraverseR(bt->left, (*visit));
        (*visit)(bt);
        InOrderTraverseR(bt->right, (*visit));
    }
    printf("\n");
}