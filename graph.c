#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

//this directed graph conists of arrays of vertices and edges
// in which each vertex is an array of edges
// each edge is an array of vertices
// both of them also carry other data

// for lookups we use bynary search
// since each node and edge carries pointers to its associates, 
// worst case memory is O(VE-V+E)//not n squared but not too good either
// but it is fast enough for our purposes, since we are dealing with very small graphs
// resize occurs when any array is full to double its size


struct Vertex;
struct Edge;


typedef struct Graph {
    struct Edge *edges;
    struct Vertex *vertexes;
    int vertex_count;
    int edge_count;
} Graph;


typedef struct Vertex {
    int id;
    void *data;
    int *edges; //only includes outbound edges
    int edge_count;
} Vertex;


typedef struct Edge {
    int id;
    void *data;
    int *source;
    int *destination;
} Edge;


Graph *graph_create(int vertex_count, int edge_count) {
    Graph *graph = malloc(sizeof(Graph));
    graph->vertexes = malloc(vertex_count * sizeof(Vertex));
    graph->edges = malloc(edge_count * sizeof(Edge));
    return graph;
}

void* binary_search(void *arr, int start, int end, int (*compare)(void *, void *), void* key, int data_size) {
    while (start < end) {
        int mid = (start + end) / 2;
        int cmp = compare(arr+mid*data_size, key);

        if (cmp == 0) {
            return arr + mid * data_size;
        } else if (cmp == -1) {
            start = mid + 1;
        } else {
            end = mid;
        }
    }
    return NULL;
}

int compare_vertex_id(void *a, void *b) {
    Vertex *x = a;
    int *y = b;
    if (x->id < *y) {
        return -1;
    } else if (x->id > *y) {
        return 1;
    } else {
        return 0;
    }
}

int compare_edge_id(void *a, void *b) {
    Edge *x = a;
    int *y = b;
    if (x->id < *y) {
        return -1;
    } else if (x->id > *y) {
        return 1;
    } else {
        return 0;
    }
}

Vertex *graph_get_vertex(Graph *graph, int id) {
    Edge mock = (Edge){    
        id: id,
        data: NULL,
        source: NULL,
        destination: NULL
    };

    return binary_search(graph->edges, 0, graph->edge_count, compare_edge_id, &mock, sizeof(Vertex));
}


int graph_get_vertex_position(Graph *graph, int id) {
    int start = 0;
    int end = graph->vertex_count;
    while (start < end) {
        int mid = (start + end) / 2;
        if (graph->vertexes[mid].id == id) {
            return mid;
        } else if (graph->vertexes[mid].id < id) {
            start = mid + 1;
        } else {
            end = mid;
        }
    }
    return -1;
}

Edge *graph_get_edge(Graph *graph, int id) {
    Edge mock = (Edge){
        id: id,
        data: NULL,
        source: NULL,
        destination: NULL
    };
    return binary_search(graph->edges, 0, graph->edge_count, compare_edge_id, &mock, sizeof(Edge));

}


int *dijkstra(Graph *graph, int start_id, int end_id, int (get_cost)(Edge*)) {
    int *cost = malloc(graph->vertex_count * sizeof(int));
    bool *visited = calloc(graph->vertex_count, sizeof(bool));
    int *prev = malloc(graph->vertex_count * sizeof(int));

    int current = graph_get_vertex_position(graph, start_id);
    cost[current] = 0;
    visited[current] = true;

    while (current != -1) {
        Vertex *vertex = &graph->vertexes[current];
        for (int i = 0; i < vertex->edge_count; i++) {
            int edge = &vertex->edges[i];
            int cost_to_destination = cost[current] + get_cost(edge);
            int destination = graph_get_vertex_position(graph, graph_get_edge(graph, edge)->destination->id);
            if (visited[destination]) {
                if (cost_to_destination < cost[destination]) {
                    cost[destination] = cost_to_destination;
                }
            } else {
                cost[destination] = cost_to_destination;
                visited[destination] = true;
            }
        }
        visited[current] = true;
        current = -1;
        int min = INT_MAX;
        for (int i = 0; i < graph->vertex_count; i++) {
            if (!visited[i] && cost[i] < min) {
                min = cost[i];
                current = i;
            }
        }
    }
}
