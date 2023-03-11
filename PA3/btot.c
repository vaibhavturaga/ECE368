#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
void BinaryToText(char *inputFile) {
    FILE* ifile = fopen(inputFile, "rb");

    short size;
    fread(&size, sizeof(short), 1, ifile);
    printf("%hd\n", size);

    for(int i = 0; i < 4; i++){
        int val;
        fread(&val, sizeof(int), 1, ifile);
        printf("%d, ", val);
    }


}

int main(int argc, char* argv[]) {
    BinaryToText(argv[1]);
}