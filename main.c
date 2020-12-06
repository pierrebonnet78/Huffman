#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Display.h"
#include"ListChar.h"
#include "Node.h"
#include "ReadText.h"
#include "Others.h"
#include "TreeCreation.h"
#include "WriteText.h"
#include "Tree.h"
#include <time.h>


void compress_txt(){

    // READ TEXT //
        char text[MAXCHAR];
        read_text(text);
        int sizetext;
        sizetext = (int)strlen(text);

    // CONVERT ASCII TEXT IN BINARY AND STORE IT IN A FILE // 
        long* bytes = (long*)malloc(sizetext * sizeof(long));
        letter_to_byte(text, bytes, sizetext);
        write_text(bytes, sizetext);
        free(bytes);

    // CREATE AND SORT LIST OF CHARACTERS OCCURENCES BY READING THE INPUT FILE //
        int len = 0;
        Node* tab[256];
        len = add_by_dichotomie(tab);
        insertion_sort(tab, len);
       
      // CREATE HUFFMAN TREE AND DICO.TXT // 
        ListChar* list_characters = NULL;
        list_characters = tab_to_listchar(tab, len);
        display_list_of_occ(list_characters);
        ListChar *temp = list_characters;
        char array_characters[256];
        int array_occurences[256];
        int i = 0;
        while (temp != NULL) {
            array_characters[i] = temp->letter;
            array_occurences[i] = temp->occ;
            temp = temp->next;
            i++;
        }
        reset_dico(); //need to reset because we open it in 'append' mode
        Tree* root = NULL;
        root = huffman_coding(array_characters, array_occurences, i);

    // STORE DICO.TXT IN MEMORY IN A SSL // 
        Letter* list_characters_huffman_code = NULL;
        list_characters_huffman_code = read_and_store_dico(text, list_characters);
        list_characters_huffman_code = sort_listChar_v2(list_characters_huffman_code);


    // CREATE AVL TO STORE THE DICO USING 2 ARRAYS OF CHARS CONTAINING EACH LETTER AND ITS HUFFMAN CODE // 
        Letter* temp2 = list_characters_huffman_code;
        char list_characters_char[256];
        char* list_characters_code[256];
        i = 0;
        while (temp2 != NULL) {
            list_characters_char[i] = temp2->lettre;
            list_characters_code[i] = temp2->code;
            //printf("%c %s\n", list_characters_char[i], list_characters_code[i]);
            temp2 = temp2->next;
            i++;
        }
        Node* avl;
        avl = create_AVL(list_characters_char, list_characters_code, 0, i-1);

    // WRITE TEXT FOLLOWING HUFFMAN CODE STORE IN AVL // 
        write_in_huffman_code(text, avl);
        character_comparaison();
    
    // FREE MEMORY // 
        free_list_char(list_characters);
        free_list_char_huffman_code(list_characters_huffman_code);
        free_tree(root);
        free_tree(avl);
        printf("\n\n\t Memory free ok.\n\n");
}
void decompress_txt(Node* avl) {
    char text[MAXCHAR];
    read_text_compressed(text);
    
    write_text_ascii(avl, text);

    
}

int main()
{
    clock_t begin = clock();
   
    compress_txt();
    //decompress_txt(avl);


    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Exececution time : %f", time_spent);

    return 0;

}
