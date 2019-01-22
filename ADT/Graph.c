#include "Graph.h"
#include "Status.h"
#include <stdarg.h>
#include "Queue.h"
#include "AdjList.h"
#include "limits.h"
//private
void dfs_adjgraph_helper(AdjGraph graph, int vex, bool *visited, void (*visit)(adjhead))
{
    visited[vex] = true;
    (*visit)(graph.vexs.heads[vex]);
    for (adjnode *node = FristArc(graph, vex); node != NULL; node = node->next)
    {
        if (visited[node->indicate] == false)
            dfs_adjgraph_helper(graph, node->indicate, visited, (*visit));
    }
}
bool *getbools(int size, bool defaultb)
{
    bool *visited = (bool *)malloc(sizeof(bool) * size);
    if (!visited)
        EXIT(ERROR, "no space when getbools");
    for (int i = 0; i < size; i++)
        visited[i] = defaultb;
    return visited;
}
int dequeueint(Queue *queue)
{
    static ElementType e;
    InitiateElement(&e, Tint);
    if (IsEmptyQ(*queue) || queue->t != Tint)
        EXIT(ERROR, "type error when dequeueint");
    DeQueue(queue, &e);
    int k;
    GetValue(e, &k);
    return k;
}
int lastqueueint(Queue *queue)
{
    if (IsEmptyQ(*queue) || queue->t != Tint)
        EXIT(ERROR, "type error when dequeueint");
    int k;
    GetValue(queue->last->data, &k);
    return k;
}
void enqueueint(Queue *queue, int k)
{
    static ElementType e;
    InitiateElement(&e, Tint);
    if (queue->t != Tint)
        EXIT(ERROR, "type error when enqueueint");
    SetValue(e, &k);
    EnQueue(queue, e);
}
void kosaraju_dfs_helper_helper(AdjGraph graph, int vex, int *n, int *orders, bool *visited)
{
    visited[vex] = true;
    for (adjnode *node = FristArc(graph, vex); node != NULL; node = node->next)
    {
        if (visited[node->indicate] == false)
            kosaraju_dfs_helper_helper(graph, node->indicate, n, orders, visited);
    }
    orders[*n] = vex;
    (*n)++;
}
void kosaraju_dfs_helper(AdjGraph graph, int *orders)
{
    bool *visited = getbools(graph.vexs.headnum, false);
    int n = 0;
    for (int i = 0; i < graph.vexs.headnum; i++)
    {
        if (visited[i] == false)
        {
            kosaraju_dfs_helper_helper(graph, i, &n, orders, visited);
        }
    }
}
void kosaraju_dfs_helper_helper2(AdjGraph graph, int vex, bool *visited, AdjList adjlist, int adjgroup)
{
    visited[vex] = true;
    ElementType e;
    InitiateElement(&e, Tnone);
    AddNode_AdjList(&adjlist, adjgroup, vex, e);
    for (adjnode *node = FristArc(graph, vex); node != NULL; node = node->next)
    {
        if (visited[node->indicate] == false)
            kosaraju_dfs_helper_helper2(graph, node->indicate, visited, adjlist, adjgroup);
    }
}
void kosaraju_dfs_helper2(AdjGraph graph, AdjList adjlist, int *order)
{
    bool *visited = getbools(graph.vexs.headnum, false);
    int n = 0;
    int adjgroup = 0;
    for (int i = graph.vexs.headnum - 1; i >= 0; i--)
    {
        int vex = order[i];
        if (visited[vex] == false)
        {
            kosaraju_dfs_helper_helper2(graph, vex, visited, adjlist, adjgroup);
            adjgroup++;
        }
    }
}
void trasport_graph(AdjGraph *graph, AdjGraph graphold)
{
    if (graphold.type != digraph)
        EXIT(ERROR, "when trasport_graph");
    Initiate_AdjGraph(graph, graphold.vexs.headnum, graphold.type, graphold.vexs.headnum, graphold.vexs.nodetype);
    for (int i = 0; i < graphold.vexs.headnum; i++)
    {
        adjnode *node = FristArc(graphold, i);
        while (node)
        {
            AddEdge_AdjGraph(graph, node->indicate, i, node->info);
            node = node->next;
        }
    }
}
int findmin(int *array, int n, bool *completed) //in Dijkstra
{
    int min = INT_MAX;
    int mini = INT_MAX;
    for (int i = 0; i < n; i++)
    {
        if ((min > array[i]) && completed[i] == false)
        {
            min = array[i];
            mini = i;
        }
    }
    return mini;
}
int getweight(ElementType e)
{
    if (e.t != Tint)
        EXIT(ERROR, "when getwight");
    int k;
    GetValue(e, &k);
    return k;
}
int getindex(int i, int j, int size)
{
    return i * size + j;
}
int geti(int index, int size)
{
    return index / size;
}
int getj(int index, int size)
{
    return index % size;
}
//pubulic

