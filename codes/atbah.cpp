#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encryptAtbah(char *plaintext, char *ciphertext) {
    int i, j = 0;
    for (i = 0; plaintext[i] != '\0'; i++) {
        char c = toupper(plaintext[i]);
        if (isalpha(c)) {
            ciphertext[j++] = 'Z' - (c - 'A');
        } else if (isspace(c)) {
            ciphertext[j++] = ' ';
        } else {
            ciphertext[j++] = c;
        }
    }
    ciphertext[j] = '\0';
}

int main() {
    char key[100]; // Not used
    char plaintext[1000];
    char ciphertext[1000];

    FILE *input = fopen("input.txt", "r");
    if (!input) {
        printf("Error opening file.\n");
        return 1;
    }

    fgets(key, sizeof(key), input); // Skip key
    fgets(plaintext, sizeof(plaintext), input);
    key[strcspn(key, "\n")] = 0;
    plaintext[strcspn(plaintext, "\n")] = 0;

    fclose(input);

    encryptAtbah(plaintext, ciphertext);
    printf("Encrypted text: %s\n", ciphertext);
    return 0;
}
