#pragma once
#ifndef TREE_CREATION_H
#define TREE_CREATION_H
#include <stdio.h>
#include <stdlib.h>
#include "ListChar.h"
#include "Node.h"
#include <string.h>
#include "Tree.h"


int is_leaf(Node* root);
void scan_path_leaf_of_tree(Node* root, int arr[], int top);
Node* create_AVL(char list_charcters_char[], char* list_charcters_code[], int start, int end);
void create_dico(int arr[], int n, Node* root);
void min_heapify(Tree* tree, int idx);
int is_size_one(Tree* tree);
Node* extract_min_node(Tree* tree);
void insert_node_in_tree(Tree* tree, Node* node);
void build_tree(Tree* tree);
Tree* create_and_build_tree(char array_characters[], int array_occurences[], int size);
Tree* build_huffman_tree(char array_characters[], int array_occurences[], int size);
Tree* huffman_coding(char array_characters[], int array_occurences[], int size);
#endif // !TREE_CREATION_H


