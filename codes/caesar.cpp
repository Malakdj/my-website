#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_LEN 1000

void encryptCaesar(char *text, int key) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            text[i] = (text[i] - base + key) % 26 + base;
        }
    }
}

int main() {
    FILE *inputFile = fopen("input.txt", "r");
    if (inputFile == NULL) {
        printf("Error: Unable to open input file!\n");
        return 1;
    }
    
    int key;
    char message[MAX_LEN];
    
    
    fscanf(inputFile, "%d", &key);
    fgetc(inputFile); 
    fgets(message, MAX_LEN, inputFile);
    fclose(inputFile);

    encryptCaesar(message, key);

    printf("Encrypted Message: %s", message);
    
    return 0;
}
