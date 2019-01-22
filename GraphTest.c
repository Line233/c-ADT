#include "Graph.h"
#include "Queue.h"

void print_adjnode(adjnode a)
{
    printf("to:%d\t.", a.indicate);
    PrintElement(a.info);
    printf("\t");
}
void print_adjhead(adjhead a)
{
    printf("H:");
    PrintElement(a.info);
    printf("\t");
    for (adjnode *node = a.firstarc; node != NULL; node = node->next)
        print_adjnode(*node);
    printf("\n");
}
void printdisandpre(int *distances, int *pre, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\n", i, distances[i], pre[i]);
    }
}
void print_path(int *path, int n)
{
    for (int i = 0; i < n * n; i++)
    {
        printf("%d\t%d\t%d\n", i / n, i % n, path[i]);
    }
}
void GraphTest()
{
    //public
    FILE *f = fopen("./TestData/GraphTestData.txt", "r");
    if (!f)
        EXIT(ERROR, "open GraphTestData.txt failed");
    int n, e, tail, head, weight;
    ElementType elemh, elemn;
    InitiateElement(&elemh, Tint);
    InitiateElement(&elemn, Tint);
    AdjGraph graph;

    //test initiate
    fscanf(f, "%d", &n);
    fscanf(f, "%d", &e);
    Initiate_AdjGraph(&graph, n, undigraph, Tint, Tint);
    for (int i = 0; i < n; i++)
    {
        SetValue(elemh, &i);
        AddHead_AdjGraph(&graph, i, elemh);
    }
    for (int i = 0; i < e; i++)
    {
        fscanf(f, "%d", &tail);
        fscanf(f, "%d", &head);
        fscanf(f, "%d", &weight);
        SetValue(elemn, &weight);
        AddEdge_AdjGraph(&graph, tail, head, elemn);
    }
    TEST("dfs", 1);
    DFS_AdjGraph(graph, print_adjhead);
    TEST("bfs", 1);
    BFS_AdjGraph(graph, print_adjhead);

    //
    if (graph.type == digraph)
    {
        TEST("kosaraju:strongly connected conponnent", 1);
        AdjList adjlist;
        Initiate_AdjList(&adjlist, graph.vexs.headnum, Tnone, Tnone);
        Kosaraju(graph, adjlist);
        Traverse_AdjList(adjlist, print_adjhead);
    }
    //
    TEST("dijkstra: shortest path from one point", 1);
    int *distances = (int *)malloc(sizeof(int) * graph.vexs.headnum);
    int *pre = (int *)malloc(sizeof(int) * graph.vexs.headnum);
    Dijkstra(graph, 0, distances, pre);
    printdisandpre(distances, pre, graph.vexs.headnum);
    //
    TEST("floyd: shortest path each point", 1);
    int *path = (int *)MALLOC(sizeof(int), graph.vexs.headnum * graph.vexs.headnum, "");
    Floyd(graph, path);
    print_path(path, graph.vexs.headnum);
    //
    TEST("findkeynode", 1);
    Queue queue;
    InitiateQueue(&queue, Tint);
    FindKeyNode(graph, &queue);
    PrintQueue(queue, "");
    //
    fclose(f);
    printf("close GraphTestData.txt successfully\n");
}

int main()
{
    GraphTest();

    //
    getchar();
}