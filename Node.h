#pragma once
#ifndef NODE_H
#define NODE_H
#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    char letter;
    int occ;
    struct Node* right;
    struct Node* left;
    char code_huffman[256];
} Node;

Node* create_node(char data, int occurence);
void free_node(Node* root);
void swap_node(Node** a, Node** b);
void insertion_sort(Node* arr[256], int n);
int add_by_dichotomie(Node* arr[256]);

#endif // !NODE_H