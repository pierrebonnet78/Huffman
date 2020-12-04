#include <stdio.h>
#include <stdlib.h>
#include "ListChar.h"




ListChar* number_of_occurences(char string[MAXCHAR])
{
    int i;
    ListChar* list = (ListChar*)malloc(sizeof(ListChar));
    ListChar* temp = list, * temp2;
    for (i = 0; i < strlen(string); i++) {
        if (string[i] == ' ') {
            string[i] = '#'; // equivalent de espace
        }
    }
    for (i = 0; i < strlen(string); i++) {
        if (string[i] == 10) {
            string[i] = '%';  // equivalent de retour a la ligne
        }
    }

    if (list != NULL) {
        if (strlen(string) > 0) {
            list->next = NULL; /// la j'initialise la premiere valeur de ma liste avec la premiere lettre du message.
            list->letter = string[0];
            list->occ = 1;

            for (i = 1; i < strlen(string); i++) { /// la si la lettre n'a jamais ete rencontree j'ajoute un noeud dns la liste.
                int pos = is_in_the_list(list, string[i]);
                if (pos == -1) {
                    ListChar* new_letter = (ListChar*)malloc(sizeof(ListChar));
                    if (new_letter != NULL) {
                        new_letter->letter = string[i];
                        new_letter->occ = 1;
                        new_letter->next = NULL;
                        temp->next = new_letter;
                        temp = temp->next;
                    }
                }
                else {
                    int count = 1; /// ducoup dans le cas contraire je recherche la position grace a is_in_the_list et j'auguemente juste l'occurence de 1.
                    temp2 = list;
                    while (temp2 != NULL && count != pos) {
                        temp2 = temp2->next;
                        count += 1;
                    }
                    temp2->occ += 1;
                }
            }
            return list;
        }
    }
    else {
        printf("Memory Allocation problem.");
    }
    return NULL;
}

ListChar* sort_listChar(ListChar* liste ) //sort the list of occurence by field 'occ' using BUBBLE SORTING
{
    if (liste == NULL)
        return NULL;
    if (liste->next == NULL)
        return liste;
    ListChar* root = liste;
    int restart;
    do {

        ListChar* previous = NULL;
        ListChar* element = root;
        ListChar* succeeding = element->next;
        restart = 0;
        while (succeeding != NULL) {
            if (succeeding->occ< element->occ) {
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

int get_list_char_size(ListChar* list_characters)
{
    int size = 0;
    ListChar* temp = list_characters;
    if (temp != NULL) {
        while (temp->next != NULL) {
            size++;
            temp = temp->next;
        }
        return size;
    }
    return size;
}

int is_in_the_list(ListChar* l, char letter){ 
    int i = 1;
    ListChar* temp;
    temp = l;
    while (temp != NULL){
        if (temp->letter == letter){
            return i;
        }
        temp = temp->next;
        i++;
    }
    return -1;
}

void free_list_char(ListChar* list) {
    ListChar* temp;
    while (list != NULL) {
        temp = list;
        list = list->next;
        free(temp);
    }
}

