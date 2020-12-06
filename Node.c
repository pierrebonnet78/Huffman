#pragma once
#pragma warning(disable : 4996)
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
        temp->letter = data;
        temp->occ = occurence;
    }
    return temp;
}

void swap_node(Node** a, Node** b)
{
    Node* temp = *a;
    *a = *b;
    *b = temp;
}

void insertion_sort(Node* arr[256], int n)
{
    int i, j;
    Node* key;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j]->occ < key->occ) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int add_by_dichotomie(Node* arr[256]) {
    int check, i;
    FILE* File;
    Node* p;
    int beg = 0, end = 0, cpt = 0, mid;
    if ((File = fopen("Alice.txt", "r")) == NULL) {
        printf("Error in opening Alice.txt");
    }
    else {
        char c = fgetc(File);
        if (c != EOF) {
            if (c == 10) {
                c = 37;
            }
            if (c < 0 | c > 127) {
                c = 63;
            }
            p = (Node*)malloc(sizeof(Node));
            p->letter = c;
            p->occ = 1;
            p->left = p->right = NULL;
            arr[0] = p;
            while ((c = fgetc(File)) != EOF) {
                if (c == 10) {
                    c = 37;
                }
                if (c < 0 | c > 127) {
                    c = 63;
                }
                check = 0;
                while (check == 0 && beg <= end) {
                    mid = (int)((beg + end) / 2);
                    if (arr[mid]->letter == c) {
                        check = 1;
                        arr[mid]->occ = arr[mid]->occ + 1;
                    }
                    else {
                        if (c > arr[mid]->letter) {
                            beg = mid + 1;
                        }
                        else {
                            end = mid - 1;
                        }
                    }
                }
                if (check == 0) {
                    cpt = cpt + 1;
                    p = (Node*)malloc(sizeof(Node));
                    p->letter = c;
                    p->occ = 1;
                    p->left = p->right = NULL;
                    for (i = cpt; i > beg; i--) {
                        arr[i] = arr[i - 1];
                    }
                    arr[beg] = p;
                }
                beg = 0;
                end = cpt;
            }
        }
        else {
            end = -1;
        }
        fclose(File);
        return end;
    }
}