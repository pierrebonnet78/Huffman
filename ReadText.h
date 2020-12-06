#pragma once
#ifndef READ_TEXT_H
#define READ_TEXT_H
#include <stdio.h>
#include <stdlib.h>
#include "ListChar.h"
#include "Letter.h"
#define MAXCHAR 1000000

void read_text(char* output);
Letter* read_and_store_dico(char* text, ListChar* list_characters);
void read_text_compressed(char* output);


#endif // !READ_TEXT_H