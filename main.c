#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXCHAR 10000

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

int main()
{

    char *text[MAXCHAR];
    readtext(text); // read the .txt file and store it the array 'text'.
    int len = strlen(text);
    long bytes[len];
    letterToByte(text, bytes); // convert each letter of the array 'text' in its binary representation and store them into array 'bytes'.
    writetext(bytes, len);     // write on an empty file 'Output.txt' what the array 'bytes' contains.
    characters();
    return 0;
}
