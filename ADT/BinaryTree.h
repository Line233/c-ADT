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
void Copy_BT(BTree *copy, BTree bt);
//normal
void Newstruct_BT(BTree *old, BTree *new, int (*newcmp)(ElementType, ElementType));
void UpdateDepth_BT(BTree bt);
void CreateInorderBT(BTree *bt, ElementType **es, int *n, int depth);


//huffmancode
//code and decode
void HuffmanCode(BTree alphatree, char *filename, char *outname);
void HuffmanDecode(BTree huffmantree, char *filename, char *outname);
//create data struct
void CreateHuffmanTree(BTree *alphatree, BTree *huffmantree);
void CreateAlpabetTree(char* filename,BTree* alphabettree);
//save data struct
void SaveAlphaTreetoFile(BTree alphatree, char *filename);
void SaveHuffmanTreetoFile(BTree huffman, char *filename);

#endif