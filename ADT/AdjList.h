#ifndef _ADJLIST_H
#define _ADJLIST_H

#include <stdio.h>
#include "Status.h"
#include <stdbool.h>
#include "ElementType.h"
#include <stdarg.h>


typedef struct adjnode
{
    int indicate;
    ElementType info;
    struct adjnode *next;
} adjnode;
typedef struct adjhead
{
    adjnode *firstarc;
    ElementType info;
} adjhead;

typedef struct
{
    int headnum;
    int nodenum;
    type headtype;
    type nodetype;
    adjhead *heads;
} AdjList;
void Initiate_adjnode(adjnode *node, type t);
void Initiate_adjhead(adjhead *head, type t);

void Initiate_AdjList(AdjList *adjlist, int maxvexnum, type eth, type etn);
void AddNode_AdjList(AdjList *graph, int tail, int head, ElementType edgeinfo);
void Traverse_AdjList(AdjList adjlist,void (*visit)(adjhead));


#endif