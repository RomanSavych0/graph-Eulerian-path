#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>



#define MAXV 50

typedef struct edgenode {
    int y;
    _Bool discovered;
    struct edgenode *next;
} EDGENODE;

typedef struct graph {
    struct edgenode *edges[MAXV+1]; //ребра
    int degree[MAXV+1]; // степінь вершини
    int nNodes; //кількість вузлів
    int nEdges; //кількість ребер
    _Bool isDirected; //орієнтований
} GRAPH;


void initializeGraph(GRAPH*, _Bool);
void readGraph(GRAPH*, _Bool);
void insertEdge(GRAPH*, int, int, _Bool);
void printGraph(GRAPH*);
void setGraph(GRAPH* graph, _Bool);

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


    printf("number of nodes: ");
    int nNodes;
    scanf("%d", &nNodes);

    printf("number of edges: ");
    int nEdges;
    scanf("%d", &nEdges);
    fflush(stdin);

    initializeGraph(graph, directed);

    //кільеість ребер
    int x, y; //ребро від .. до ..

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
    initializeGraph(graph, directed);

    graph->nNodes = 4;
    graph->nEdges = 4;

    insertEdge(graph, 1, 2, directed);
    insertEdge(graph, 2, 3, directed);
    insertEdge(graph, 3, 4, directed);
    insertEdge(graph, 4, 1, directed);
}
void setHardWay(GRAPH* graph, _Bool directed)
{
    initializeGraph(graph, directed);

    graph->nNodes = 5;
    graph->nEdges = 8;

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


typedef struct discoveredEdges {
    int y;
    struct discoveredEdges* next;
} DiscEdges;

typedef struct path {
    int y;
    struct path* next;
}PATH;



void edgeWasDiscovered(DiscEdges* discoveredEdges[], int x, int y)
{
    DiscEdges* node = malloc(sizeof(DiscEdges));
    node->y = y;
    node->next = discoveredEdges[x];
    discoveredEdges[x] = node;

    node = malloc(sizeof(DiscEdges));
    node->y = x;
    node->next = discoveredEdges[y];
    discoveredEdges[y] = node;
}
_Bool wasDiscoverd(DiscEdges* discoveredEdges[], int x, int y)
{

    for(DiscEdges* node = discoveredEdges[x]; node != NULL; node = node->next)
    {
        if(node->y == y) return 1;
    }
    return 0;
}
void addStepToPath(PATH** end, int y)
{
    PATH* node = malloc(sizeof(PATH));
    node->y = y;
    node->next = NULL;
    (*end)->next = node;
    *end = node;
}
void setEdgeUndiscovered(DiscEdges* discoveredEdges[], _Bool directed, int x, int y)
{
    DiscEdges* prev = discoveredEdges[x];
    if(prev == NULL) return;
    DiscEdges* node = prev->next;

    if(prev->y == y)
    {
        discoveredEdges[x] = prev->next;
        free(prev);
    }
    else {
        while(node != NULL)
        {
            if(node->y == y)
            {
                prev->next = node->next;
                free(node);
                break;
            }

            prev = prev->next;
            node = node->next;
        }
    }

    if(directed == 0)
        setEdgeUndiscovered(discoveredEdges, 1, y, x);
}
void deleteStepFromPath(PATH* start, PATH** end)
{
    if(start == NULL)
        puts("start == NULL");
    while(start != NULL && start != *end)
    {
        if(start->next == *end)
        {
            start->next = NULL;
            free(*end);
            *end = start;
            return;
        }

        start = start->next;
    }

    puts("Error: can't delete the last node in path");
}
void printPath(PATH* node)
{
    printf("The way: ");
    for(; node != NULL; node = node->next)
        printf(" %d", node->y);
    puts("");
}
void printDiscEdges(int nNodes, DiscEdges* discoveredEdges[])
{
    DiscEdges* edge;
    for(int i = 1; i <= nNodes; i++)
    {
        printf("Edge %d to: ", i);
        edge = discoveredEdges[i];
        while(edge != NULL)
        {
            printf(" %d", edge->y);
            edge = edge->next;
        }

        printf("\n");
    }
}

void searchPath(GRAPH* graph, _Bool directed, DiscEdges* discoveredEdges[], PATH* start, PATH* end, int x, int* counter)
{
    //список суміжних вершин
    EDGENODE* aroundVertexes = graph->edges[x];//я беру всі вершини які є зєднані із вершиною x


    //цикл нам потрібний для того щоб пройтися по всім елементам списку
    for (int y;aroundVertexes != NULL; aroundVertexes = aroundVertexes->next)
    {
        //і ти дістаю значення ітого елемента
        y = aroundVertexes->y;

        //якщо я наткнувя на не відкриту вершину
        if (wasDiscoverd(discoveredEdges, x, y) == 0)
        {
            //printf("Now is being processed neighbor to %d: %d\n", x,y);
            edgeWasDiscovered(discoveredEdges, x, y);
            //ми втановлюємо батька "v"
            addStepToPath(&end, y);
            //паралельно опрацювати вершину "y"
            *counter += 1;

            searchPath(graph, directed, discoveredEdges, start, end, y, counter);

            setEdgeUndiscovered(discoveredEdges, directed, x, y);
            deleteStepFromPath(start, &end);
            *counter -= 1;

            //printDiscEdges(graph->nNodes, discoveredEdges);

            //printf("After deleting: ");
            //printPath(start);
        }

    }

    if(*counter *2 == graph->nEdges)
    {
        printPath(start);
    }

}
void initializeSearch(GRAPH* graph, DiscEdges* discoveredEdges[], PATH** start, PATH** end, int firstPoint)
{
    for(int i = 1; i <= graph->nNodes; i++)
        discoveredEdges[i] = NULL;


    PATH* firstNode = malloc(sizeof(PATH));
    firstNode->y = firstPoint;
    firstNode->next = NULL;
    *end = firstNode;
    *start = *end;
}

void startSearch(GRAPH* graph, _Bool directed)
{
    DiscEdges* discoveredEdges[MAXV+1];//відкрита// побували чи ні
    PATH *start, *end;//шлях який пройшов алгоритм
    int counter = 0;


    for(int i = 1; i <= graph->nNodes; i++)
    {
        initializeSearch(graph, discoveredEdges, &start, &end, i);

        searchPath(graph, directed, discoveredEdges, start, end, i, &counter);
    }
}


int main()
{
    GRAPH graph;
    readGraph(&graph, 0);
    //setGraph(&graph, 0);
    //setHardWay(&graph, 0);

    printGraph(&graph);


    startSearch(&graph, 0);


    puts("");
    system("pause");
    return 0;
}