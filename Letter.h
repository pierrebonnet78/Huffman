#pragma once
#ifndef LETTER_H
#define LETTER_H
#include <stdio.h>
#include <stdlib.h>

typedef struct Letter
{
    char lettre[1];
    char code[20];
    struct Node* next;
}Letter;

void free_list_char_huffman_code(Letter* list);
void delete_last_node_letter(Letter* head);
Letter* sort_listChar_v2(Letter* liste);
#endif // !LETTER8H