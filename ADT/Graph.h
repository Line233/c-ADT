//status
#ifndef _GRAPH_H
#define _GRAPH_H

#include <stdio.h>
#include "Status.h"
#include <stdbool.h>
#include "ElementType.h"
#include <stdarg.h>
#include "AdjList.h"
#include"Queue.h"

typedef enum
{
    digraph,
    undigraph
} graphtype;
typedef struct
{
    graphtype type;
    AdjList vexs;
} AdjGraph;

void Initiate_adjnode(adjnode *node, type t);
void Initiate_adjhead(adjhead *head, type t);

void Initiate_AdjGraph(AdjGraph *graph, int maxvexnum, graphtype gt, type eth, type etn);
void AddEdge_AdjGraph(AdjGraph *graph, int tail, int head, ElementType edgeinfo);
void AddHead_AdjGraph(AdjGraph *graph, int vex, ElementType headinfo);

void DFS_AdjGraph(AdjGraph graph, void (*visit)(adjhead));
void BFS_AdjGraph(AdjGraph graph, void (*visit)(adjhead));
adjnode *FristArc(AdjGraph graph, int vex);

void Kosaraju(AdjGraph graph, AdjList adjlist); //find strongly connected conponent
void Dijkstra(AdjGraph graph, int vex, int *distances, int *pre);

void Floyd(AdjGraph graph, int *path);

void FindKeyNode(AdjGraph graph, Queue *queue);

#endif