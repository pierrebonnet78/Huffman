#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXCHAR 100000

typedef struct ListChar
{
    char letter;
    int occ;
    struct ListChar *next;
} ListChar;

typedef struct Node
{
    char letter;
    int occ;
    struct Node *right;
    struct Node *left;
} Node;

typedef struct Queue
{
    int front;
    int rear;
    int size;
    struct Node **arrayofnode;
} Queue;

void display_tree(Node *tree)
{
    if (tree == NULL)
    {
        return;
    }
    display_tree(tree->left);
    printf("%d|%c    ", tree->occ, tree->letter);
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

void letterToByte(char input[], long bytes[])
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
            fprintf(fp, "%ld ", bytes[i]);
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

/*ListChar *add_list_char(char lettre, int occurence)
{
    ListChar *mylist = (ListChar *)malloc(sizeof(ListChar));
    mylist->letter = lettre;
    mylist->occ = occurence;
    mylist->next = NULL;
    return mylist;
}*/

void list_remove(ListChar **mylist, char lettre)
{
    if (*mylist != NULL)
    {
        ListChar *temp = *mylist;
        ListChar *prev;
        while (temp != NULL && temp->letter == lettre)
        {
            *mylist = temp->next;
            temp = *mylist;
        }
        while (temp != NULL)
        {
            while (temp != NULL && temp->letter != lettre)
            {
                prev = temp;
                temp = temp->next;
            }

            if (temp == NULL)
            {
                return;
            }
            prev->next = temp->next;
            temp = prev->next;
        }
    }
}

Node *createNode(char data, int occurence)
{
    Node *temp = (Node *)malloc(sizeof(Node));
    temp->left = NULL;
    temp->right = NULL;
    temp->letter = data;
    temp->occ = occurence;
    return temp;
}

Queue *createQueue(int size)
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    queue->front = -1;
    queue->rear = -1;
    queue->size = size;
    queue->arrayofnode = (Node **)malloc(queue->size * sizeof(Node *));
    return queue;
}

