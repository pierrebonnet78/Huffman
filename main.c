#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXCHAR 10000 

typedef struct ListChar{
    char letter;
    int occ;
    struct ListChar* next;
}ListChar;

typedef struct Node{
    char letter;
    int occ;
    struct Node *right;
    struct Node *left;
}Node;

void display_tree(Node* tree){
    if(tree == NULL) {
        return;
    }
    display_tree(tree->left);
    printf("%d|%c    ",tree->occ, tree->letter);
    display_tree(tree->right);
}

long decimalToBinary(int decimalnum)
{
    long binarynum = 0;
    int rem, temp = 1;

    while (decimalnum != 0)
    {
        rem = decimalnum % 2;
        decimalnum = decimalnum / 2;
        binarynum = binarynum + rem * temp;
        temp = temp * 10;
    }
    return binarynum;
}

void letterToByte(char input[
    
], long bytes[])
{

    int len = strlen(input);
    int ascii[len];
    int i = 0;
    for (i; i < len; i++)
    {
        ascii[i] = (int)input[i];
    }
    for (i = 0; i < len; i++)
    {
        long temp = decimalToBinary(ascii[i]);
        bytes[i] = temp;
    }
}

void readtext(char *output)
{
    FILE *fp;
    char str[MAXCHAR];
    char *filename = "C:\\Users\\pierr\\OneDrive - Efrei\\Documents\\EFREI\\S03\\Algo\\C\\Project 1 Huffman Coding\\Alice.txt";

    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Could not open file %s", filename);
    }
    else
    { 
        while (fgets(str, MAXCHAR, fp) != NULL)
        {
            strncat(output, str, (sizeof(output) - strlen(str)));
        }
        fclose(fp);
    }
}

void writetext(long bytes[], int size)
{
    int num;
    FILE *fp;
    fp = fopen("C:\\Users\\pierr\\OneDrive - Efrei\\Documents\\EFREI\\S03\\Algo\\C\\Project 1 Huffman Coding\\Output.txt", "w");
    if (fp == NULL)
    {
        printf("\nError, Cannot open the file !");
    }
    else
    {
        for (int i = 0; i < size; i++)
        {
            fprintf(fp, "%ld", bytes[i]);
            if ((i + 2) % 10 == 1)
            {
                fprintf(fp, "\n");
            }
        }
        fclose(fp);
    }
}

void characters()
{
    FILE *fp;
    char str;
    char *filename = "C:\\Users\\pierr\\OneDrive - Efrei\\Documents\\EFREI\\S03\\Algo\\C\\Project 1 Huffman Coding\\Alice.txt";
    fp = fopen(filename, "r");
    int count = 0;
    while ((str = fgetc(fp)) != EOF)
    {
        count++;
    }
    printf("\nNumber of characters in Alice.txt : %d ", count);
    fclose(fp);
    filename = "C:\\Users\\pierr\\OneDrive - Efrei\\Documents\\EFREI\\S03\\Algo\\C\\Project 1 Huffman Coding\\Output.txt";
    fp = fopen(filename, "r");
    count = 0;
    while ((str = fgetc(fp)) != EOF)
    {
        count++;
    }
    printf("\nNumber of characters in Output.txt : %d ", count);
    fclose(fp);
}

ListChar* add_list_char(char lettre, int occurence){
    ListChar* mylist = (ListChar*)malloc(sizeof(ListChar));
    mylist->letter = lettre; 
    mylist->occ = occurence;
    mylist->next = NULL;
    return mylist;
}

void display_list_char(ListChar* mylist){
    printf("\n");
    if(mylist != NULL){
        ListChar* temp = mylist;
        while(temp != NULL){
            printf("%c appears %d times\n", temp->letter , temp->occ);
            temp = temp -> next;
        }
    }
}

ListChar* create_list_char(){
    ListChar* mylist = (ListChar*)malloc(sizeof(ListChar));
    mylist->letter = 'P';
    mylist->occ = 3;
    mylist->next = add_list_char('A', 2);
    mylist->next->next = add_list_char('M', 6);
    mylist->next->next->next = add_list_char('D', 1);
    mylist->next->next->next->next = add_list_char('N', 3);
    return mylist;
}

void list_remove(ListChar** mylist, char lettre ){
    if(*mylist != NULL){
        ListChar *temp = *mylist;
        ListChar *prev;
        while(temp != NULL && temp->letter == lettre){
            *mylist = temp->next;
            temp = *mylist;
        }
        while(temp != NULL){
            while(temp != NULL && temp-> letter != lettre){
                prev = temp;
                temp = temp->next;
            }

            if(temp == NULL){
                return;
            }
            prev->next = temp->next;
            temp = prev->next;
        }
    }
}

Node* smallest_item(ListChar** mylist){
    if(*mylist != NULL){
        ListChar* temp = (*mylist)->next;
        Node* min_node = (Node*)malloc(sizeof(Node));
        min_node->letter = (*mylist)->letter;
        min_node->occ = (*mylist)->occ;
        min_node ->left = NULL;
        min_node ->right = NULL;
        while(temp != NULL){
            if(min_node->occ > temp->occ){
                min_node->occ = temp->occ;
                min_node->letter = temp->letter;
            }
            temp = temp->next;
        }
        list_remove(mylist, min_node->letter);
        return min_node;
    }
}

Node* create_huffman_parents_node(Node* child1, Node* child2){
    Node* parent= (Node*)malloc(sizeof(Node));
    parent->occ = child1->occ + child2->occ;
    parent->letter = NULL;
    parent->right = child1;
    parent->left = child2;
    return parent;
}

int is_empty(ListChar* mylist){
    if(mylist == NULL){
        return 1;
    }
    return 0;
}

Node* huffman_tree(ListChar** mylist){
    Node* element_min = smallest_item(mylist);
    Node* element_min2 = smallest_item(mylist);
    Node* temp = create_huffman_parents_node(element_min, element_min2);
    Node* root;
    while(!is_empty(*mylist)){
        element_min = smallest_item(mylist);
        root = create_huffman_parents_node(temp, element_min);
        temp = root;
    }
    return root;
}


int main()
{
    /*
    char *text[MAXCHAR];
    readtext(text); // read the .txt file and store it the array 'text'.
    int len = strlen(text);
    long bytes[len];
    letterToByte(text, bytes); // convert each letter of the array 'text' in its binary representation and store them into array 'bytes'.
    writetext(bytes, len);     // write on an empty file 'Output.txt' what the array 'bytes' contains.
    characters();
    */
    ListChar* mylist = create_list_char();
    ListChar* element_min;

    Node* root = huffman_tree(&mylist);
    printf("%d|%c    ",root->occ, root->letter);
    printf("%d|%c    ",root->left->occ, root->left->letter);
    printf("%d|%c    ",root->right->occ, root->right->letter);
    printf("%d|%c    ",root->right->left->occ, root->right->left->letter);
    printf("%d|%c    ",root->right->right->occ, root->right->right->letter);
    printf("%d|%c    ",root->right->right->left->occ, root->right->right->left->letter);
    printf("%d|%c    ",root->right->right->right->occ, root->right->right->right->letter);
    printf("%d|%c    ",root->right->right->right->left->occ, root->right->right->right->left->letter);
    printf("%d|%c    ",root->right->right->right->right->occ, root->right->right->right->right->letter);
    return 0;
}
