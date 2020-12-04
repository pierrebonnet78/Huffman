#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include "WriteText.h"


void reset_dico() {
    FILE* fp;
    fp = NULL;
    fp = fopen("C:\\Users\\pierr\\OneDrive - Efrei\\Documents\\EFREI\\S03\\Algo\\C\\Huffman Project\\Huffman Project\\Dico.txt", "w");
    fclose(fp);
}
void write_text(long bytes[], int size)
{

    FILE* fp;
    fp = NULL;
    fp = fopen("C:\\Users\\pierr\\OneDrive - Efrei\\Documents\\EFREI\\S03\\Algo\\C\\Huffman Project\\Huffman Project\\Output.txt", "w");
    if (fp != NULL) {
        for (int i = 0; i < size; i++)
        {
            fprintf(fp, "%ld ", bytes[i]);
        }
        fclose(fp);
    }
    else {
        printf("\nError in openning Output.txt");
    }
}

Node* search_in_dico(Node* temp, char value) {
    if (temp == NULL || temp->letter[0] == value) {
        return temp;
    }
    if (temp->letter[0] < value) {
        return search_in_dico(temp->right, value);
    }
    return search_in_dico(temp->left, value);

}

void write_in_huffman_code(char* text, Node* avl) {
    FILE* fp;
    fp = NULL;
    fp = fopen("C:\\Users\\pierr\\OneDrive - Efrei\\Documents\\EFREI\\S03\\Algo\\C\\Huffman Project\\Huffman Project\\OutputHuffmanCode.txt", "w");
    if (fp != NULL) {
        int size, i;
        size = strlen(text);
        Node* node;
        for (i = 0; i < size; i++) {
            node = search_in_dico(avl, text[i]);
            if (node != NULL) {
                fprintf(fp, "%s ", node->code_huffman);
            }
        }
        fclose(fp);
    }
    else {
        printf("\nProblem in opening OutputHuffmanCode.txt");
    }
}
