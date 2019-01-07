#include "BinaryTree.h"
#include <malloc.h>
#include "StackS.h"
#include "Queue.h"

void InitiateBTree(BTree *bt, type t)
{
    *bt = (BTree)malloc(sizeof(struct btree));
    if (!bt)
        EXIT(ERROR, "no space when initiate bt");
    InitiateElement(&(*bt)->e, t);
    (*bt)->depth = 0;
    (*bt)->left = (*bt)->right = (*bt)->parent = NULL;
    (*bt)->t = t;
}

void OrderInsertBT(BTree *bt, ElementType e)
{
    OrderInsertElementBT_withCmp(bt, e, CmpElement);
}
void OrderInsertBT_withCmp(BTree *bt, BTree node, int (*cmp)(ElementType, ElementType))
{
    if ((*bt) != NULL && (*bt)->t != node->t)
        EXIT(ERROR, "type different when orderInsertBT");
    BTree pre = NULL;
    BTree *btx = bt;
    while (*btx)
    {
        pre = *btx;
        int c = (*cmp)(node->e, (*btx)->e);
        if (c < 0)
        {
            btx = &((*btx)->left);
        }
        else
        {
            //c>=0
            btx = &((*btx)->right);
        }
    }
    *btx = node;
    node->parent = pre;
    node->depth = node->parent ? node->parent->depth + 1 : 0;
}
void OrderInsertElementBT_withCmp(BTree *bt, ElementType e, int (*cmp)(ElementType, ElementType))
{
    BTree btc;
    InitiateBTree(&btc, e.t);
    CopyElement((btc->e), e);
    OrderInsertBT_withCmp(bt, btc, (*cmp));
}
void LevelOrderTraverse(BTree bt, void (*visit)(BTree), int orient)
{
    Queue queue;
    InitiateQueue(&queue, Tpointer);
    bool x = true;
    ElementType pointer;
    InitiateElement(&pointer, Tpointer);
    while (bt)
    {
        (*visit)(bt);
        if (orient == 0)
        {
            if (bt->left)
            {
                SetValue(pointer, &(bt->left));
                EnQueue(&queue, pointer);
            }
            if (bt->right)
            {
                SetValue(pointer, &(bt->right));
                EnQueue(&queue, pointer);
            }
        }
        else
        {
            if (bt->right)
            {
                SetValue(pointer, &(bt->right));
                EnQueue(&queue, pointer);
            }
            if (bt->left)
            {
                SetValue(pointer, &(bt->left));
                EnQueue(&queue, pointer);
            }
        }
        // PrintQueue(queue, "enqueue"); //debug
        if (!IsEmptyQ(queue))
        {
            DeQueue(&queue, &pointer);
            GetValue(pointer, &bt);
        }
        else{
            break;
        }
        // PrintQueue(queue, "dequeue"); //debug
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
    //
    BTree p = bt;
    //traverse function1
    while (p || !IsEmptySS(stack))
    {
        if (p) //should be pushed
        {
            SetValue(e, &p);
            PushSS(&stack, e);
            p = p->left;
        }
        else
        { //p is NULL,returned from left or right.first pop,then insert right
            PopSS(&stack, &e);
            GetValue(e, &p);
            (*visit)(p);
            p = p->right;
        }
    }

    //traverse function2
    // SetValue(e, &p);
    // PushSS(&stack, e);
    // while (!IsEmptySS(stack))
    // {
    //     if (p != NULL)//has pushed a right
    //     {
    //         GetTopSS(stack, &e); //each pop which's left should had been read
    //         GetValue(e, &p);
    //         for (; p->left != NULL; p = p->left)
    //         {
    //             SetValue(e, &(p->left));
    //             PushSS(&stack, e);
    //         } //go to left to end
    //     }
    //     PopSS(&stack, &e);
    //     GetValue(e, &p);
    //     (*visit)(p);
    //     if (p->right)
    //     {
    //         SetValue(e, &(p->right));
    //         PushSS(&stack, e);
    //     }
    //     else
    //     {
    //         p = NULL;
    //     }
    // }
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
void CreateInorderBT(BTree *bt, ElementType **es, int *n, int depth)
{
    char c;
    GetValue(**es, &c);

    if (c == ' ' || n == 0)
    {
        *bt = NULL;
        (*es)++;
        n--;
    }
    else
    {
        InitiateBTree(bt, Tchar);
        CopyElement((*bt)->e, **es);
        (*bt)->depth = depth;
        (*es)++;
        n--;
        CreateInorderBT(&((*bt)->left), es, n, depth + 1);
        CreateInorderBT(&((*bt)->right), es, n, depth + 1);
    }
}
void FindinBTree(BTree bt, ElementType e, BTree *result)
{
    if (bt != NULL && bt->t != e.t)
        EXIT(ERROR, "type different when FindinBTree");

    while (bt)
    {
        int c = CmpElement(e, bt->e);
        if (c == 0)
        {
            break;
        }
        else if (c < 0)
        {
            bt = bt->left;
        }
        else
        {
            //c>0
            bt = bt->right;
        }
    }
    *result = bt;
}
void UpdateDepthofBT(BTree bt)
{
    if (!bt)
        EXIT(ERROR, "null error when UpdateDepthofBT");
    bt->depth = bt->parent ? bt->parent->depth + 1 : 0;
}
void FindMinBT(BTree bt, BTree *min)
{
    *min = bt;
    while (*min && (*min)->left)
    {
        *min = (*min)->left;
    }
}
void DeleteMinBT(BTree *bt, BTree *min)
{
    if ((*bt) == NULL)
    {
        (*min) = (*bt);
        return;
    }
    FindMinBT(*bt, min);
    BTree *pbt = (*min)->parent ? ((*min)->parent->left == (*min) ? &((*min)->parent->left)
                                                                  : &((*min)->parent->right))
                                : bt;
    *pbt = (*min)->right;
    //updata *pbt
    if (*pbt)
    {
        (*pbt)->parent = (*min)->parent;
        PreOrderTraverse((*pbt), UpdateDepthofBT);
    }
    //update *min
    (*min)->left = NULL;
    (*min)->right = NULL;
    (*min)->depth = 0;
}
void ConvertBinaryTreeNewCmp(BTree *old, BTree *new, int (*newcmp)(ElementType, ElementType))
{
    BTree tmpbt;
    while (*old)
    {
        DeleteMinBT(old, &tmpbt);
        OrderInsertBT_withCmp(new, tmpbt, (*newcmp));
    }
}
//huffmantree
#include <CII.h>
void visit_bt2(BTree bt) //debug
{
    for (int i = 0; i < bt->depth; i++)
    {
        printf(". ");
    }
    PrintElement(bt->e);
    printf("\n");
}
BTree tonext_huffmantree(BTree bt, int orient) //0 left,1 right
{
    if (!bt)
        EXIT(ERROR, "null error tonext_huffmantree");
    if (orient == 0)
    {
        while (bt->left != NULL && ((cii *)(bt->left->e.content))->b == inHT)
            bt = bt->left;
    }
    else
    {
        while (bt->right != NULL && ((cii *)(bt->right->e.content))->b == inHT)
            bt = bt->right;
    }
    return bt; //return end of a ht tree
}
int CmpCia(ElementType e1, ElementType e2)
{
    if (e1.t != Tci || e2.t != Tci)
        EXIT(ERROR, "error type when cii");
    return ((cii *)(e1.content))->a - ((cii *)(e2.content))->a;
}

void FindMin_HuffmanT(BTree bt, BTree *min)
{
    if (bt->t != Tcii)
    {
        EXIT(ERROR, "elementtype should be cii when findmin_huffman");
    }
    BTree pre = bt;
    *min = NULL;
    while (pre)
    {
        *min = pre;
        pre = tonext_huffmantree(pre, 0)->left;
    }
}

void ConverttoHuffmanTree(BTree *bt)
{
    if ((*bt)->t != Tci)
    {
        EXIT(ERROR, "elementtype should be ci when ConverttoHuffmanTree");
    }
    StackS stack;
    InitiateStackS(&stack, Tpointer);
    ElementType pointer;
    InitiateElement(&pointer, Tpointer);
    BTree min = NULL;
    BTree min2 = NULL;
    DeleteMinBT(bt, &min);
    DeleteMinBT(bt, &min2);
    while (min && min2)
    {
        BTree new;
        InitiateBTree(&new, Tci);
        ci cix = {'-', ((ci *)(min->e.content))->a + ((ci *)(min2->e.content))->a};
        SetValue(new->e, &cix);
        min->parent = min2->parent = new;
        OrderInsertBT_withCmp(bt, new, CmpCia);
        //store min min2
        SetValue(pointer, &min);
        PushSS(&stack, pointer);
        SetValue(pointer, &min2);
        PushSS(&stack, pointer);

        // getchar(); //debug
        DeleteMinBT(bt, &min);
        DeleteMinBT(bt, &min2);
    }
    OrderInsertBT_withCmp(bt, min, CmpCia);
    bool x = true; //right
    while (!IsEmptySS(stack))
    {
        PopSS(&stack, &pointer);
        BTree tmp;
        GetValue(pointer, &tmp);
        if (x)
        {
            tmp->parent->right = tmp;
        }
        else
        {
            tmp->parent->left = tmp;
        }
        x = !x;
    }
    PreOrderTraverse(*bt, UpdateDepthofBT);
}
