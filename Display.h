#pragma once
#ifndef HEADER_H
#define HEADER_H
#include <stdio.h>
#include <stdlib.h>
#include "Node.h"
#include "ListChar.h"

void display_tree(Node* node);
void display_list_of_occ(ListChar* list);
void character_comparaison();
void print_tab(Node* tab, int len);


#endif // !HEADER_H