#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


#define MAXV 1000

typedef struct edgenode {
    int y;
    struct edgenode *next;
} EDGENODE;

typedef struct graph {
    struct edgenode *edges[MAXV+1]; //ребра
    int degree[MAXV+1]; // степінь вершини
    int nNodes; //кількість вузлів
    int nEdges; //кількість ребер
    _Bool isDirected; //орієнтований
} GRAPH;


void initializeGraph(GRAPH* graph, _Bool direction);

void readGraph(GRAPH* graph, _Bool directed);

void insertEdge(GRAPH* graph, int x, int y, _Bool directed);
void printGraph(GRAPH* graph);

int main()
{
    GRAPH graph;
    readGraph(&graph, 0);

    printGraph(&graph);

    //initialize_search(&graph);
    //dfs(&graph, 1);

    //start_search(&graph);

    puts("");
    system("pause");
    return 0;
}



void initializeGraph(GRAPH* graph, _Bool direction)
{
    graph->nNodes = 0;
    graph->nEdges = 0;
    graph->isDirected = direction;
    for(int i = 1; i <= MAXV; i++) graph->degree[i] = 0;
    for(int i = 1; i <= MAXV; i++) graph->edges[i] = NULL;
}

void readGraph(GRAPH* graph, _Bool directed)
{
    initializeGraph(graph, directed);

    //кільеість ребер
    int x, y; //ребро від .. до ..

    printf("number of nodes: ");
    scanf("%d", &(graph->nNodes));
    printf("number of edges: ");
    scanf("%d", &(graph->nEdges));
    fflush(stdin);

    for(int i = 1, n = graph->nEdges; i <= n; i++)
    {
        printf("x y: ");
        scanf("%d %d", &x, &y);
        fflush(stdin);
        insertEdge(graph, x, y, directed);
    }
}

void insertEdge(GRAPH* graph, int x, int y, _Bool directed)
{
    EDGENODE* edge;
    edge = malloc(sizeof(EDGENODE));
    if(edge == NULL)
        exit(400);

    edge->y = y;
    edge->next = graph->edges[x];//стає початком

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