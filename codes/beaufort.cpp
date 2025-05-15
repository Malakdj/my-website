#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encryptBeaufort(char *plaintext, char *key, char *ciphertext) {
    int i, j = 0;
    int textLen = strlen(plaintext);
    int keyLen = strlen(key);

    for (i = 0; i < textLen; i++) {
        if (isalpha(plaintext[i])) {
            char base = islower(plaintext[i]) ? 'a' : 'A';
            char plainChar = tolower(plaintext[i]) - 'a'; 
            char keyChar = tolower(key[j % keyLen]) - 'a'; 

            int cipherVal = (keyChar - plainChar + 26) % 26;
            ciphertext[i] = base + cipherVal;
            j++;
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[i] = '\0';
}

int main() {
    char plaintext[1000];
    char key[100];
    char ciphertext[1000];
    FILE *input = fopen("input.txt", "r");
    if (!input) {
        printf("Error opening file.\n");
        return 1;
    }

    fgets(key, sizeof(key), input);
    key[strcspn(key, "\n")] = 0;

    fgets(plaintext, sizeof(plaintext), input);
    plaintext[strcspn(plaintext, "\n")] = 0;

    fclose(input);
    encryptBeaufort(plaintext, key, ciphertext);
    printf("%s\n", ciphertext);
    return 0;
}
