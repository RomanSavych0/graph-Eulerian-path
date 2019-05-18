#ifndef GRAPHS_SEARCH_EULER_H
#define GRAPHS_SEARCH_EULER_H

typedef struct discoveredEdges {
    int y;
    struct discoveredEdges* next;
} DiscEdges;

typedef struct path {
    int y;
    struct path* next;
}PATH;


#endif //GRAPHS_SEARCH_EULER_H
