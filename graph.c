#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

void initializeGraph(GRAPH* graph, _Bool direction, int nNodes, int nEdges)
{
    graph->nNodes = nNodes;
    graph->nEdges = nEdges;
    graph->isDirected = direction;

    graph->degree = malloc(sizeof(struct edgenode*)* (nNodes+1));
    graph->edges = malloc(sizeof(int) * (nNodes+1));
    for(int i = 1; i <= nNodes; i++) graph->degree[i] = 0;
    for(int i = 1; i <= nNodes; i++) graph->edges[i] = NULL;
}

void readGraphKeyboard(GRAPH* graph, _Bool directed)
{


    int x, y; //ребро від .. до ..

    printf("number of nodes: ");
    int nNodes;
    scanf("%d", &nNodes);

    printf("number of edges: ");
    int nEdges;
    scanf("%d", &nEdges);
    fflush(stdin);

    initializeGraph(graph, directed, nNodes, nEdges);

    for(int i = 1, n = graph->nEdges; i <= n; i++)
    {
        printf("x y: ");
        scanf("%d %d", &x, &y);
        fflush(stdin);
        insertEdge(graph, x, y, directed);
    }
}
void readGraphFile(GRAPH* graph, _Bool directed)
{
    /*
    printf("name of file: ");
    char nameOfFile[51];
    gets(nameOfFile);
    fflush(stdin);


    ///////////////////відкрити файл//////////////////
    FILE* file;
    if( (file = fopen(nameOfFile, "rt") ) == NULL)
    {
        puts("Error: can't open the file.");
        return;
    }


    ///////////////////опрацювати файл//////////////////
    const SIZE = 11;
    char buff[SIZE];
    //кількість вузлів
    fgets(buff, SIZE, file);
    int nNodes = (int)atoi(buff);
    //кількість ребер


    //зчитати ребра


    ////////////////////закрити файл/////////////////////
    fclose(file);*/
}

void insertEdge(GRAPH* graph, int x, int y, _Bool directed)
{
    EDGENODE* edge;
    edge = malloc(sizeof(EDGENODE));
    if(edge == NULL)
        exit(400);

    edge->y = y;
    edge->next = graph->edges[x];//стає початком
    edge->discovered = 0;

    graph->edges[x] = edge;
    (graph->degree[x])++;//степінь вузла (кількість

    if(directed == 0)
        insertEdge(graph, y, x, 1);
    else
        graph->nEdges++;
}
void printGraph(GRAPH* graph)
{
    EDGENODE* edge;
    for(int i = 1; i <= graph->nNodes; i++)
    {
        printf("%d: ", i);
        edge = graph->edges[i];
        while(edge != NULL)
        {
            printf(" %d", edge->y);
            edge = edge->next;
        }

        printf("\n");
    }

}
void setGraph(GRAPH* graph, _Bool directed)
{
    initializeGraph(graph, directed, 4, 4);

    graph->nNodes = 4;
    graph->nEdges = 4;

    insertEdge(graph, 1, 2, directed);
    insertEdge(graph, 2, 3, directed);
    insertEdge(graph, 3, 4, directed);
    insertEdge(graph, 4, 1, directed);
}
void setHardWay(GRAPH* graph, _Bool directed)
{
    initializeGraph(graph, directed, 5, 8);

    insertEdge(graph, 1, 2, directed);
    insertEdge(graph, 2, 3, directed);
    insertEdge(graph, 3, 4, directed);
    insertEdge(graph, 4, 1, directed);
    insertEdge(graph, 1, 3, directed);
    insertEdge(graph, 3, 5, directed);
    insertEdge(graph, 5, 4, directed);
    insertEdge(graph, 4, 2, directed);

//    5
//    8
//    1 2
//    2 3
//    3 4
//    4 1
//    1 3
//    3 5
//    5 4
//    4 2

}
void clearGraph(GRAPH* graph)
{
    free(graph->degree);
    for(int i = 1; i <= graph->nNodes; i++)
    {
        EDGENODE* node = graph->edges[i];
        for(EDGENODE *del; node != NULL;)
        {
            del = node;
            node = node->next;
            free(del);
        }
    }
    free(graph->edges);
}