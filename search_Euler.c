#include "search_Euler.h"


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
void deleteStepFromPath(PATH* node, PATH** end)
{
    if(node == NULL)
        puts("start == NULL");
    while(node != NULL && node != *end)
    {
        if(node->next == *end)
        {
            node->next = NULL;
            free(*end);
            *end = node;
            return;
        }

        node = node->next;
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

void searchPath(GRAPH* graph, _Bool directed, DiscEdges* discoveredEdges[], PATH* start, PATH* end, int x, int* counter, int *numOfPaths)
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

            searchPath(graph, directed, discoveredEdges, start, end, y, counter, numOfPaths);

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
        (*numOfPaths)++;
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
    int numOfPaths = 0;

    puts("\tEulerian paths:");

    for(int i = 1, counter = 0; i <= graph->nNodes; i++)
    {
        initializeSearch(graph, discoveredEdges, &start, &end, i);
        searchPath(graph, directed, discoveredEdges, start, end, i, &counter, &numOfPaths);
    }

    printf("\n%d paths were found\n", numOfPaths);
}


