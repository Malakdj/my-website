#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encryptTrithemus(char *plaintext, char *ciphertext) {
    int i, j = 0;
    
    for (i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            char c = toupper(plaintext[i]);
            int shift = i % 26;
            char encrypted = ((c - 'A' + shift) % 26) + 'A';
            ciphertext[j++] = encrypted;
        } else if (isspace(plaintext[i])) {
            ciphertext[j++] = ' ';
        } else {
            ciphertext[j++] = plaintext[i];
        }
    }
    ciphertext[j] = '\0';
}

int main() {
    char plaintext[1000];
    char key[100]; // not used for Trithémus
    char ciphertext[1000];

    // Read input from file
    FILE *input = fopen("input.txt", "r");
    if (!input) {
        printf("Error opening file.\n");
        return 1;
    }

    fgets(key, sizeof(key), input); // Skip key line
    fgets(plaintext, sizeof(plaintext), input);
    plaintext[strcspn(plaintext, "\n")] = 0;

    fclose(input);

    encryptTrithemus(plaintext, ciphertext);
    printf("%s\n", ciphertext);

    return 0;
}
