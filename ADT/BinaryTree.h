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
void CreateBTree(BTree *bt, ElementType e);

//insert
void OrderInsertElement_BT(BTree *bt, ElementType e, int(*cmp)(ElementType, ElementType));
void OrderInsert_BT(BTree *bt, BTree node, int (*cmp)(ElementType, ElementType));
//traverse
void InOrderTraverse_BT(BTree bt, void (*visit)(BTree));
void InOrderTraverse_BT_R(BTree bt, void (*visit)(BTree));
void PostOrderTraverse_BT(BTree bt, void (*visit)(BTree));
void PreOrderTraverse_BT(BTree bt, void (*visit)(BTree));
void LevelOrderTraverse_BT(BTree bt, void (*visit)(BTree), int orient);
//find
void Find_BT(BTree bt, ElementType e, BTree *result,int (*cmp)(ElementType,ElementType));
void FindMin_BT(BTree bt, BTree *min);
//delete
void DeleteMin_BT(BTree *bt, BTree *min);
//copy
void Copy(BTree *copy, BTree bt);
//normal
void Newstruct_BT(BTree *old, BTree *new, int (*newcmp)(ElementType, ElementType));
void UpdateDepth_BT(BTree bt);
void CreateInorderBT(BTree *bt, ElementType **es, int *n, int depth);

//to huffman
int Cmp_ci_a(ElementType e1, ElementType e2);
void ConverttoHuffmanTree(BTree *bt);
//
int cmp_pcodenode_a(ElementType e1,ElementType e2);
int cmp_pcodenode_c(ElementType e1,ElementType e2);
int add_pcodenode_a(ElementType e1,ElementType e2);

void ConstructHuffmantree(BTree *alphatree, BTree *huffmantree);
void newcodenode(codenode **c, char ch, int a);
void print_pcodenode_inBT(BTree bt);
void coding(BTree alphatree, char *filename, char *outname);
void decode(BTree huffmantree, char *filename, char *outname);
void print_AlphaTree(BTree alphatree, char *filename);

#endif