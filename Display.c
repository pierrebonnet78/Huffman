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
    printf("\n%c : %s", node->letter[0], node->code_huffman);
}

void display_list_of_occ(ListChar* list)  //test function
{
    ListChar* temp = list;
    while (temp != NULL)
    {
        printf("\n %c : %d", temp->letter, temp->occ);

        temp = temp->next;
    }
}

void character_comparaison()
{
    FILE* fp;
    fp = NULL;
    char str;
    char* filename = "C:\\Users\\pierr\\OneDrive - Efrei\\Documents\\EFREI\\S03\\Algo\\C\\Huffman Project\\Huffman Project\\Output.txt";
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
    filename = "C:\\Users\\pierr\\OneDrive - Efrei\\Documents\\EFREI\\S03\\Algo\\C\\Huffman Project\\Huffman Project\\OutputHuffmanCode.txt";
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

