#include <stdio.h>
#include <string.h>
#include <ctype.h>

void decryptTrithemus(char *ciphertext, char *plaintext) {
    int i, j = 0;

    for (i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char c = toupper(ciphertext[i]);
            int shift = i % 26;
            char decrypted = ((c - 'A' - shift + 26) % 26) + 'A';
            plaintext[j++] = decrypted;
        } else if (isspace(ciphertext[i])) {
            plaintext[j++] = ' ';
        } else {
            plaintext[j++] = ciphertext[i];
        }
    }
    plaintext[j] = '\0';
}

int main() {
    char ciphertext[1000];
    char key[100]; // not used for Trithémus
    char plaintext[1000];

    // Read input from file
    FILE *input = fopen("input.txt", "r");
    if (!input) {
        printf("Error opening file.\n");
        return 1;
    }

    fgets(key, sizeof(key), input); // Skip key line
    fgets(ciphertext, sizeof(ciphertext), input);
    ciphertext[strcspn(ciphertext, "\n")] = 0;

    fclose(input);

    decryptTrithemus(ciphertext, plaintext);
    printf("%s\n", plaintext);

    return 0;
}
