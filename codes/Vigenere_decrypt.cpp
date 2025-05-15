#include <stdio.h>
#include <string.h>
#include <ctype.h>

void decryptVigenere(char *ciphertext, char *key, char *plaintext) {
    int i, j = 0;
    int textLen = strlen(ciphertext);
    int keyLen = strlen(key);

    for (i = 0; i < textLen; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            char keyChar = tolower(key[j % keyLen]) - 'a';
            plaintext[i] = ((tolower(ciphertext[i]) - 'a' - keyChar + 26) % 26) + base;  
            j++;
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[i] = '\0';
}

int main() {
    char ciphertext[1000];
    char key[100];
    char plaintext[1000];
    FILE *input = fopen("input.txt", "r");
    if (!input) {
        printf("Error opening input file\n");
        return 1;
    }

    fgets(key, sizeof(key), input);
    key[strcspn(key, "\n")] = 0;
    fgets(ciphertext, sizeof(ciphertext), input);
    ciphertext[strcspn(ciphertext, "\n")] = 0;
    fclose(input);

    decryptVigenere(ciphertext, key, plaintext);
    printf("%s", plaintext);
    return 0;
}