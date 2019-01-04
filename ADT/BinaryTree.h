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
    type t;
    int depth;
};

void InitiateBTree(BTree* bt,type t);
void OrderInsertBT(BTree bt,ElementType e);
void InOrderTraverse(BTree bt,void (*visit)(ElementType));
void InOrderTraverseR(BTree bt, void (*visit)(ElementType));


#endif