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
    (*bt)->bf = 0;
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
//AVL insert

void rotate_avl(BTree *bt, int lr)
{
    if (lr == 0)
    {
        (*bt)->bf -= (*bt)->right->bf > 0 ? (*bt)->right->bf : 0;
        (*bt)->bf--;
        if((*bt)->bf>=0) (*bt)->right->bf--;
        else (*bt)->right->bf-=(*bt)->bf;

        BTree p = (*bt)->right;

        p->parent = (*bt)->parent;
        (*bt)->parent = p;
        if(p->left)p->left->parent = (*bt);;

        (*bt)->right = p->left;
        p->left = *bt;
        (*bt) = p;
    }
    else //lr==1
    {
        (*bt)->bf -= (*bt)->left->bf < 0 ? (*bt)->left->bf : 0;
        (*bt)->bf++;
        (*bt)->left->bf += (*bt)->bf > 0 ? (*bt)->bf : 0;
        (*bt)->left->bf++;

        BTree p = (*bt)->left;

        p->parent = (*bt)->parent;
        (*bt)->parent = p;
        if(p->right)p->right->parent = (*bt);

        (*bt)->left = p->right;
        p->right = *bt;
        (*bt) = p;
    }
    PreOrderTraverse_BT(*bt, UpdateDepth_BT);
}

void update_avl(BTree bt, int lr)
{
    if (lr == 0)
    {
        bt->left->parent = bt;
        bt->left->depth = bt->depth + 1;
    }
    else
    {
        bt->right->parent = bt;
        bt->right->depth = bt->depth + 1;
    }
}
void dobalance_avl(BTree *bt)
{
    enum BF bfroot = (*bt)->bf;
    enum BF bfl = (*bt)->left ? (*bt)->left->bf : 0;
    enum BF bfr = (*bt)->right ? (*bt)->right->bf : 0;
    if (bfroot < 0)
    {
        if (bfl < 0)
            rotate_avl(bt, 1);
        else //bfl=rh
        {
            rotate_avl(&((*bt)->left), 0);
            rotate_avl(bt, 1);
        }
    }
    else
    { //bfroot==rh
        if (bfr > 0)
            rotate_avl(bt, 0);
        else
        {
            rotate_avl(&((*bt)->right), 1);
            rotate_avl(bt, 0);
        }
    }
}
void balance_avl(BTree *bt, int lr, bool *bfchanged)
{
    enum BF bfx = (*bt)->bf;
    if (bfx == EH)
    {
        (*bt)->bf = lr == 0 ? LH : RH;
        *bfchanged = true;
    }
    else
    {
        if ((bfx == RH && lr == 0) || (bfx == LH) && lr == 1)
        {
            (*bt)->bf = EH;
        }
        else
        {
            (*bt)->bf += (*bt)->bf < 0 ? -1 : 1;
            dobalance_avl(bt);
        }
        *bfchanged = false;
    }
}
void Insert_avl_BT(BTree *bt, BTree node, int (*cmp)(ElementType, ElementType), bool *bfchanged, bool *inserted)
{
    if (!(*bt))
    {
        (*bt) = node;
        *bfchanged = true;
        *inserted = true;
        return;
    }
    int r = (*cmp)((*bt)->e, node->e);
    if (r == 0)
    {
        *bfchanged = false;
        *inserted = false;
        return;
    }
    else
    {
        if (r < 0)
        {
            Insert_avl_BT(&((*bt)->right), node, (*cmp), bfchanged, inserted);
        }
        else
        {
            Insert_avl_BT(&((*bt)->left), node, (*cmp), bfchanged, inserted);
        }
        int lr = r < 0 ? 1 : 0;
        if (*inserted)
        {
            update_avl(*bt, lr);
            *inserted = false;
        }
        if (*bfchanged)
        {
            balance_avl(bt, lr, bfchanged);
        }
    }
}
void InsertElement_avl_BT(BTree *bt, ElementType e, int (*cmp)(ElementType, ElementType))
{
    BTree btc;
    InitiateBTree(&btc, e.t);
    CopyElement((btc->e), e);
    bool b = false;
    bool c = false;
    Insert_avl_BT(bt, btc, (*cmp), &b, &c);
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
void Copy_BT(BTree *copy, BTree bt)
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
//normal
void initiatecodenode_hf(codenode **c, char ch, int a)
{
    *c = (codenode *)malloc(sizeof(codenode));
    if (!(*c))
        EXIT(ERROR, "no space initiatecodenode_hf");
    initiate_codenode(*c);
    (*c)->c = ch;
    (*c)->a = a;
}
int union_pcodenode_hf(ElementType e1, ElementType e2, ElementType *u)
{
    codenode *a1, *a2;
    GetValue(e1, &a1);
    GetValue(e2, &a2);
    codenode *ux;
    initiatecodenode_hf(&ux, '-', a1->a + a2->a);
    SetValue(*u, &ux);
}
int cmp_ci_a_hf(ElementType e1, ElementType e2)
{
    if (e1.t != Tci || e2.t != Tci)
        EXIT(ERROR, "error type when cii");
    return ((cii *)(e1.content))->a - ((cii *)(e2.content))->a;
}
int cmp_pcodenode_a_hf(ElementType e1, ElementType e2)
{
    if (e1.t != Tpointer || e2.t != Tpointer)
        EXIT(ERROR, "error type when cmp_pcodenode_a_hf");
    codenode *a1, *a2;
    GetValue(e1, &a1);
    GetValue(e2, &a2);
    return a1->a - a2->a;
}
int cmp_pcodenode_c_hf(ElementType e1, ElementType e2)
{
    if (e1.t != Tpointer || e2.t != Tpointer)
        EXIT(ERROR, "error type when cmp_pcodenode_a_hf");
    codenode *a1, *a2;
    GetValue(e1, &a1);
    GetValue(e2, &a2);
    return a1->c - a2->c;
}

// code and decode
char getcharfromcode_hf(ElementType e) //used in decode
{
    codenode *cn;
    GetValue(e, &cn);
    return cn->c;
}
void getelemnfromchar_hf(char c, ElementType **e) //used in HuffmanCode
{
    if ((*e) == NULL)
    {
        (*e) = (ElementType *)malloc(sizeof(ElementType));
        if (!*e)
            EXIT(ERROR, "error getelemnfromchar_hf");
        InitiateElement(*e, Tpointer);
        codenode *cn;
        initiatecodenode_hf(&cn, c, 1);
        SetValue(**e, &cn);
    }
    else
    {
        codenode *cn;
        GetValue(**e, &cn);
        cn->c = c;
    }
}
void getcodefromchar_hf(BTree alphatree, ElementType e, char **code) //used in code HuffmanCode
{
    BTree r;
    Find_BT(alphatree, e, &r, cmp_pcodenode_c_hf);
    codenode *cn;
    GetValue(r->e, &cn);
    *code = cn->code;
}
void HuffmanDecode(BTree huffmantree, char *filename, char *outname)
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
            fprintf(out, "%c", getcharfromcode_hf(now->e));
            now = huffmantree;
        }
        c = fgetc(f);
    }
    //
    fclose(f);
    fclose(out);
}
void HuffmanCode(BTree alphatree, char *filename, char *outname)
{
    FILE *f = fopen(filename, "r");
    FILE *out = fopen(outname, "w");

    ElementType *e = NULL;
    char **cp;
    char c;
    c = fgetc(f);

    while (c != EOF)
    {
        getelemnfromchar_hf(c, &e);
        getcodefromchar_hf(alphatree, *e, cp);
        fprintf(out, "%s", *cp);
        // printf("%s",*cp);
        c = fgetc(f);
    }

    //
    fclose(f);
    fclose(out);
}

