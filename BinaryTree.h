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
    int depth;
};

void InitiateBTree(BTree* bt,ElementType e);
void OrderInsertBT(BTree bt,ElementType e);
void PrintBTree(BTree bt);


#endif