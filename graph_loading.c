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
#include "./graph.c"

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

//returns a list of vertexes from a token list
// only valid tokens are considered
vertex *load_vertexes(token *tokens, int len) {
    vertex *vertexes = malloc(sizeof(vertex));
    int vertexes_size = 1;

    