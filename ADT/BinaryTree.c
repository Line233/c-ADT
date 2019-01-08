#include "BinaryTree.h"
#include <malloc.h>
#include "StackS.h"
#include "Queue.h"
#include "StaticList.h"

//insert
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
void CreateBTree(BTree *bt, ElementType e)
{
    InitiateBTree(bt, e.t);
    CopyElement((*bt)->e, e);
}
//insert
void OrderInsert_BT(BTree *bt, BTree node, int (*cmp)(ElementType, ElementType))
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
void OrderInsertElement_BT(BTree *bt, ElementType e, int (*cmp)(ElementType, ElementType))
{
    BTree btc;
    InitiateBTree(&btc, e.t);
    CopyElement((btc->e), e);
    OrderInsert_BT(bt, btc, (*cmp));
}

//traverse
void LevelOrderTraverse_BT(BTree bt, void (*visit)(BTree), int orient)
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
        else
        {
            break;
        }
        // PrintQueue(queue, "dequeue"); //debug
    }
}
void InOrderTraverse_BT(BTree bt, void (*visit)(BTree))
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
void PreOrderTraverse_BT(BTree bt, void (*visit)(BTree))
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
void PostOrderTraverse_BT(BTree bt, void (*visit)(BTree))
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
void InOrderTraverse_BT_R(BTree bt, void (*visit)(BTree))
{
    if (bt == NULL)
        return;
    else
    {
        InOrderTraverse_BT_R(bt->left, (*visit));
        (*visit)(bt);
        InOrderTraverse_BT_R(bt->right, (*visit));
    }
    printf("\n");
}
//find
void Find_BT(BTree bt, ElementType e, BTree *result, int (*cmp)(ElementType, ElementType))
{
    if (bt != NULL && bt->t != e.t)
        EXIT(ERROR, "type different when Find_BT");
    while (bt)
    {
        int c = (*cmp)(e, bt->e);
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

void FindMin_BT(BTree bt, BTree *min)
{
    *min = bt;
    while (*min && (*min)->left)
    {
        *min = (*min)->left;
    }
}
//delete
void DeleteMin_BT(BTree *bt, BTree *min)
{
    if ((*bt) == NULL)
    {
        (*min) = (*bt);
        return;
    }
    FindMin_BT(*bt, min);
    BTree *pbt = (*min)->parent ? ((*min)->parent->left == (*min) ? &((*min)->parent->left)
                                                                  : &((*min)->parent->right))
                                : bt;
    *pbt = (*min)->right;
    //updata *pbt
    if (*pbt)
    {
        (*pbt)->parent = (*min)->parent;
        PreOrderTraverse_BT((*pbt), UpdateDepth_BT);
    }
    //update *min
    (*min)->left = NULL;
    (*min)->right = NULL;
    (*min)->depth = 0;
}
//copy
void Copy(BTree *copy, BTree bt)
{
    CreateBTree(copy, bt->e);
}
//normal
void Newstruct_BT(BTree *old, BTree *new, int (*newcmp)(ElementType, ElementType))
{
    //PreOrderTraverse
    BTree bt = *old;
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
        // (*visit)(p);
        //insert
        OrderInsertElement_BT(new, p->e, newcmp);
        //
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
void UpdateDepth_BT(BTree bt)
{
    if (!bt)
        EXIT(ERROR, "null error when UpdateDepth_BT");
    bt->depth = bt->parent ? bt->parent->depth + 1 : 0;
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

//huffmantree
#include <CII.h>
int Cmp_ci_a(ElementType e1, ElementType e2)
{
    if (e1.t != Tci || e2.t != Tci)
        EXIT(ERROR, "error type when cii");
    return ((cii *)(e1.content))->a - ((cii *)(e2.content))->a;
}
void ConverttoHuffmanTree(BTree *bt)
{
    if ((*bt)->t != Tpointer)
    {
        EXIT(ERROR, "elementtype should be tpointer when ConverttoHuffmanTree");
    }
    StackS stack;
    InitiateStackS(&stack, Tpointer);
    ElementType pointer;
    InitiateElement(&pointer, Tpointer);
    BTree min = NULL;
    BTree min2 = NULL;
    DeleteMin_BT(bt, &min);
    DeleteMin_BT(bt, &min2);
    while (min && min2)
    {
        BTree new;
        InitiateBTree(&new, Tpointer);
        //now codenodt
        union_pcodenode(min->e, min2->e, &pointer);
        CopyElement(new->e, pointer);
        OrderInsert_BT(bt, new, cmp_pcodenode_a);

        min->parent = min2->parent = new;
        //store min min2
        SetValue(pointer, &min);
        PushSS(&stack, pointer);
        SetValue(pointer, &min2);
        PushSS(&stack, pointer);

        // getchar(); //debug
        DeleteMin_BT(bt, &min);
        DeleteMin_BT(bt, &min2);
    }
    OrderInsert_BT(bt, min, Cmp_ci_a);
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
    PreOrderTraverse_BT(*bt, UpdateDepth_BT);
}
int cmp_pcodenode_a(ElementType e1, ElementType e2)
{
    if (e1.t != Tpointer || e2.t != Tpointer)
        EXIT(ERROR, "error type when cmp_pcodenode_a");
    codenode *a1, *a2;
    GetValue(e1, &a1);
    GetValue(e2, &a2);
    return a1->a - a2->a;
}
int cmp_pcodenode_c(ElementType e1, ElementType e2)
{
    if (e1.t != Tpointer || e2.t != Tpointer)
        EXIT(ERROR, "error type when cmp_pcodenode_a");
    codenode *a1, *a2;
    GetValue(e1, &a1);
    GetValue(e2, &a2);
    return a1->c - a2->c;
}
int add_pcodenode_a(ElementType e1, ElementType e2)
{
    if (e1.t != Tpointer || e2.t != Tpointer)
        EXIT(ERROR, "error type when cmp_pcodenode_a");
    codenode *a1, *a2;
    GetValue(e1, &a1);
    GetValue(e2, &a2);
    return a1->a + a2->a;
}
int union_pcodenode(ElementType e1, ElementType e2, ElementType *u)
{
    codenode *a1, *a2;
    GetValue(e1, &a1);
    GetValue(e2, &a2);
    codenode *ux;
    newcodenode(&ux, '-', a1->a + a2->a);
    SetValue(*u, &ux);
}
void newcodenode(codenode **c, char ch, int a)
{
    *c = (codenode *)malloc(sizeof(codenode));
    if (!(*c))
        EXIT(ERROR, "no space newcodenode");
    initiate_codenode(*c);
    (*c)->c = ch;
    (*c)->a = a;
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
void fullcode(ElementType e, char *c, int pos)
{
    codenode *cn;
    GetValue(e, &cn);
    cn->code = (char *)malloc(sizeof(char) * (pos + 1));
    if (!cn->code)
        EXIT(ERROR, "no space when GetCodefromHuffmanTree");
    for (int i = 0; i < pos; i++)
    {
        *(cn->code + i) = *(c + i);
    }
    *(cn->code + pos) = '\0';
}
void newelem(char c, ElementType **e)
{
    if ((*e) == NULL)
    {
        (*e) = (ElementType *)malloc(sizeof(ElementType));
        if (!*e)
            EXIT(ERROR, "error newelem");
        InitiateElement(*e, Tpointer);
        codenode *cn;
        newcodenode(&cn, c, 1);
        SetValue(**e, &cn);
    }
    else
    {
        codenode *cn;
        GetValue(**e, &cn);
        cn->c = c;
    }
}
void GetCodefromHuffmanTree(BTree huffmantree, char *c, int pos)
{
    if (huffmantree->left)
    {
        *(c + pos) = '0';
        GetCodefromHuffmanTree(huffmantree->left, c, pos + 1);
    }
    if (huffmantree->right)
    {
        *(c + pos) = '1';
        GetCodefromHuffmanTree(huffmantree->right, c, pos + 1);
    }
    if (huffmantree->left == NULL && huffmantree->right == NULL)
    {
        //leaf
        fullcode(huffmantree->e, c, pos);
    }
}
void ConstructHuffmantree(BTree *alphatree, BTree *huffmantree)
{
    if ((*alphatree)->t != Tpointer)
        EXIT(ERROR, "error argument ConstructHuffmantree");
    //alpatree should be contrusted //huffmantree should not be constructed
    BTree alphatree_a = NULL;
    Newstruct_BT(alphatree, &alphatree_a, cmp_pcodenode_a);
    // printf("alphatree_a\n");                               //debug
    // InOrderTraverse_BT(alphatree_a, print_pcodenode_inBT); //debug
    // ConverttoHuffmanTree(&alphatree_a);
    ConverttoHuffmanTree(&alphatree_a);
    // printf("huffman tree is\n");                                 //debug
    // LevelOrderTraverse_BT(alphatree_a, print_pcodenode_inBT, 1); //debug
    *huffmantree = alphatree_a;
    char cs[255];
    GetCodefromHuffmanTree(*huffmantree, cs, 0);
    // printf("huffman tree is\n");                                 //debug
    // LevelOrderTraverse_BT(alphatree_a, print_pcodenode_inBT, 1); //debug
    PreOrderTraverse_BT(*alphatree, print_pcodenode_inBT);
}
void FindCode(BTree alphatree, ElementType e, char **code)
{
    BTree r;
    Find_BT(alphatree, e, &r, cmp_pcodenode_c);
    codenode *cn;
    GetValue(r->e, &cn);
    *code = cn->code;
}

void coding(BTree alphatree, char *filename, char *outname)
{
    FILE *f = fopen(filename, "r");
    FILE *out = fopen(outname, "w");

    ElementType *e = NULL;
    char **cp;
    char c;
    c = fgetc(f);

    while (c != EOF)
    {
        newelem(c, &e);
        FindCode(alphatree, *e, cp);
        fprintf(out, "%s", *cp);
        // printf("%s",*cp);
        c = fgetc(f);
    }

    //
    fclose(f);
    fclose(out);
}
char getchar_inE(ElementType e)
{
    codenode *cn;
    GetValue(e, &cn);
    return cn->c;
}
void decode(BTree huffmantree, char *filename, char *outname)
{
    FILE *f = fopen(filename, "r");
    FILE *out = fopen(outname, "w");
    //
    BTree now = huffmantree;
    char c;
    c = fgetc(f);
    while (c != EOF)
    {
        if (c == '0')
        {
            now = now->left;
        }
        else
        {
            now = now->right;
        }
        if (now->left == now->right && now->left == NULL)
        {
            fprintf(out, "%c", getchar_inE(now->e));
            // printf("%c", getchar_inE(now->e));
            now = huffmantree;
        }
        c = fgetc(f);
    }
    //
    fclose(f);
    fclose(out);
}
void print_HuffmanTree(BTree huffman, char *filename)
{
    FILE *f = fopen(filename, "w");

    //
    fclose(f);
}
void print_AlphaTree(BTree alphatree, char *filename)
{
    FILE *f = fopen(filename, "w");
    
    //inorder traverse
    BTree bt=alphatree;
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
            // (*visit)(p);
            //visit
            codenode* cn;
            GetValue(p->e,&cn);
            fprintf(f,"%d %d %s\n",cn->c,cn->a,cn->code);
            //
            p = p->right;
        }
    }

    //
    fclose(f);
}