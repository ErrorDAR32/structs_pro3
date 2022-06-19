// this file contains necessary functions to load a graph from a file
// the must have the following sintax
//
//first, cities (vertexes) are stated
// ciudad <name>
// this repeats until we find "..."
//
// after that we start to load the edges
// ciudad <source_name>
// ciudad <destination_name>
// <distance>
// blank lines are ignored
// one again we stop when we find "..."
//
// keyword ciudad is case insensitive

#include <stdlib.h>
#include "graph.h"
#include <memory.h>>

typedef struct token {
    char* str;
    int len;
} token;


//returns a list of tokens from a string
// the tokens are delimited by either newlines or spaces
// delimiters are not included in the tokens
// delimiters next to each other are considered one delimiter
token *tokenize(char *str, int *len) {
    int current_token_len = 0;

    //duplicate size if full
    token *tokens = malloc(sizeof(token));
    int tokens_size = 1;
    
    for (int i=0; str[i]!='\0'; i++) {
        if (str[i] == '\n' || str[i] == ' ') {
            if (current_token_len == 0) {
                continue; //ignore delimiters next to each other
            }

            //token finished
            token t;
            t.str = str + i - current_token_len;
            t.len = current_token_len;
            current_token_len = 0;

            //add token to list
            if (tokens_size == tokens_size) {
                tokens_size *= 2;
                tokens = realloc(tokens, tokens_size * sizeof(token));
            }
            tokens[tokens_size++] = t;
            continue;
        }
    }
}

bool prefix(const char *pre, const char *str) {
    return strncmp(pre, str, strlen(pre)) == 0;
}

//returns a list of vertexes from a token list
// only ciudad tokens are considered, rest are ignored
Vertex *load_vertexes(token *tokens, int len) {
    Vertex *vertexes = malloc(sizeof(Vertex));
    int vertexes_size = 0;
    int vertexes_capacity = 1;

    bool detected = false;

    for (int i=0; i<len; i++) {
        if (vertexes_size == vertexes_capacity) {
            vertexes_capacity *= 2;
            vertexes = realloc(vertexes, vertexes_capacity * sizeof(Vertex));
        }

        if (detected) {
            Vertex v;
            v.id = vertexes_size;
            v.data = memcpy(malloc(tokens[i+1].len + 1), tokens[i+1].str, tokens[i+1].len);
            vertexes[vertexes_size] = v;
        }

        if (strcmp(tokens[i].str, "ciudad") == 0) {
            detected = true;
        }
    }
    return vertexes;
}


// improvement, dont do this super slow vertexes lookup of linear time in each edge
Edge *load_edges(token *tokens, int len, Vertex *vertexes, int vertexes_size) {
    Edge *edges = malloc(sizeof(Edge));
    int edges_size = 0;
    int edges_capacity = 1;

    int detected = 0;

    int c1 = 0;
    int c2 = 0;
    int d = 0;

    for (int i=0; i<len; i++) {
        if (edges_size == edges_capacity) {
            edges_capacity *= 2;
            edges = realloc(edges, edges_capacity * sizeof(Edge));
        }

        if (detected == 5) {
            Edge e;

            e.source = vertexes[c1].id;
            e.destination = vertexes[c2].id;
            e.data = memcpy(malloc(malloc(tokens[i].len + 1)), tokens[i].str, tokens[i].len);
            edges[edges_size] = e;
            
            detected = 0;
            continue;

        } 

        if (detected == 1 || detected == 3) {
            detected++;
            if (detected == 1) {
                // search for c1 token.str in vertexes.data
                bool found = false;
                for (int j=0; j<vertexes_size; j++) {
                    if (strcmp(vertexes[j].data, tokens[i].str) == 0) {
                        c1 = j;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    printf("error: vertex not found\n");
                    return NULL;
                }  
                continue;
            } else {
                //search for c2 token.str in vertexes.data
                bool found = false;
                for (int j=0; j<vertexes_size; j++) {
                    if (strcmp(vertexes[j].data, tokens[i].str) == 0) {
                        c2 = j;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    printf("error: vertex not found\n");
                    return NULL;
                }
                continue;
            }
        } else {
            println("error: invalid token");
            return NULL;
        }
        
        if (prefix("ciudad", tokens[i].str)) {
            if (detected == 0 || detected == 2) {
                detected++;
            } else {
                println("error: invalid token");
                return NULL;
            }
        }

        if (prefix("distancia", tokens[i].str)) {
            if (detected == 4) {
                d = i;
                detected++;
            } else {
                println("error: invalid token");
                return NULL;
            }
            
        }
    }
    return edges;
}