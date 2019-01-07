//status
#ifndef _BINARYTREE_H
#define _BINARYTREE_H

#include "Status.h"
#include "ElementType.h"

typedef struct btree *BTree;
struct btree
{
    ElementType e;
    BTree left;
    BTree right;
    BTree parent;
    type t;
    int depth;
};
void InitiateBTree(BTree *bt, type t);
void OrderInsertBT(BTree* bt, ElementType e);
void InOrderTraverse(BTree bt, void (*visit)(BTree));
void InOrderTraverseR(BTree bt, void (*visit)(BTree));
void PostOrderTraverse(BTree bt, void (*visit)(BTree));
void PreOrderTraverse(BTree bt, void (*visit)(BTree));
void CreateInorderBT(BTree *bt, ElementType **es, int *n, int depth);
void FindinBTree(BTree bt, ElementType e, BTree *result);
void LevelOrderTraverse(BTree bt, void (*visit)(BTree),int orient);


void ConvertBinaryTreeNewCmp(BTree* old,BTree* new,int (*newcmp)(ElementType,ElementType));
void DeleteMinBT(BTree* bt,BTree* min);
void FindMinBT(BTree bt,BTree* min);
void UpdateDepthofBT(BTree bt);
void OrderInsertBT_withCmp(BTree *bt, BTree node, int (*cmp)(ElementType, ElementType));
void OrderInsertElementBT_withCmp(BTree *bt, ElementType e, int (*cmp)(ElementType, ElementType));


//to huffman
#define inHT 0
#define notHT 1
void ConverttoHuffmanTree(BTree *bt);
void FindMin_HuffmanT(BTree bt, BTree *min);
void OrderInsertBT_HuffmanT(BTree *bt, BTree new);

int CmpCia(ElementType e1, ElementType e2);
#endif