#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXCHAR 100000

typedef struct ListChar
{
    char letter;
    int occ;
    struct ListChar* next;
} ListChar;

typedef struct Node
{
    char letter;
    int occ;
    struct Node* right;
    struct Node* left;
} Node;

typedef struct Queue
{
    int front;
    int rear;
    int size;
    struct Node** arrayofnode;
} Queue;

typedef struct Letter
{
    char lettre[5];
    char code[10];
    struct Node* next;
}Letter;

typedef struct Dictionnary
{
    Letter* letter;
    int size;
} Dictionnary;

void readtext(char* output)
{
    FILE* fp;
    fp = NULL;
    char str[MAXCHAR];
    char* filename = "C:\\Users\\pierr\\OneDrive - Efrei\\Documents\\EFREI\\S03\\Algo\\C\\Huffman Project\\Huffman Project\\Alice.txt";
    fp = fopen( filename, "r");
    if (fp != NULL) {
        while (fgets(str, MAXCHAR, fp) != NULL)
        {
            strncat(output, str, (sizeof(output) - strlen(str)));
        }
        fclose(fp);
    }
    else {
        printf("Problem in opening Alice.txt");
    }
}

long decimalToBinary(int decimalnum) {
    long binarynum = 0;
    int rem, temp = 1;
    while (decimalnum != 0) {
        rem = decimalnum % 2;
        decimalnum = decimalnum / 2;
        binarynum = binarynum + rem * temp;
        temp = temp * 10;
    }
    return binarynum;
}

void letterToByte(char input[], long* bytes, int sizetext){
    int *ascii = (int*)malloc(sizetext * sizeof(int));
    if (ascii != NULL) {
        int i;
        for (i = 0; i < sizetext; i++){
            ascii[i] = input[i];
        }
        for (i = 0; i < sizetext; i++){
            long temp = decimalToBinary(ascii[i]);
            bytes[i] = temp;
        }
    }
    free(ascii);
}

void writetext(long bytes[], int size)
{
    
    FILE* fp;
    fp = NULL;
    fp = fopen("C:\\Users\\pierr\\OneDrive - Efrei\\Documents\\EFREI\\S03\\Algo\\C\\Huffman Project\\Huffman Project\\Output.txt", "w");
    if (fp != NULL){
        for (int i = 0; i < size; i++)
        {
            fprintf(fp, "%ld ", bytes[i]);
            if ((i + 2) % 10 == 1)
            {
                fprintf(fp, "\n");
            }
        }
        fclose(fp);
    }
    else {
        printf("\nError in openning Output.txt");
    }
}

void character_comparaison()
{
    FILE* fp;
    fp = NULL;
    char str;
    char* filename = "C:\\Users\\pierr\\OneDrive - Efrei\\Documents\\EFREI\\S03\\Algo\\C\\Huffman Project\\Huffman Project\\Alice.txt";
    fp = fopen(filename, "r");
    if (fp != NULL) {
        int count = 0;
        while ((str = fgetc(fp)) != EOF)
        {
            count++;
        }
        printf("\nNumber of characters in Alice.txt : %d ", count);
        fclose(fp);
    }
    else {
        printf("Problem in openning Alice.txt");
    }
    fp = NULL;
    filename = "C:\\Users\\pierr\\OneDrive - Efrei\\Documents\\EFREI\\S03\\Algo\\C\\Huffman Project\\Huffman Project\\Output.txt";
    fp = fopen(filename, "r");
    if (fp != NULL) {
        int count = 0;
        while ((str = fgetc(fp)) != EOF)
        {
            count++;
        }
        printf("\nNumber of characters in Output.txt : %d ", count);
        fclose(fp);
    }
    else {
        printf("Problem in openning Output.txt");
    }
}

