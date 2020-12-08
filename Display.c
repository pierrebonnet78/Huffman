#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include "Display.h"
#include "ListChar.h"


void display_tree(Node* node) {
    if (node == NULL)
        return;
    display_tree(node->left);
    display_tree(node->right);
    printf("\n%c : %d", node->letter, node->occ);
}

void print_tab(Node* tab[256], int len) {
    for (int i = 0; i <= len; i++) {
        printf("\n%c - %d", tab[i]->letter, tab[i]->occ);

    }
}

void display_list_of_occ(ListChar* list)  //test function
{
    printf("\nChar | Occurrences ");
    printf("\n--------------------\n");
    ListChar* temp = list;
    while (temp != NULL)
    {
        printf("\n  %c  | %d", temp->letter, temp->occ);

        temp = temp->next;
    }
    printf("\n\n");
}

void character_comparaison()
{
    FILE* fp;
    fp = NULL;
    char str;
    char* filename = "Output.txt";
    fp = fopen(filename, "r");
    int count1 = 0;
    int count2 = 0;
    float ratio;
    if (fp != NULL) {

        while ((str = fgetc(fp)) != EOF)
        {
            count1++;
        }
        printf("\n\tNumber of characters before compression : %d", count1);
        fclose(fp);
    }
    else {
        printf("Problem in openning Alice.txt");
    }
    fp = NULL;
    filename = "OutputHuffmanCode.txt";
    fp = fopen(filename, "r");
    if (fp != NULL) {
        while ((str = fgetc(fp)) != EOF)
        {
            count2++;
        }
        ratio = 100-((float)count2 * 100) / (float)count1;
        char pourcent;
        pourcent = '%';
        printf("\n\tNumber of characters after compression : %d ", count2);
        printf("\n\tCompression rate : %.2f %c\n\n", ratio, pourcent);
        fclose(fp);
    }
    else {
        printf("Problem in openning Output.txt");
    }
}

