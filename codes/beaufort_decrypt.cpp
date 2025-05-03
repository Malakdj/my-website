#include <stdio.h>
#include <string.h>
#include <ctype.h>

void decryptBeaufort(char *ciphertext, char *key, char *plaintext) {
    int i, j = 0;
    int textLen = strlen(ciphertext);
    int keyLen = strlen(key);

    for (i = 0; i < textLen; i++) {
        if (isalpha(ciphertext[i])) {
            char base = islower(ciphertext[i]) ? 'a' : 'A';
            char cipherChar = tolower(ciphertext[i]) - 'a';  // 0–25
            char keyChar = tolower(key[j % keyLen]) - 'a';    // 0–25

            int plainVal = (keyChar - cipherChar + 26) % 26;
            plaintext[i] = base + plainVal;
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

    // Reading input from file
    FILE *input = fopen("input.txt", "r");
    if (!input) {
        printf("Error opening file.\n");
        return 1;
    }

    // Read key and ciphertext from file
    fgets(key, sizeof(key), input);
    key[strcspn(key, "\n")] = 0;

    fgets(ciphertext, sizeof(ciphertext), input);
    ciphertext[strcspn(ciphertext, "\n")] = 0;

    fclose(input);

    // Decrypt using Beaufort cipher
    decryptBeaufort(ciphertext, key, plaintext);
    printf("%s\n", plaintext);
    return 0;
}