int isQueueSizeOne(Queue *queue)
{
    if ((queue->front == queue->rear) && (queue->front != -1))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int isQueueEmpty(Queue *queue)
{
    if (queue->front == -1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int isQueueFull(Queue *queue)
{
    if (queue->rear == queue->size - 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void enQueue(Queue *queue, Node *node)
{
    if (!isQueueFull(queue) && node != NULL)
    {
        queue->arrayofnode[++queue->rear] = node;
        if (queue->front == -1)
            ++queue->front;
    }
}

Node *deQueue(Queue *queue)
{
    if (!isQueueEmpty(queue))
    {
        Node *temp = queue->arrayofnode[queue->front];
        if (queue->front == queue->rear)
        { // There is only one item in the array
            queue->front = -1;
            queue->rear = -1;
        }
        else
        {
            ++queue->front;
        }
        return temp;
    }
}

Node *getFrontQueue(Queue *queue)
{
    if (isQueueEmpty(queue))
    {
        return NULL;
    }
    return queue->arrayofnode[queue->front];
}

Node *findMinTwoQueues(Queue *Queue1, Queue *Queue2)
{
    if (Queue1 != NULL && Queue2 != NULL)
    {
        // If queue 1 is empty, dequeue from queue 2
        if (isQueueEmpty(Queue1))
            return deQueue(Queue2);

        // If queue 2 is empty, dequeue from queue 1
        if (isQueueEmpty(Queue2))
            return deQueue(Queue1);

        // Else compare the front of the two queues and dequeue min
        if (getFrontQueue(Queue1)->occ < getFrontQueue(Queue2)->occ)
        {
            return deQueue(Queue1);
        }
        //Last possibility
        return deQueue(Queue2);
    }
}

int isLeaf(Node *root)
{
    if (root->left == NULL && root->right == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void printArray(int arr[], int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int getListCharactersSize(ListChar *list_characters)
{
    int size = 0;
    ListChar *temp = list_characters;
    if (temp != NULL)
    {

        while (temp->next != NULL)
        {
            size++;
            temp = temp->next;
        }
        return size;
    }
    return size;
}

Node *createHuffmanTreeWithQueue(list_characters)
{

    int size = getListCharactersSize(list_characters);
    Node *left, *right, *top;
    int i;
    ListChar *temp = list_characters;

    // 1 - Create 2 empty queues
    Queue *queue1 = createQueue(size);
    Queue *queue2 = createQueue(size);

    // 2 - Create a leaf node for each character of the data[] array, enqueu it to queue 1
    for (i = 0; i < size; i++)
    {
        enQueue(queue1, createNode(temp->letter, temp->occ));
        temp = temp->next;
    }
    while (!(isQueueEmpty(queue1) && isQueueSizeOne(queue2)))
    {
        // 3 - Dequeue two nodes with the min occurrence by looking at the front of both queues
        left = findMinTwoQueues(queue1, queue2);
        right = findMinTwoQueues(queue1, queue2);

        // 4 - Create new node with occurences equal to the sum of the two other nodes and enqueu this node to second queue
        top = createNode('$', left->occ + right->occ);
        top->left = left;
        top->right = right;
        enQueue(queue2, top);
    }
    return deQueue(queue2);
}

void printCodes(Node *root, int arr[], int top)
{
    // Assign 0 to left edge and recur
    if (root->left)
    {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }

    // Assign 1 to right edge and recur
    if (root->right)
    {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }

    // If this is a leaf node, then it contains one of the
    // input characters, print the character and its code
    // from arr[]
    if (isLeaf(root))
    {
        printf("%c : ", root->letter);
        printArray(arr, top);
    }
}

void HuffmanCodes(ListChar *list_characters)
{
    // Construct Huffman Tree
    Node *root = createHuffmanTreeWithQueue(list_characters);

    int arr[MAXCHAR];
    int top = 0;

    printCodes(root, arr, top);
    display_tree(root);
    treetotxt(root);
}


Node *removeElement(ListChar **mylist)
{
    if (*mylist != NULL)
    {
        Node* min_node = (Node*)malloc(sizeof(Node));
        min_node->letter = (*mylist)->letter;
        min_node->occ =(*mylist)->occ;
        min_node->left = NULL; 
        min_node->right = NULL;

        list_remove(mylist, min_node->letter);
        return min_node;
    }
}

Node *create_huffman_parents_node(Node *child1, Node *child2)
{
    Node *parent = (Node *)malloc(sizeof(Node));
    parent->occ = child1->occ + child2->occ;
    parent->letter = '$';
    parent->right = child1;
    parent->left = child2;
    return parent;
}

int is_empty(ListChar *mylist)
{
    if (mylist == NULL)
    {
        return 1;
    }
    return 0;
}

Node *create_huffman_tree(ListChar **mylist)
{

    Node *element_min = removeElement(mylist);
    Node *element_min2 = removeElement(mylist);
    Node *temp = create_huffman_parents_node(element_min, element_min2);
    Node *root;
    while (!is_empty(*mylist))
    {
        element_min = removeElement(mylist);
        root = create_huffman_parents_node(temp, element_min);
        temp = root;
    }
    return root;
}

int is_in_the_list(ListChar *l, char letter)
{ /// la pour simplifier mon code j'utilise la fonction is_in_the list de hephaistos pour savoir si un element est deja dans la liste ou non
    int i = 1;
    ListChar *temp;
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

ListChar *number_of_occurences(char string[MAXCHAR])
{ /// la c'est ma fonction nombre d'occurences j'ai mmis string[100] en parametre mais la taille a mettre sera donée par une autre fonction
    int i;
    ListChar *list = malloc(sizeof(ListChar));
    ListChar *temp = list, *temp2;
    if (strlen(string) > 0)
    {
        list->next = NULL; /// la j'initialise la premiere valeur de ma liste avec la premiere lettre du message.
        list->letter = string[0];
        list->occ = 1;

        for (i = 1; i < strlen(string); i++)
        { /// la si la lettre n'a jamais ete rencontree j'ajoute un noeud dns la liste.
            int pos = is_in_the_list(list, string[i]);
            if (pos == -1)
            {
                ListChar *new_letter = malloc(sizeof(ListChar));
                new_letter->letter = string[i];
                new_letter->occ = 1;
                new_letter->next = NULL;
                temp->next = new_letter;
                temp = temp->next;
            }
            else
            {
                int count = 1; /// ducoup dans le cas contraire je recherche la position grace a is_in_the_list et j'auguemente juste l'occurence de 1.
                temp2 = list;
                while (temp2 != NULL && count != pos)
                {
                    temp2 = temp2->next;
                    count += 1;
                }
                temp2->occ += 1;
            }
        }
        return list;
    }
}

ListChar *sortListChar(ListChar *liste) //sort the list of occurence by field 'occ' using BUBBLE SORTING
{
    if (liste == NULL)
        return NULL; // liste vide, rien à trier
    if (liste->next == NULL)
        return liste; // un seul élément, rien à trier

    ListChar *root = liste;

    int restart;
    do
    {
        // commence au début de la liste
        ListChar *previous = NULL;
        ListChar *element = root;
        ListChar *succeeding = element->next;
        restart = 0;

        while (succeeding != NULL)
        {
            if (succeeding->occ < element->occ)
            {
                // si le classement de l'élément et de son suivant est incorrect :

                // la liste devra être re-parcourue
                restart = 1;

                // inverse l'élément courant et son succeeding
                if (previous == NULL)
                {
                    root = succeeding;
                }
                else
                {
                    previous->next = succeeding;
                }
                element->next = succeeding->next;
                succeeding->next = element;

                // avance dans la liste
                previous = succeeding;
                succeeding = element->next;
            }
            else
            {
                // si le classement de l'élément et de son suivant est correct :

                // avance dans la liste
                previous = element;         // nouveau précédent = ancien élément
                element = element->next;    // nouvel élément = ancien suivant
                succeeding = element->next; // nouveau suivant = suivant du nouvel élément
            }
        }
    } while (restart);

    // retourne la nouvelle liste
    return root;
}

void display_list_of_occ(ListChar *list)
{ /// la c'etait juste pour tester si ca marchait j'avais besoin d'une fonction afficher peut etre utile au cas ou ...
    ListChar *temp = list;
    while (temp != NULL)
    {
        printf("\n %c : %d", temp->letter, temp->occ);

        temp = temp->next;
    }
}

void treetotxt(Node *huffman_tree)
{
    FILE *fp;
    Node *temp = huffman_tree;
    Node *root = huffman_tree;
    int size = 5;
    char result[MAXCHAR] = "0";
    char path_0[] = "0";
    char path_1[] = "1";
    fp = fopen("C:\\Users\\pierr\\OneDrive - Efrei\\Documents\\EFREI\\S03\\Algo\\C\\Project 1 Huffman Coding\\dico.txt", "w");
    int i = 0;
    int cpt = 0;

    if (fp == NULL)
    {
        printf("\nError, Cannot open the file 'dico.txt'");
    }
    else
    {
        while (temp->right != NULL && temp->left != NULL)
        {
            if (temp->left->left == NULL)
            {
                fprintf(fp, "%c : ", temp->left->letter);
                for (i = 0; i < cpt; i++)
                {
                    fprintf(fp, "1");
                }
                fprintf(fp, "0\n");
            }
            temp = temp->right;
            cpt++;
        }
    }
    fclose(fp);
}

int main()
{

    char text[MAXCHAR];
    readtext(text); // read the .txt file and store it the array 'text'.
    int len = strlen(text);
    long bytes[len];
    letterToByte(text, bytes); // convert each letter of the array 'text' in its binary representation and store them into array 'bytes'.
    writetext(bytes, len);     // write on an empty file 'Output.txt' what the array 'bytes' contains.
    //characters();

    ListChar *list_characters = number_of_occurences(text);
    sortListChar(list_characters);

    //  Node *root = create_huffman_tree(&list_characters);   ancienne méthode pour générer l'abre d'Huffman
    //treetotxt(root);   à modifier ne marche plus avec le nouvel arbre de Huffman

    display_list_of_occ(list_characters);
    HuffmanCodes(list_characters); //génére l'arbre de Huffman grace à deux Queues

    return 0;

}
