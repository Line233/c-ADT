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
    (*bt)->left = (*bt)->right = (*bt)->parent = NULL;
    (*bt)->t = t;
}

void OrderInsertBT(BTree *bt, ElementType e)
{
    if ((*bt) != NULL && (*bt)->t != e.t)
        EXIT(ERROR, "type different when orderInsertBT");
    BTree btc;
    InitiateBTree(&btc, e.t);
    CopyElement((btc->e), e);
    BTree pre = NULL;
    BTree *btx = bt;
    while (*btx)
    {
        pre = *btx;
        int c = CmpElement(e, (*btx)->e);
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
    *btx = btc;
    btc->parent = pre;
    if (btc->parent != NULL)
        btc->depth = btc->parent->depth + 1;
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
int CmpCiia(ElementType e1, ElementType e2)
{
    if (e1.t != Tcii || e2.t != Tcii)
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
void subDepth(BTree bt)
{
    bt->depth--;
}
void DeleteBTree_HuffmanTree(BTree *btroot, BTree delete)
{
    BTree right = (delete)->right;
    while (right && ((cii *)(right->e.content))->b == inHT)
    {
        right = right->right;
    }
    PreOrderTraverse(right, subDepth);
    if ((*btroot) == (delete))
    {
        (*btroot) = right;
    }
    else if (delete->parent->left == delete)
    {
        delete->parent->left = delete->right;
    }
    else
    {
        delete->parent->right = delete->right;
    }
    tonext_huffmantree(delete, 0)->left = NULL;
    tonext_huffmantree(delete, 1)->right = NULL;
    printf("delete\n");//debug
    PreOrderTraverse(*btroot, visit_bt2); //debug
}

void ConverttoHuffmanTree(BTree *bt)
{
    if ((*bt)->t != Tcii)
    {
        EXIT(ERROR, "elementtype should be cii when ConverttoHuffmanTree");
    }
    BTree min = NULL;
    BTree min2 = NULL;
    FindMin_HuffmanT(*bt, &min);
    DeleteBTree_HuffmanTree(bt, min);
    FindMin_HuffmanT(*bt, &min2);
    DeleteBTree_HuffmanTree(bt, min2);
    while (min && min2)
    {
        BTree new;
        InitiateBTree(&new, Tcii);
        cii ci = {'-', ((cii *)(min->e.content))->b + ((cii *)(min2->e.content))->b, notHT};
        SetValue(new->e, &ci);
        new->left = min;
        new->right = min2;
        min->parent = new;
        min2->parent = new;
        ((cii *)(min->e.content))->b = inHT;
        ((cii *)(min2->e.content))->b = inHT;
        OrderInsertBT_HuffmanT(bt, new);

        
        getchar();//debug
        FindMin_HuffmanT(*bt, &min);
        DeleteBTree_HuffmanTree(bt, min);
        FindMin_HuffmanT(*bt, &min2);
        DeleteBTree_HuffmanTree(bt, min2);
    }
}
void updateDepth(BTree bt)
{
    bt->depth = bt->parent ? bt->parent->depth + 1 : 0;
}
void OrderInsertBT_HuffmanT(BTree *bt, BTree new)
{
    if ((*bt)->t != Tcii || new->t != Tcii)
        EXIT(ERROR, "elementtype should be cii when OrderInsertBT_HuffmanT");
    BTree pre = NULL;
    BTree *now = bt;
    while (*now)
    {
        pre = *now;
        int c = CmpCiia(new->e, (*now)->e);
        if (c < 0)
        {
            now = &((tonext_huffmantree(*now, 0))->left);
        }
        else //c >= 0,insert to right
        {
            now = &((tonext_huffmantree(*now, 0))->right);
        }
    }
    if (*now == NULL)
    {
        *now = new;
        new->parent = pre;
        PreOrderTraverse(new, updateDepth);
    }
    else
    {
        EXIT(ERROR, "OrderInsertBT_HuffmanT error");
    }
    printf("insert\n");//debug
    PreOrderTraverse(*bt, visit_bt2); //debug
}