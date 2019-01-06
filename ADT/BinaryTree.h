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

//to huffman
#define inHT 0
#define notHT 1
void ConverttoHuffmanTree(BTree *bt);
void FindMin_HuffmanT(BTree bt, BTree *min);
void OrderInsertBT_HuffmanT(BTree *bt, BTree new);
#endif