#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <stdio.h>
#include "merge_sort.h"

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
    int edges_capacity;
    int vertexes_capacity;
} Graph;


typedef struct Vertex {
    int id;
    void *data;
    int *edges; //only includes outbound edges
    int edge_count;
    int edges_capacity;
} Vertex;


typedef struct Edge {
    int id;
    void *data;
    int source;
    int destination;
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
        source: -1,
        destination: -1
    };

    return binary_search(graph->vertexes, 0, graph->vertex_count, compare_vertex_id, &mock, sizeof(Vertex));
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
        source: -1,
        destination: -1
    };

    return binary_search(graph->edges, 0, graph->edge_count, compare_edge_id, &mock, sizeof(Edge));

}

// return array corresponding to raw positions of vertexes in graph arrays
int *dijkstra(Graph *graph, int start_id, int (get_cost)(Edge*)) {
    int *distances = malloc(graph->vertex_count * sizeof(int));
    bool *visited = malloc(graph->vertex_count * sizeof(bool));
    int *prev = malloc(graph->vertex_count * sizeof(int));
    int *queue = malloc(graph->vertex_count * sizeof(int));
    
    for (int i = 0; i < graph->vertex_count; i++) {
        distances[i] = INT_MAX;
        visited[i] = false;
        prev[i] = -1;
    }

    distances[graph_get_vertex_position(graph, start_id)] = 0;
    int queue_start = 0;
    int queue_end = 0;
    queue[queue_end++] = start_id;

    while (queue_start < queue_end) {
        int current = queue[queue_start++];
        visited[current] = true;

        Vertex *current_vertex = graph_get_vertex(graph, current);
        printf("edge count: %d\n", current_vertex->edge_count);

        //print edges of current vertex
        //for (int i = 0; i < current_vertex->edge_count; i++) {
        //    Edge *edge = graph_get_edge(graph, current_vertex->edges[i]);
        //    printf("%d %d %d\n", edge->source, edge->destination, get_cost(edge));
        //}

        for (int i = 0; i < current_vertex->edge_count; i++) {
            Edge *edge = graph_get_edge(graph, current_vertex->edges[i]);
            int cost = get_cost(edge);
            int next = current_vertex->edges[i];
            if (distances[next] > distances[current] + cost) {
                distances[next] = distances[current] + cost;
                prev[next] = current;
                if (!visited[next]) {
                    queue[queue_end++] = next;
                }
            }
        }
    }

    free(queue);
    free(visited);
    free(distances);

    return prev;

}

int distance(Edge *edge) {
    return *(int*) edge->data;
}


Vertex new_Vertex(int id, void *data) {
    Vertex v;
    v.id = id;
    v.data = data;
    v.edge_count = 0;
    v.edges = malloc(sizeof(int));
    v.edges_capacity = 1;
    return v;
}

Edge new_edge(int id, int source, int destination, void *data) {
    Edge e;
    e.id = id;
    e.source = source;
    e.destination = destination;
    e.data = data;
    return e;
}

void graph_add_vertex(Graph *graph, int id, void *data) {
    if (graph->vertex_count == graph->vertexes_capacity) {
        graph->vertexes_capacity *= 2;
        graph->vertexes = realloc(graph->vertexes, graph->vertexes_capacity * sizeof(Vertex));
    }
    Vertex v = new_Vertex(id, data);
    graph->vertexes[graph->vertex_count] = v;
    graph->vertex_count++;

    merge_sort(graph->vertexes, graph->vertex_count, compare_vertex_id, sizeof(Vertex));
}

void vertex_add_edge(Graph *graph, Vertex *vertex, int id) {
    Edge *e = graph_get_edge(graph, id);

    if (e == NULL) {
        printf("edge not found\n");
        return;
    }

    if (vertex->edge_count == vertex->edges_capacity) {
        vertex->edges_capacity *= 2;
        vertex->edges = realloc(vertex->edges, vertex->edges_capacity * sizeof(int));
    }

    vertex->edges[vertex->edge_count] = id;
    vertex->edge_count++;
    merge_sort(vertex->edges, vertex->edge_count, compare_ints, sizeof(int));
}

Edge *graph_add_edge(Graph *graph, int id, int source, int destination, void *data) {
    if (graph->edge_count == graph->edges_capacity) {
        graph->edges_capacity *= 2;
        graph->edges = realloc(graph->edges, graph->edges_capacity * sizeof(Edge));
    }

    Vertex *source_vertex = graph_get_vertex(graph, source);
    Vertex *destination_vertex = graph_get_vertex(graph, destination);

    if (source_vertex == NULL || destination_vertex == NULL) {
        printf("source or destination vertex not found\n");
        return NULL;
    }

    Edge e = new_edge(id, source, destination, data);
    graph->edges[graph->edge_count] = e;
    graph->edge_count++;

    vertex_add_edge(graph, source_vertex, id);
    
    merge_sort(graph->edges, graph->edge_count, compare_edge_id, sizeof(Edge));
}

Graph new_graph() {
    Graph g;
    g.vertexes = malloc(10 * sizeof(Vertex));
    g.vertex_count = 0;
    g.vertexes_capacity = 10;
    g.edges = malloc(10 * sizeof(Edge));
    g.edge_count = 0;
    g.edges_capacity = 10;
    return g;
}



void main() {
    //create testing graph
    Graph graph = new_graph();

    char *data = malloc(sizeof(char) * 10);
    *data = 'A';
    graph_add_vertex(&graph, 0, data);

    data = malloc(sizeof(char) * 10);
    *data = 'B';
    graph_add_vertex(&graph, 1, data);
    
    data = malloc(sizeof(char) * 10);
    *data = 'C';
    graph_add_vertex(&graph, 2, data);
    
    data = malloc(sizeof(char) * 10);
    *data = 'D';
    graph_add_vertex(&graph, 3, data);
    
    data = malloc(sizeof(char) * 10);
    *data = 'E';
    graph_add_vertex(&graph, 4, data);


    data = malloc(sizeof(int));
    *data = 1;
    graph_add_edge(&graph, 0, 0, 1, data);
    data = malloc(sizeof(int));
    *data = 2;
    graph_add_edge(&graph, 1, 0, 2, data);
    data = malloc(sizeof(int));
    *data = 3;
    graph_add_edge(&graph, 2, 1, 3, data);
    data = malloc(sizeof(int));
    *data = 1;
    graph_add_edge(&graph, 3, 2, 4, data);
    data = malloc(sizeof(int));
    *data = 2;
    graph_add_edge(&graph, 4, 3, 0, data);

    //print graph vertexes
    for (int i = 0; i < graph.vertex_count; i++) {
        printf("v: %d %c, \n", graph.vertexes[i].id, *(char*)graph.vertexes[i].data);

        //print vertex edges
        for (int j = 0; j < graph.vertexes[i].edge_count; j++) {
            printf("    %d\n", graph.vertexes[i].edges[j]);
            
            Edge *edge = graph_get_edge(&graph, graph.vertexes[i].edges[j]);
            printf("e: %p\n", edge);
            printf("    e: %d %d %p\n", edge->source, edge->destination, edge->data);
        }
    }

    printf("pre dijkstra\n");
    // test dijkstra
    int *routes = dijkstra(&graph, 0, distance);

    for (int i = 0; i < graph.vertex_count; i++) {
        printf("%c\n", *(char*)graph.vertexes[i].data);
    }

    for (int i = 0; i < graph.vertex_count; i++) {
        printf("%d\n", routes[i]);
    }
}