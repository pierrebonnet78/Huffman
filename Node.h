#pragma once
#ifndef NODE_H
#define NODE_H
#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    char letter[1];
    int occ;
    struct Node* right;
    struct Node* left;
    char code_huffman[257];
} Node;

Node* create_node(char data, int occurence);
void free_tree(Node* root);


#endif // !NODE_H