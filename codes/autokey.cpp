#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encryptAutoKey(char *plaintext, char *key, char *ciphertext) {
    int i, j = 0;
    int textLen = strlen(plaintext);
    int keyLen = strlen(key);
    char fullKey[1000];

    strcpy(fullKey, key);
    strncat(fullKey, plaintext, textLen);  

    for (i = 0; i < textLen; i++) {
        if (isalpha(plaintext[i])) {
            char base = isupper(plaintext[i]) ? 'A' : 'a';
            char keyChar = tolower(fullKey[i]) - 'a';  
            ciphertext[i] = ((tolower(plaintext[i]) - 'a' + keyChar) % 26) + base;
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
    encryptAutoKey(plaintext, key, ciphertext);
    printf("%s", ciphertext);
    return 0;
}
