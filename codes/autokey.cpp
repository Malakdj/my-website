#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encryptAutoKey(char *plaintext, char *key, char *ciphertext) {
    int i, j = 0;
    int textLen = strlen(plaintext);
    int keyLen = strlen(key);
    char fullKey[1000];

    // Start with the initial key and append plaintext to it for dynamic key expansion
    strcpy(fullKey, key);
    strncat(fullKey, plaintext, textLen);  // Append the entire plaintext to key (correctly handle key length)

    for (i = 0; i < textLen; i++) {
        if (isalpha(plaintext[i])) {
            char base = isupper(plaintext[i]) ? 'A' : 'a';
            char keyChar = tolower(fullKey[i]) - 'a';  // Use the evolving key for each character
            ciphertext[i] = ((tolower(plaintext[i]) - 'a' + keyChar) % 26) + base;
        } else {
            ciphertext[i] = plaintext[i];  // Non-alphabet characters remain unchanged
        }
    }
    ciphertext[i] = '\0';  // Null-terminate the ciphertext
}

int main() {
    char plaintext[1000];
    char key[100];
    char ciphertext[1000];

    // Reading input from file
    FILE *input = fopen("input.txt", "r");
    if (!input) {
        printf("Error opening file.\n");
        return 1;
    }

    // Read key and plaintext from file
    fgets(key, sizeof(key), input);
    key[strcspn(key, "\n")] = 0;  // Remove newline character
    fgets(plaintext, sizeof(plaintext), input);
    plaintext[strcspn(plaintext, "\n")] = 0;  // Remove newline character
    fclose(input);

    // Encrypt the plaintext using AutoKey cipher
    encryptAutoKey(plaintext, key, ciphertext);

    // Print the encrypted message
    printf("%s", ciphertext);
    return 0;
}