int is_in_the_list(ListChar* l, char letter)
{ /// la pour simplifier mon code j'utilise la fonction is_in_the list de hephaistos pour savoir si un element est deja dans la liste ou non
    int i = 1;
    ListChar* temp;
    temp = l;
    while (temp != NULL)
    {
        if (temp->letter == letter)
        {
            return i;
        }
        temp = temp->next;
        i++;
    }
    return -1;
}

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
        if (strlen(string) > 0){
            list->next = NULL; /// la j'initialise la premiere valeur de ma liste avec la premiere lettre du message.
            list->letter = string[0];
            list->occ = 1;

            for (i = 1; i < strlen(string); i++){ /// la si la lettre n'a jamais ete rencontree j'ajoute un noeud dns la liste.
                int pos = is_in_the_list(list, string[i]);
                if (pos == -1){
                    ListChar* new_letter =(ListChar*)malloc(sizeof(ListChar));
                    if (new_letter != NULL) {
                        new_letter->letter = string[i]; 
                        new_letter->occ = 1;
                        new_letter->next = NULL;
                        temp->next = new_letter;
                        temp = temp->next;
                    }
                }
                else{
                    int count = 1; /// ducoup dans le cas contraire je recherche la position grace a is_in_the_list et j'auguemente juste l'occurence de 1.
                    temp2 = list;
                    while (temp2 != NULL && count != pos){
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

void display_list_of_occ(ListChar* list)  //test function
{ 
    ListChar* temp = list;
    while (temp != NULL)
    {
        printf("\n %c : %d", temp->letter, temp->occ);

        temp = temp->next;
    }
}

ListChar* sortListChar(ListChar* liste) //sort the list of occurence by field 'occ' using BUBBLE SORTING
{
    if (liste == NULL)
        return NULL; // liste vide, rien à trier
    if (liste->next == NULL)
        return liste; // un seul élément, rien à trier
    ListChar* root = liste;
    int restart;
    do{
        // commence au début de la liste
        ListChar* previous = NULL;
        ListChar* element = root;
        ListChar* succeeding = element->next;
        restart = 0;
        while (succeeding != NULL){
            if (succeeding->occ < element->occ){
                // si le classement de l'élément et de son suivant est incorrect :

                // la liste devra être re-parcourue
                restart = 1;
                // inverse l'élément courant et son succeeding
                if(previous == NULL){
                    root = succeeding;
                }
                else{
                    previous->next = succeeding;
                }
                element->next = succeeding->next;
                succeeding->next = element;
                // avance dans la liste
                previous = succeeding;
                succeeding = element->next;
            }
            else{
                // si le classement de l'élément et de son suivant est correct :
                // avance dans la liste
                previous = element;         // nouveau précédent = ancien élément
                element = element->next;    // nouvel élément = ancien suivant
                succeeding = element->next; // nouveau suivant = suivant du nouvel élément
            }
        }
    }while (restart);
    return root;
}

Node* createNode(char data, int occurence)
{
    Node* temp = (Node*)malloc(sizeof(Node));
    if (temp != NULL) {
        temp->left = NULL;
        temp->right = NULL;
        temp->letter = data;
        temp->occ = occurence;
    }
    return temp;
}

Queue* createQueue(int size)
{
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if (queue != NULL){
        queue->front = -1;
        queue->rear = -1;
        queue->size = size;
        queue->arrayofnode = (Node**)malloc(queue->size * sizeof(Node*));
    }
    return queue;
}

int isQueueSizeOne(Queue* queue)
{
    if ((queue->front == queue->rear) && (queue->front != -1)){
        return 1;
    }
    else{
        return 0;
    }
}

int isQueueEmpty(Queue* queue)
{
    if (queue->front == -1){
        return 1;
    }
    else{
        return 0;
    }
}

int isQueueFull(Queue* queue)
{
    if (queue->rear == queue->size - 1){
        return 1;
    }
    else{
        return 0;
    }
}

void enQueue(Queue* queue, Node* node)
{
    if (!isQueueFull(queue) && node != NULL){
        queue->arrayofnode[++queue->rear] = node;
        if (queue->front == -1) {
            ++queue->front;
        }
    }
}

Node* deQueue(Queue* queue)
{
    if (!isQueueEmpty(queue)){
        Node* temp = queue->arrayofnode[queue->front];
        if (queue->front == queue->rear){ // There is only one item in the array
            queue->front = -1;
            queue->rear = -1;
        }
        else{
            ++queue->front;
        }
        return temp;
    }
}

Node* getFrontQueue(Queue* queue)
{
    if (isQueueEmpty(queue)){
        return NULL;
    }
    return queue->arrayofnode[queue->front];
}

Node* findMinTwoQueues(Queue* Queue1, Queue* Queue2)
{
    if (Queue1 != NULL && Queue2 != NULL){
        // If queue 1 is empty, dequeue from queue 2
        if (isQueueEmpty(Queue1)) {
            return deQueue(Queue2);
        }

        // If queue 2 is empty, dequeue from queue 1
        if (isQueueEmpty(Queue2)) {
            return deQueue(Queue1);
        }

        // Else compare the front of the two queues and dequeue min
        if (getFrontQueue(Queue1)->occ < getFrontQueue(Queue2)->occ){
            return deQueue(Queue1);
        }
        //Last possibility
        return deQueue(Queue2);
    }
}

int isLeaf(Node* root)
{
    if (root->left == NULL && root->right == NULL){
        return 1;
    }
    else{
        return 0;
    }
}

void createDico(int arr[], int n, Node* root)
{
    FILE* fp;
    fp = NULL;
    char* filename = "C:\\Users\\pierr\\OneDrive - Efrei\\Documents\\EFREI\\S03\\Algo\\C\\Huffman Project\\Huffman Project\\Dico.txt";
    fp = fopen(filename, "a");
    int i;
    if (fp != NULL) {
        fprintf(fp, "%c ", root->letter);
        for (i = 0; i < n; i++) {
            fprintf(fp, "%d", arr[i]);
        }
        fprintf(fp, "\n");
        fclose(fp);
    }
    else {
        printf("Problem in openning Dico.txt");
    }
    
}


int getListCharactersSize(ListChar* list_characters)
{
    int size = 0;
    ListChar* temp = list_characters;
    if (temp != NULL){
        while (temp->next != NULL){
            size++;
            temp = temp->next;
        }
        return size;
    }
    return size;
}

Node* createHuffmanTreeWithQueue(ListChar* list_characters)
{
    int size;
    size = getListCharactersSize(list_characters) +1 ;
    Node* left, * right, * top;
    int i;
    ListChar* temp = list_characters;

    // Create 2 empty queues
    Queue* queue1 = createQueue(size);
    Queue* queue2 = createQueue(size);

    // Create a leaf node for each character of the data[] array, enqueu it to queue 1
    for (i = 0; i < size; i++){
        enQueue(queue1, createNode(temp->letter, temp->occ));
        temp = temp->next;
    }
    while (!(isQueueEmpty(queue1) && isQueueSizeOne(queue2))){
        // Dequeue two nodes with the min occurrence by looking at the front of both queues
        left = findMinTwoQueues(queue1, queue2);
        right = findMinTwoQueues(queue1, queue2);

        // Create new node with occurences equal to the sum of the two other nodes and enqueu this node to second queue
        top = createNode('$', left->occ + right->occ);
        top->left = left;
        top->right = right;
        enQueue(queue2, top);
    }
    return deQueue(queue2);
}


void printCodes(Node* root, int arr[], int top)
{
    // Assign 0 to left edge and recur
    if (root->left) {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }
    // Assign 1 to right edge and recur
    if (root->right) {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }
    // If this is a leaf node, then it contains one of the
    // input characters, print the character and its code
    // from arr[]
    if (isLeaf(root)) {
        createDico(arr, top, root);
    }
}

Node* huffman_code(ListChar* list_characters)
{
    // Construct Huffman Tree
    Node* root = createHuffmanTreeWithQueue(list_characters);

    int arr[MAXCHAR];
    int top = 0;
    printCodes(root, arr, top);
    return root;
 
}


Letter* translate_text(char* text, ListChar* list_characters) {
    FILE* fp;
    fp = NULL;
    char str[MAXCHAR];
    char* filename = "C:\\Users\\pierr\\OneDrive - Efrei\\Documents\\EFREI\\S03\\Algo\\C\\Huffman Project\\Huffman Project\\Dico.txt";
    fp = fopen(filename, "r");
    if (fp != NULL) {
        Letter* root = (Letter*)malloc(sizeof(Letter));
        Letter* temp = root;

        while (fgets(str, MAXCHAR, fp) != NULL) {
            //printf("%s\n", str);
            if (temp != NULL) {
                sscanf(str, "%s %s", temp->lettre, temp->code);
                temp->next = (Letter*)malloc(sizeof(Letter));
                temp = temp->next;
            }
        }
        temp->next = NULL;
        fclose(fp);
        return root;
    }
    else {
        printf("\nProblem in opening Dico.txt");
        return 0;
    }
}



void write_in_huffman_code(char* text, Letter* list_characters_huffman_code) {
    FILE* fp;
    fp = NULL;
    fp = fopen("C:\\Users\\pierr\\OneDrive - Efrei\\Documents\\EFREI\\S03\\Algo\\C\\Huffman Project\\Huffman Project\\OutputHuffmanCode.txt", "w");
    if (fp != NULL) {
        int size, i;
        size = strlen(text);
        Letter* temp = list_characters_huffman_code;
        for (i = 0; i < size; i++) {
            while (temp != NULL) {
                if (*temp->lettre == text[i]) {
                    fprintf(fp, "%s ", temp->code);
                }
                temp = temp->next;
            }
            temp = list_characters_huffman_code;
        }
        fclose(fp);
    }
    else {
        printf("\nProblem in opening OutputHuffmanCode.txt");
    }
    
}

void reset_dico() {
    FILE* fp;
    fp = NULL;
    fp = fopen("C:\\Users\\pierr\\OneDrive - Efrei\\Documents\\EFREI\\S03\\Algo\\C\\Huffman Project\\Huffman Project\\Dico.txt", "w");
    fclose(fp);
}

int main()
{
    char text[MAXCHAR];
    readtext(text);
    int sizetext;
    sizetext = (int)strlen(text);
    long* bytes = (long*)malloc(sizetext * sizeof(long));
    letterToByte(text, bytes, sizetext);
    writetext(bytes, sizetext);
    free(bytes);
    //character_comparaison();
    
    ListChar* list_characters = NULL;
    list_characters = number_of_occurences(text);

    sortListChar(list_characters);
    //display_list_of_occ(list_characters);
    

    reset_dico();
    Node* root;
    root = huffman_code(list_characters);

    
    Letter* list_characters_huffman_code = NULL;

    list_characters_huffman_code = translate_text(text, list_characters);
    Letter* temp = list_characters_huffman_code;

    while (temp != NULL) {
        printf("%s %s\n", temp->lettre, temp->code);
        temp = temp->next;
    }

    write_in_huffman_code(text, list_characters_huffman_code);

    free(list_characters);

    return 0;

}