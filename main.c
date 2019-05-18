#include <stdio.h>
#include "graph.c"
#include "search_Euler.c"


int main()
{
    GRAPH graph;
    //readGraphKeyboard(&graph, 0);
    readGraphFile(&graph, 0);
    //setGraph(&graph, 0);
    //setHardWay(&graph, 0);

    printGraph(&graph);

    startSearch(&graph, 0);

    clearGraph(&graph);

    puts("");
    system("pause");
    return 0;
}