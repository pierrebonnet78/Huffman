#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include "TreeCreation.h"


int is_leaf(Node* root){
    if (root->left == NULL && root->right == NULL) {
        return 1;
    }
    else {
        return 0;
    }
}

Node* create_huffman_tree_with_queue(ListChar* list_characters)
{
    int size;
    size = get_list_char_size(list_characters)+1;
    Node* left, * right, * top;
    int i;
    ListChar* temp = list_characters;

    // Create 2 empty queues
    Queue* queue1 = create_queue(size);
    Queue* queue2 = create_queue(size);

    // Create a leaf node for each character of the data[] array, enqueu it to queue 1
    for (i = 0; i < size; i++) {
        en_queue(queue1, create_node(temp->letter, temp->occ));
        temp = temp->next;
    }
    while (!(is_queue_empty(queue1) && is_queue_size_one(queue2))) {
        // Dequeue two nodes with the min occurrence by looking at the front of both queues
        left = find_min_two_queues(queue1, queue2);
        right = find_min_two_queues(queue1, queue2);

        // Create new node with occurences equal to the sum of the two other nodes and enqueu this node to second queue
        top = create_node('$', left->occ + right->occ);
        top->left = left;
        top->right = right;
        en_queue(queue2, top);
    }

    return de_queue(queue2);
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

Node* huffman_code(ListChar* list_characters)
{
    Node* root = create_huffman_tree_with_queue(list_characters);
    int arr[257];
    int top = 0;
    scan_path_leaf_of_tree(root, arr, top);
    return root;
}

Node* create_AVL(char list_characters_char[257], char* list_characters_code[257], int start, int end) {
    if (start > end) {
        return NULL;
    }
    int mid = (start + end) / 2;
    Node* root = (Node*)malloc(sizeof(Node));


    root->letter[0] = list_characters_char[mid];

    memmove(root->code_huffman, list_characters_code[mid], sizeof(char)*257);

    root->left = create_AVL(list_characters_char, list_characters_code, start, mid - 1);
    root->right = create_AVL(list_characters_char, list_characters_code, mid + 1, end);
    return root;
}

void create_dico(int arr[], int n, Node* root) {
    FILE* fp;
    fp = NULL;
    char* filename = "C:\\Users\\pierr\\OneDrive - Efrei\\Documents\\EFREI\\S03\\Algo\\C\\Huffman Project\\Huffman Project\\Dico.txt";
    fp = fopen(filename, "a");
    int i;
    if (fp != NULL) {
        fputc(root->letter[0], fp);
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