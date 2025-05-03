#include <stdio.h>
#include <string.h>
#include <ctype.h>

void stringEncryption(const char *text, const char *key, char *cipherText) {
    int length = strlen(key);
    for (int i = 0; i < length; i++) {
        int textChar = toupper(text[i]) - 'A';
        int keyChar = toupper(key[i]) - 'A';
        int sum = textChar + keyChar;
        
        if (sum > 25) {
            sum -= 26;
        }
        
        cipherText[i] = sum + 'A';
    }
    cipherText[length] = '\0';
}

int main() {
    char plaintext[1000];
    char key[1000];
    char ciphertext[1000];

    // Read input from file
    FILE *input = fopen("input.txt", "r");
    if (!input) return 1;

    fgets(key, sizeof(key), input);
    key[strcspn(key, "\n")] = '\0';
    fgets(plaintext, sizeof(plaintext), input);
    plaintext[strcspn(plaintext, "\n")] = '\0';
    fclose(input);

    // Check lengths match
    if (strlen(plaintext) != strlen(key)) {
        printf("Error: Plaintext and key must be same length\n");
        return 1;
    }

    // Convert both to uppercase
    for (int i = 0; plaintext[i]; i++) {
        plaintext[i] = toupper(plaintext[i]);
    }
    for (int i = 0; key[i]; i++) {
        key[i] = toupper(key[i]);
    }

    stringEncryption(plaintext, key, ciphertext);
    printf("%s", ciphertext);
    return 0;
}