//create data struct

void copycode_hf(ElementType e, char *c, int pos) //used in constructcode
{
    codenode *cn;
    GetValue(e, &cn);
    cn->code = (char *)malloc(sizeof(char) * (pos + 1));
    if (!cn->code)
        EXIT(ERROR, "no space when constructcode");
    for (int i = 0; i < pos; i++)
    {
        *(cn->code + i) = *(c + i);
    }
    *(cn->code + pos) = '\0';
}
void constructcode(BTree huffmantree, char *c, int pos) //used in createhuffmantree
{
    if (huffmantree->left)
    {
        *(c + pos) = '0';
        constructcode(huffmantree->left, c, pos + 1);
    }
    if (huffmantree->right)
    {
        *(c + pos) = '1';
        constructcode(huffmantree->right, c, pos + 1);
    }
    if (huffmantree->left == NULL && huffmantree->right == NULL)
    {
        //leaf
        copycode_hf(huffmantree->e, c, pos);
    }
}
void converttohuffmantree_hf(BTree *bt)
{
    if ((*bt)->t != Tpointer)
    {
        EXIT(ERROR, "elementtype should be tpointer when converttohuffmantree_hf");
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
        union_pcodenode_hf(min->e, min2->e, &pointer);
        CopyElement(new->e, pointer);
        OrderInsert_BT(bt, new, cmp_pcodenode_a_hf);

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
    OrderInsert_BT(bt, min, cmp_ci_a_hf);
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
void CreateAlpabetTree(char *filename, BTree *alphabettree)
{
    FILE *f = fopen(filename, "r");
    if (!f)
        EXIT(ERROR, "open file error when CreateAlpabetTree");
    //
    char c;
    ElementType e;
    InitiateElement(&e, Tpointer); //pointer to codenode
    *alphabettree = NULL;
    c = fgetc(f);
    while (c != EOF)
    {
        // printf("%c",c);//debug
        codenode *cn;
        initiatecodenode_hf(&cn, c, 1);
        SetValue(e, &cn);
        BTree find = NULL;
        Find_BT(*alphabettree, e, &find, cmp_pcodenode_c_hf);
        if (find == NULL)
        {
            OrderInsertElement_BT(alphabettree, e, cmp_pcodenode_c_hf);
        }
        else
        {
            codenode *cn2;
            GetValue(find->e, &cn2);
            cn2->a++;
        }
        c = fgetc(f);
    }
    //
    fclose(f);
}
void CreateHuffmanTree(BTree *alphatree, BTree *huffmantree)
{
    if ((*alphatree)->t != Tpointer)
        EXIT(ERROR, "error argument CreateHuffmanTree");
    //alpatree should be contrusted //huffmantree should not be constructed
    BTree alphatree_a = NULL;
    Newstruct_BT(alphatree, &alphatree_a, cmp_pcodenode_a_hf);
    converttohuffmantree_hf(&alphatree_a);
    *huffmantree = alphatree_a;
    char cs[255];
    constructcode(*huffmantree, cs, 0);
    // PreOrderTraverse_BT(*alphatree, print_pcodenode_inBT);
}

//save to file
void SaveHuffmanTreetoFile(BTree huffman, char *filename)
{
    FILE *f = fopen(filename, "w");

    //
    fclose(f);
}
void SaveAlphaTreetoFile(BTree alphatree, char *filename)
{
    FILE *f = fopen(filename, "w");

    //inorder traverse
    BTree bt = alphatree;
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
            codenode *cn;
            GetValue(p->e, &cn);
            fprintf(f, "%d %d %s\n", cn->c, cn->a, cn->code);
            //
            p = p->right;
        }
    }
    //
    fclose(f);
}
