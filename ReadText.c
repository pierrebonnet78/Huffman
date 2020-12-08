#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include "ReadText.h"

void read_text(char* output){
    FILE* fp;
    fp = NULL;
    char* filename = "Alice.txt";
    fp = fopen(filename, "r");
    int i = 0;
    if (fp != NULL) {
        char tmp = fgetc(fp);
        while (tmp != EOF && i<MAXCHAR) {
            if (tmp == 10) {
                tmp = 37;
            }
            if (tmp < 0 | tmp > 127) {
                tmp = 63;
            }
            if(tmp)
            output[i] = tmp;
            tmp = fgetc(fp);
            i++;
        }
        if (tmp != EOF) {
            printf("Error in compiling, size of the document is to big.");
        }
        fclose(fp);
    }
    else {
        printf("Problem in opening Alice.txt");
    }
}

void read_text_compressed(char* output) {
    FILE* fp;
    fp = NULL;
    char* filename = "OutputHuffmanCode.txt";
    fp = fopen(filename, "r");
    int i = 0;
    if (fp != NULL) {
        char tmp = fgetc(fp);
        while (tmp != EOF && i < MAXCHAR) {
            output[i] = tmp;
            tmp = fgetc(fp);
            i++;
        }
        if (tmp != EOF) {
            printf("Error in compiling, size of the document is to big.");
        }
        fclose(fp);
    }
    else {
        printf("Problem in opening OutputHuffmanCoding.txt");
    }
}

Letter* read_and_store_dico(char* text, ListChar* list_characters) {
    FILE* fp;
    fp = NULL;
    char str[MAXCHAR];
    char* filename = "Dico.txt";
    fp = fopen(filename, "r");
    if (fp != NULL) {
        Letter* root = (Letter*)malloc(sizeof(Letter));
        Letter* temp = root;
        if (temp != NULL) {
            char tmp = fgetc(fp);
            while (tmp != EOF) {
                temp->lettre = tmp;
                fgetc(fp);
                tmp = fgetc(fp);
                signed int cpt = 0;
                while (tmp != 10) {
                    temp->code[cpt] = tmp;
                    cpt++;
                    tmp = fgetc(fp);
                }
                tmp = fgetc(fp);
                temp->next = (Letter*)malloc(sizeof(Letter));
                temp = temp->next;
            }
            temp->next = NULL;
        }
        delete_last_node_letter(root);
        fclose(fp);
        return root;
    }
    else {
        printf("\nProblem in opening Dico.txt"); 
        return NULL;
    }
}

void read_avl_in_file(char* text) {
    FILE* fp;
    fp = NULL;
    char* filename = "AVLbackup.txt";
    fp = fopen(filename, "r");
    int i = 0;
    if (fp != NULL) {
        char tmp = fgetc(fp);
        while (tmp != EOF && i < MAXCHAR) {
            text[i] = tmp;
            tmp = fgetc(fp);
            i++;
        }
        if (tmp != EOF) {
            printf("Error in compiling, size of the document is to big.");
        }
        fclose(fp);
    }
    else {
        printf("Problem in opening AVLbackup.txt");
    }
}