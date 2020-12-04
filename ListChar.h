#pragma once
#ifndef LISTCHAR_H
#define LISTCHAR_H
#include <stdio.h>
#include <stdlib.h>
#define MAXCHAR 10000000

typedef struct ListChar
{
    char letter;
    int occ;
    struct ListChar* next;
} ListChar;


ListChar* number_of_occurences(char string[MAXCHAR]);
ListChar* sort_listChar(ListChar* liste);
int  get_list_char_size(ListChar* list_characters);
int is_in_the_list(ListChar* l, char letter);
void free_list_char(ListChar* list);



#endif // !LISTCHAR_H
