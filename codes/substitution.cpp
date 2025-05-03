#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encryptSubstitution(char *plaintext, char *ciphertext, const char *keyMap) {
    int i, j = 0;
    for (i = 0; plaintext[i] != '\0'; i++) {
        char c = toupper(plaintext[i]);
        if (isalpha(c)) {
            ciphertext[j++] = keyMap[c - 'A'];
        } else if (isspace(c)) {
            ciphertext[j++] = ' ';
        } else {
            ciphertext[j++] = c;
        }
    }
    ciphertext[j] = '\0';
}

int main() {
    char key[100];
    char plaintext[1000];
    char ciphertext[1000];
    char keyMap[26];

    FILE *input = fopen("input.txt", "r");
    if (!input) {
        printf("Error opening file.\n");
        return 1;
    }

    fgets(key, sizeof(key), input); // Read key (26 uppercase letters)
    fgets(plaintext, sizeof(plaintext), input);
    key[strcspn(key, "\n")] = 0;
    plaintext[strcspn(plaintext, "\n")] = 0;
    fclose(input);

    if (strlen(key) != 26) {
        printf("Invalid key length. Must be 26 characters.\n");
        return 1;
    }

    for (int i = 0; i < 26; i++) {
        keyMap[i] = toupper(key[i]);
    }

    encryptSubstitution(plaintext, ciphertext, keyMap);
    printf("%s\n", ciphertext);
    return 0;
}
