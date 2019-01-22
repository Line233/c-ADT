#include"AdjList.h"
#include"ElementType.h"

void Initiate_adjnode(adjnode *node, type t)
{
    node->indicate = 0;
    InitiateElement(&(node->info), t);
    node->next = NULL;
}
void Initiate_adjhead(adjhead *head, type t)
{
    head->firstarc = NULL;
    InitiateElement(&(head->info), t);
}

void Initiate_AdjList(AdjList* adjlist, int maxvexnum, type eth, type etn)
{
    adjlist->heads = (adjhead *)malloc(sizeof(adjhead) * maxvexnum);
    if (!adjlist->heads)
        EXIT(ERROR, "no space when Initiate_AdjGraph");
    for (int i = 0; i < maxvexnum; i++)
        Initiate_adjhead(adjlist->heads + i, eth);
    adjlist->headnum = maxvexnum;
    adjlist->nodenum = 0;
    adjlist->headtype = eth;
    adjlist->nodetype = etn;
}
void AddNode_AdjList(AdjList *graph, int tail, int head, ElementType edgeinfo)
{
    if (edgeinfo.t != graph->nodetype)
        EXIT(ERROR, "error type");
    adjnode *node = (adjnode *)malloc(sizeof(adjnode));
    if (!node)
        EXIT(ERROR, "no space when AddEdge_AdjGraph");
    Initiate_adjnode(node, graph->nodetype);
    CopyElement(node->info, edgeinfo);
    node->next = (graph->heads + tail)->firstarc;
    node->indicate = head;
    (graph->heads + tail)->firstarc = node;
    graph->nodenum++;
}
void Traverse_AdjList(AdjList adjlist,void (*visit)(adjhead))
{
    for(int i=0;i<adjlist.headnum;i++)
    {
        (*visit)(adjlist.heads[i]);
    }
}