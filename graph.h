#ifndef GRAPHS_GRAPH_H
#define GRAPHS_GRAPH_H

#define MAXV 50

typedef struct edgenode {
    int y;
    _Bool discovered;
    struct edgenode *next;
} EDGENODE;

typedef struct graph {
    struct edgenode** edges; //ребра
    int* degree; // степінь вершини
    int nNodes; //кількість вузлів
    int nEdges; //кількість ребер
    _Bool isDirected; //орієнтований
} GRAPH;

//ініціалізація графа
void initializeGraph(GRAPH* , _Bool , int , int);
void readGraphKeyboard(GRAPH*, _Bool);
void readGraphFile(GRAPH*, _Bool);
void insertEdge(GRAPH*, int, int, _Bool);
void printGraph(GRAPH*);
void setGraph(GRAPH* graph, _Bool);
void clearGraph(GRAPH* graph);

#endif //GRAPHS_GRAPH_H
