#include <stdio.h>
#include <stdlib.h>

void treetotxt(){
    FILE *File;
    Tree *temp = Huffman;
    int i, cpt = 0;
    /* Creating the dictionary (w+ = Open a text file for update (reading and writing), first truncating the file to zero length if it exists or creating the file if it doesn't */
    if ((File = fopen("dico.txt", "w+")) == NULL){
        /* Printing a custom message before the error message itself */
        perror("Error: ");
    }
    else{
        if (temp!=NULL){
            /* Going through the tree */
            while(temp->right!NULL && temp->left!=NULL){
                if(temp->left->left==NULL){
                    fputwc(temp->left->ListChar->data, File);
                    for (i=0;i<cpt;i++){
                        /* Writing 1 in ASCII code */
                        fputwc(49,File);
                    }
                    /* Writing 0 in ASCII code */
                    fputwc(48,File);
                    /* Breaking a line in ASCII code */
                    fputwc(10,File);
                }
                temp=temp->right;
                cpt++;
            }
            fputwc(temp->ListChar->data,File);
            /* Checking the number of letters in the folder */
            if (cpt==0){
                fputwc(48,File);
            }
            else{
                for (i=0,i<cpt;i++){
                    fputwc(49,File);
                }
            }
        }
        /* Closing the file to save the changes applied */
        fclose(File);
    }
