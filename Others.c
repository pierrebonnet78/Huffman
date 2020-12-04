#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "Others.h"

long decimal_to_binary(int decimalnum) {
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

void letter_to_byte(char input[], long* bytes, int sizetext) {
    int* ascii = (int*)malloc(sizetext * sizeof(int));
    if (ascii != NULL) {
        int i;
        for (i = 0; i < sizetext; i++) {
            if (input[i] < 0 || input[i] > 127){
                input[i] = '?';
            }
            ascii[i] = input[i];
        }
        for (i = 0; i < sizetext; i++) {
            long temp = decimal_to_binary(ascii[i]);
            bytes[i] = temp;
        }
    }
    free(ascii);
}