void Initiate_AdjGraph(AdjGraph *graph, int maxvexnum, graphtype gt, type eth, type etn)
{
    Initiate_AdjList(&graph->vexs, maxvexnum, eth, etn);
    graph->type = gt;
}
void AddEdge_AdjGraph(AdjGraph *graph, int tail, int head, ElementType edgeinfo)
{
    if (edgeinfo.t != graph->vexs.nodetype)
        EXIT(ERROR, "error type");
    AddNode_AdjList(&graph->vexs, tail, head, edgeinfo);
    if (graph->type == undigraph)
    {
        AddNode_AdjList(&graph->vexs, head, tail, edgeinfo);
        graph->vexs.nodenum--;
    }
}
void AddHead_AdjGraph(AdjGraph *graph, int vex, ElementType headinfo)
{
    if (headinfo.t != graph->vexs.headtype)
        EXIT(ERROR, "error type when AddHead_AdjGraph");
    CopyElement(graph->vexs.heads[vex].info, headinfo);
}

void DFS_AdjGraph(AdjGraph graph, void (*visit)(adjhead))
{
    bool *visited = getbools(graph.vexs.headnum, false);
    for (int i = 0; i < graph.vexs.headnum; i++)
    {
        if (visited[i] == false)
        {
            dfs_adjgraph_helper(graph, i, visited, (*visit));
        }
    }
}
void BFS_AdjGraph(AdjGraph graph, void (*visit)(adjhead))
{
    bool *visited = getbools(graph.vexs.headnum, false);
    Queue queue;
    InitiateQueue(&queue, Tint);
    ElementType elem;
    InitiateElement(&elem, Tint);
    for (int i = 0; i < graph.vexs.headnum; i++)
    {
        if (visited[i] == false)
        {
            enqueueint(&queue, i); //root
            visited[i] = true;
            while (!IsEmptyQ(queue))
            {
                int k = dequeueint(&queue);
                (*visit)(graph.vexs.heads[k]);
                for (adjnode *node = FristArc(graph, k); node; node = node->next)
                {
                    if (visited[node->indicate] == false)
                    {
                        enqueueint(&queue, node->indicate);
                        visited[node->indicate] = true;
                    }
                }
            }
        }
    }
}

adjnode *FristArc(AdjGraph graph, int vex)
{
    return graph.vexs.heads[vex].firstarc;
}

//for digraph
void Kosaraju(AdjGraph graph, AdjList adjlist) //find strongly connected conponent
{
    if (graph.type != digraph || adjlist.headtype != Tnone || adjlist.nodetype != Tnone || adjlist.headnum != graph.vexs.headnum)
        EXIT(ERROR, "when Kosaraju");
    int *order = (int *)malloc(sizeof(int) * graph.vexs.headnum);
    if (!order)
        EXIT(ERROR, "no space when Kosaraju");
    //dfs
    bool *visited = getbools(graph.vexs.headnum, false);
    kosaraju_dfs_helper(graph, order);
    AdjGraph grapht;
    trasport_graph(&grapht, graph);
    kosaraju_dfs_helper2(grapht, adjlist, order);
}

void Dijkstra(AdjGraph graph, int vex, int *distances, int *pre)
{
    bool *completed = (bool *)getbools(graph.vexs.headnum, false);
    for (int i = 0; i < graph.vexs.headnum; i++)
    {
        distances[i] = INT_MAX;
        pre[i] = -1;
    }
    adjnode *node = FristArc(graph, vex);
    while (node)
    {
        distances[node->indicate] = getweight(node->info);
        pre[node->indicate] = vex;
        node = node->next;
    }
    distances[vex] = 0;
    pre[vex] = vex;
    completed[vex] = true;
    for (int i = 0; i < graph.vexs.headnum - 1; i++)
    {
        int k = findmin(distances, graph.vexs.headnum, completed);
        if (k == INT_MAX)
            break;
        completed[k] = true;
        for (node = FristArc(graph, k); node; node = node->next)
        {
            if (completed[node->indicate] == false)
            {
                if (distances[node->indicate] > distances[k] + getweight(node->info))
                {
                    distances[node->indicate] = distances[k] + getweight(node->info);
                    pre[node->indicate] = k;
                }
            }
        }
    }
}

