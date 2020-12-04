#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "Node.h"


void free_tree(Node* root) {
    if (root != NULL) {
        free_tree(root->right);
        free_tree(root->left);
        free(root);
    }
}

Node* create_node(char data, int occurence)
{
    Node* temp = (Node*)malloc(sizeof(Node));
    if (temp != NULL) {
        temp->left = NULL;
        temp->right = NULL;
        temp->letter[0] = data;
        temp->occ = occurence;
    }
    return temp;
}
