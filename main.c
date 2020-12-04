#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Display.h"
#include"ListChar.h"
#include "Node.h"
#include"Queue.h"
#include "ReadText.h"
#include "Others.h"
#include "TreeCreation.h"
#include "WriteText.h"
#include <time.h>

 
void compress_txt() {

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

    // CREATE AND SORT LIST OF CHARACTERS OCCURENCES FROM ASCII TEXT //
        ListChar* list_characters = NULL;
        list_characters = number_of_occurences(text);
        sort_listChar(list_characters);
        
    // CREATE HUFFMAN TREE AND DICO.TXT // 
        reset_dico(); //need to reset because opened in 'append' mode
        Node* root;
        root = huffman_code(list_characters);

    // STORE DICO.TXT IN MEMORY IN A SSL // 
        Letter* list_characters_huffman_code = NULL;
        list_characters_huffman_code = read_and_store_dico(text, list_characters);
        list_characters_huffman_code = sort_listChar_v2(list_characters_huffman_code);

    // CREATE AVL USING 2 ARRAYS OF CHARS CONTAINING EACH LETTER AND ITS HUFFMAN CODE // 
        Letter* temp = list_characters_huffman_code;
        char list_characters_char[257];
        char* list_characters_code[257];
        int i = 0;
        while (temp != NULL) {
            list_characters_char[i] = temp->lettre[0];
            list_characters_code[i] = temp->code;
            printf("%c %s\n", list_characters_char[i], list_characters_code[i]);
            temp = temp->next;
            i++;
        }
   
        Node* avl;
        avl = create_AVL(list_characters_char, list_characters_code, 0, i-1);

    // WRITE TEXT FOLLOWINF HUFFMAN CODE STORE IN AVL // 
        write_in_huffman_code(text, avl);
        character_comparaison();
    
    // FREE MEMORY // 
        free_list_char(list_characters);
        free_list_char_huffman_code(list_characters_huffman_code);
        free_tree(root);
        free_tree(avl);
        printf("\n\n\t Memory free ok.\n\n");
}


int main()
{
    /*clock_t begin = clock();*/
   
    compress_txt();


    /*clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Exececution time : %f", time_spent);*/

    return 0;

}
