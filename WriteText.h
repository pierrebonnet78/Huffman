#pragma once
#ifndef WRITE_TEXT_H
#define WRITE_TEXT_H
#include <stdio.h>
#include <stdlib.h>
#include "Letter.h"
#include "Node.h"

void reset_dico();
void write_text(long bytes[], int size);
void write_in_huffman_code(char* text, Node* avl);
Node* search_in_dico(Node* temp, char value);
#endif // !WRITE_TEXT_H