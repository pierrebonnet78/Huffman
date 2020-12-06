#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include "TreeCreation.h"
#include "Display.h"
#include "Tree.h"

int is_leaf(Node* root){
    if (root->left == NULL && root->right == NULL) {
        return 1;
    }
    return 0;
}

void scan_path_leaf_of_tree(Node* root, int arr[], int top)
{
    if (root->left) {
        arr[top] = 0;
        scan_path_leaf_of_tree(root->left, arr, top + 1);
    }
    if (root->right) {
        arr[top] = 1;
        scan_path_leaf_of_tree(root->right, arr, top + 1);
    }
    
    if (is_leaf(root)) {
        create_dico(arr, top, root);
    }
}

Node* create_AVL(char list_characters_char[256], char* list_characters_code[256], int start, int end) {
    if (start > end) {
        return NULL;
    }
    int mid = (start + end) / 2;
    Node* root = (Node*)malloc(sizeof(Node));

    root->letter = list_characters_char[mid];

    memmove(root->code_huffman, list_characters_code[mid], sizeof(char)*256);

    root->left = create_AVL(list_characters_char, list_characters_code, start, mid - 1);
    root->right = create_AVL(list_characters_char, list_characters_code, mid + 1, end);
    return root;
}

void create_dico(int arr[], int n, Node* root) {
    FILE* fp;
    fp = NULL;
    char* filename = "Dico.txt";
    fp = fopen(filename, "a");
    int i;
    if (fp != NULL) {
        fputc(root->letter, fp);
        fputc(32, fp);
        for (i = 0; i < n; i++) {
            fputc(arr[i]+48, fp);
            
        }
        fputc(0, fp);
        fputc(10, fp);
        fclose(fp);
    }
    else {
        printf("Problem in openning Dico.txt");
    }
}

void min_heapify(Tree* tree, int idx)
{
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if ((left < tree->size) && (tree->arrayofnode[left]->occ < tree->arrayofnode[smallest]->occ))
        smallest = left;

    if ((right < tree->size) && (tree->arrayofnode[right]->occ < tree->arrayofnode[smallest]->occ))
        smallest = right;

    if (smallest != idx) {
        swap_node(&tree->arrayofnode[smallest], &tree->arrayofnode[idx]);
        min_heapify(tree, smallest);
    }
}

int is_size_one(Tree* tree)
{
    if (tree->size == 1) {
        return 1;
    }
    return 0;
}

Node* extract_min_node(Tree* tree)
{
    Node* temp = tree->arrayofnode[0];
    tree->arrayofnode[0] = tree->arrayofnode[tree->size - 1];
    tree->size--;
    min_heapify(tree, 0);
    return temp;
}

void insert_node_in_tree(Tree* tree, Node* node)
{
    tree->size++;
    int i;
    i = tree->size - 1;
    while (i && node->occ < tree->arrayofnode[(i - 1) / 2]->occ) {

        tree->arrayofnode[i] = tree->arrayofnode[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    tree->arrayofnode[i] = node;
}

void build_tree(Tree* tree)
{
    int n = tree->size - 1;
    int i;
    for (i = (n - 1) / 2; i >= 0; --i)
        min_heapify(tree, i);
}

Tree* create_and_build_tree(char array_characters[], int array_occurences[], int size)
{
    Tree* tree = create_tree(size);
    for (int i = 0; i < size; ++i) {
        tree->arrayofnode[i] = create_node(array_characters[i], array_occurences[i]);
    }
    tree->size = size;
    build_tree(tree);
    return tree;
}

Tree* build_huffman_tree(char array_characters[], int array_occurences[], int size)
{
    Node* left, * right, * top;
    Tree* tree = create_and_build_tree(array_characters, array_occurences, size);
    while (!is_size_one(tree)) {
        left = extract_min_node(tree);
        right = extract_min_node(tree);
        top = create_node('$', left->occ + right->occ);
        top->left = left;
        top->right = right;
        insert_node_in_tree(tree, top);
    }

    return extract_min_node(tree);
}

Tree* huffman_coding(char array_characters[], int array_occurences[], int size) {

    Tree* root = build_huffman_tree(array_characters, array_occurences, size);
    int arr[256];
    int top = 0;
    scan_path_leaf_of_tree(root, arr, top);
    return root;
}
