#include <stdio.h>
#include <iostream>

void printIfLessThan50(unsigned char x) {
    if (x < 50) {
        printf("%c is less than 50!", x);
    }
}

int main(int argc, char ** argv) {
    printIfLessThan50(20);
    return 0;
}