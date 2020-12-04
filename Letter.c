#include <stdio.h>
#include <stdlib.h>
#include "Letter.h"


void free_list_char_huffman_code(Letter* list) {
    Letter* temp;
    while (list != NULL) {
        temp = list;
        list = list->next;
        free(temp);
    }
}

Letter* sort_listChar_v2(Letter* liste) //sort the list of Letter by ascii charactercs using BUBBLE SORTING
{
    if (liste == NULL)
        return NULL;
    if (liste->next == NULL)
        return liste;
    Letter* root = liste;
    int restart;
    do {

        Letter* previous = NULL;
        Letter* element = root;
        Letter* succeeding = element->next;
        restart = 0;
        while (succeeding != NULL) {
            if (succeeding->lettre[0] < element->lettre[0]) {
                restart = 1;
                if (previous == NULL) {
                    root = succeeding;
                }
                else {
                    previous->next = succeeding;
                }
                element->next = succeeding->next;
                succeeding->next = element;
                previous = succeeding;
                succeeding = element->next;
            }
            else {
                previous = element;
                element = element->next;
                succeeding = element->next;
            }
        }
    } while (restart);
    return root;
}

void delete_last_node_letter(Letter* head) {
    Letter* toDelete;
    Letter* secondLastNode;
    if (head != NULL) {
        toDelete = head;
        secondLastNode = head;
        while (toDelete->next != NULL) {
            secondLastNode = toDelete;
            toDelete = toDelete->next;
        }
        if (toDelete == head) {
            head = NULL;
        }
        else {
            secondLastNode->next = NULL;
        }
        free(toDelete);
    }
}

