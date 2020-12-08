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
        reset_dico(); //need to reset because we open it in 'append' mode
        Tree* root = NULL;
        root = huffman_coding(len, tab);
       
    // STORE DICO.TXT IN MEMORY IN A SSL // 
        Letter* list_characters_huffman_code = NULL;
        list_characters_huffman_code = read_and_store_dico(text, list_characters);
        list_characters_huffman_code = sort_listChar_v2(list_characters_huffman_code);

    // CREATE AVL TO STORE THE DICO USING 2 ARRAYS OF CHARS CONTAINING EACH LETTER AND ITS HUFFMAN CODE // 
        Letter* temp = list_characters_huffman_code;
        char list_characters_char[256];
        char* list_characters_code[256];
        int i = 0;
        while (temp != NULL) {
            list_characters_char[i] = temp->lettre;
            list_characters_code[i] = temp->code;
            //printf("%c %s\n", list_characters_char[i], list_characters_code[i]);
            temp = temp->next;
            i++;
        }
        Node* avl;
        avl = create_AVL(list_characters_char, list_characters_code, 0, i-1);

    // WRITE TEXT IN HUFFMAN CODE // 
        write_in_huffman_code(text, avl);
        //reset_avl_backup();
        post_order_tree_traversal(avl);
        character_comparaison();

    // FREE MEMORY // 
    // FREE MEMORY // 
        free_list_char(list_characters);
        free_list_char_huffman_code(list_characters_huffman_code);
        free_tree(root);
        free_node(avl);
}





void decompress_txt() {
    /*char text2[MAXCHAR];
    read_text_compressed(text2);
    read_avl_in_file(text);
    printf("\n%s", text2);
    rebuild_avl(text);
    write_text_ascii(avl, text);*/
    
}

int main(){
    int choice = 0;
    int i = 0;
    do{
        printf("%c", 201);
        for (i = 0; i < 100; i++) printf("%c", 205);
        printf("%c", 187);
        printf("\n\n\t\t\t\t\t\tHuffman Coding\n\n");
        printf("%c", 200);
        for (i = 0; i < 99; i++) printf("%c", 205);
        printf("%c", 205);
        printf("%c", 188);
        printf("\n\n\n");
        printf("\n\n\n\t\t\t\t\tPress any key to go to main menu.....");
        fflush(stdin);
        getchar();
        printf("\n-----------------------------------------------------------------------------------------------------");
        MENU:printf("\n\t\t\t\t\t\t   MENU");
        printf("\n-----------------------------------------------------------------------------------------------------");
        printf("\n\t\t\t1. Compress  Text");
        printf("\n\t\t\t2. Decompress Text");
        printf("\n\t\t\t3. exit\n");

        printf("\n\n\t\t\t->");
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            compress_txt();
            goto MENU;

        case 2:
            printf("\n\t\t\tSorry, this feature is not develop yet\n\n");
            
            goto MENU;
        case 3:
            exit(0);
        }
   
    }while (choice < 1 || choice>3);
    //clock_t begin = clock();

    compress_txt();
    decompress_txt();

    //clock_t end = clock();
    //double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    //printf("Exececution time : %f", time_spent);

    //return 0;

}