void Floyd(AdjGraph graph, int *path)
{
    IntiateIntArray(path, graph.vexs.headnum * graph.vexs.headnum, INT_MAX);
    int n = graph.vexs.headnum;
    int n2 = n * n;
    int i, j, u;
    for (i = 0; i < n; i++)
    {
        adjnode *node = FristArc(graph, i);
        while (node)
        {
            int k = getindex(i, node->indicate, n);
            path[k] = getweight(node->info);
            node = node->next;
        }
    }
    for (int c = 0; c < n; c++)
    {
        int k = getindex(c, c, n);
        path[k] = 0;
    }
    for (u = 0; u < graph.vexs.headnum; u++)
    {
        for (i = 0; i < graph.vexs.headnum; i++)
        {
            for (j = 0; j < graph.vexs.headnum; j++)
            {
                int k = getindex(i, j, n);
                int k2 = getindex(i, u, n);
                int k3 = getindex(u, j, n);
                if (path[k] > path[k2] + path[k3])
                {
                    path[k] = path[k2] + path[k3];
                }
            }
        }
    }
}

void dfs_findkeynode_helper(AdjGraph graph, int vex, int *n, int *visited, int *low, int last)
{
    printf("aa%d\t%d\n", vex, last);
    low[vex] = visited[vex] = *n;
    (*n)++;
    for (adjnode *node = FristArc(graph, vex); node != NULL; node = node->next)
    {
        if (visited[node->indicate] == -1)
        {
            // low[node->indicate] = visited[vex];
            dfs_findkeynode_helper(graph, node->indicate, n, visited, low, vex);
            if (low[vex] > low[node->indicate])
                low[vex] = low[node->indicate];
        }
        else //return edge
        {
            if (node->indicate != last)
            {
                if (low[vex] > visited[node->indicate]) //low[vex] equal visited[parent] early
                    low[vex] = visited[node->indicate];
            }
        }
    }
}
void dfs_findkeynode_helper2(AdjGraph graph, int vex, int *visited, int *low, Queue *queue, bool *visitedbool)
{
    visitedbool[vex] = true;
    bool iskeynode = false;
    for (adjnode *node = FristArc(graph, vex); node != NULL; node = node->next)
    {
        if (visitedbool[node->indicate] == false)
        {
            // low[node->indicate] = visited[vex];
            dfs_findkeynode_helper2(graph, node->indicate, visited, low, queue, visitedbool);
            if (visited[vex] <= low[node->indicate] && !iskeynode)
            {
                enqueueint(queue, vex);
                iskeynode = true;
            }
        }
    }
}

void FindKeyNode(AdjGraph graph, Queue *queue)
{
    int *visited = (int *)MALLOC(sizeof(int), graph.vexs.headnum, "");
    IntiateIntArray(visited, graph.vexs.headnum, -1);
    int *low = (int *)MALLOC(sizeof(int), graph.vexs.headnum, "");
    for (int i = 0; i < graph.vexs.headnum; i++)
    {
        if (visited[i] == -1)
        {
            int n = 0;
            dfs_findkeynode_helper(graph, i, &n, visited, low, 0);
        }
    }
    for (int i = 0; i < graph.vexs.headnum; i++)
    {
        printf("%d\t%d\t%d\n", i, visited[i], low[i]);
    }
    bool *visitedbool = getbools(graph.vexs.headnum, false);
    for (int i = 0; i < graph.vexs.headnum; i++)
    {
        if (visitedbool[i] == false)
        {
            visitedbool[i] = true;
            bool iskeynode = false;
            int edgenum = 0;
            for (adjnode *node = FristArc(graph, i); node != NULL; node = node->next)
            {
                if (visitedbool[node->indicate] == false)
                {
                    // low[node->indicate] = visited[vex];
                    dfs_findkeynode_helper2(graph, node->indicate, visited, low, queue, visitedbool);
                    edgenum++;
                    if ((edgenum > 1 || visited[i] <= low[node->indicate]) && !iskeynode)
                    {
                        enqueueint(queue, i);
                        iskeynode = true;
                    }
                }
            }
        }
    }
}