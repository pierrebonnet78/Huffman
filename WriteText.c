#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include "WriteText.h"
#define MAXCHAR 10000000


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
    if (temp == NULL || temp->letter == value) {
        return temp;
    }
    if (temp->letter < value) {
        return search_in_dico(temp->right, value);
    }
    return search_in_dico(temp->left, value);

}

void write_in_huffman_code(char* text, Node* avl) {
    FILE* fp;
    fp = NULL;
    fp = fopen("OutputHuffmanCode.txt", "w");
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
        fputc(42, fp);
        fclose(fp);
    }
    else {
        printf("\nProblem in opening OutputHuffmanCode.txt");
    }
}

void write_text_ascii(Node* avl, char* text) {
    FILE* fp;
    fp = NULL;
    
    fp = fopen("C:\\Users\\pierr\\OneDrive - Efrei\\Documents\\EFREI\\S03\\Algo\\C\\Huffman Project\\Huffman Project\\decompressedFile.txt", "w");
    if (fp != NULL){
        char tmp;
        int i = 0;
        int y = 0;
        char my_array[25];
        /*for (y = 0; y < 25; y++) {
            my_array[y] = '2';
        }*/
        for (int i = 0; i < strlen(text); i++){
            while (text[i] != 42) {
                if (text[i] == 32) {
                    
                    for (y = 0; y <= 24; y++) {
                        my_array[y] = '2';
                    }
                    i++;
                }
                else {
                    my_array[i] = text[i];
                    i++;
                }
            }
            printf("%s\n", my_array);
         }
            //while(fputc(text[i], fp);
        fclose(fp);
        }
    
    else {
        printf("\nProblem in opening the compressed file.");
    }
}

