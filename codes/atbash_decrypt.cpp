#include <stdio.h>
#include <string.h>
#include <ctype.h>

void decryptAtbash(char *ciphertext, char *plaintext) {
    int i, j = 0;
    for (i = 0; ciphertext[i] != '\0'; i++) {
        char c = toupper(ciphertext[i]);
        if (isalpha(c)) {
            plaintext[j++] = 'Z' - (c - 'A');
        } else if (isspace(c)) {
            plaintext[j++] = ' ';
        } else {
            plaintext[j++] = c;
        }
    }
    plaintext[j] = '\0';
}

int main() {
    char key[100]; // Not used
    char ciphertext[1000];
    char plaintext[1000];

    FILE *input = fopen("input.txt", "r");
    if (!input) {
        printf("Error opening file.\n");
        return 1;
    }

    fgets(key, sizeof(key), input); // Skip key
    fgets(ciphertext, sizeof(ciphertext), input);
    key[strcspn(key, "\n")] = 0;
    ciphertext[strcspn(ciphertext, "\n")] = 0;

    fclose(input);

    decryptAtbash(ciphertext, plaintext);
    printf("%s\n", plaintext);
    return 0;
}
