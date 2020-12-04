#pragma once
#ifndef TREE_CREATION_H
#define TREE_CREATION_H
#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"
#include "ListChar.h"
#include "Node.h"
#include <wchar.h>
#include <string.h>




int is_leaf(Node* root);
Node* create_huffman_tree_with_queue(ListChar* list_characters);
void scan_path_leaf_of_tree(Node* root, int arr[], int top);
Node* huffman_code(ListChar* list_characters);
Node* create_AVL(char list_charcters_char[], char* list_charcters_code[], int start, int end);
void create_dico(int arr[], int n, Node* root);

#endif // !TREE_CREATION_H
