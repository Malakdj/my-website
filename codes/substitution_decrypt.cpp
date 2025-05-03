#include <stdio.h>
#include <string.h>
#include <ctype.h>

void decryptSubstitution(char *ciphertext, char *plaintext, const char *keyMap) {
    char reverseMap[26];
    for (int i = 0; i < 26; i++) {
        reverseMap[keyMap[i] - 'A'] = 'A' + i;
    }

    int i, j = 0;
    for (i = 0; ciphertext[i] != '\0'; i++) {
        char c = toupper(ciphertext[i]);
        if (isalpha(c)) {
            plaintext[j++] = reverseMap[c - 'A'];
        } else if (isspace(c)) {
            plaintext[j++] = ' ';
        } else {
            plaintext[j++] = c;
        }
    }
    plaintext[j] = '\0';
}

int main() {
    char key[100];
    char ciphertext[1000];
    char plaintext[1000];
    char keyMap[26];

    FILE *input = fopen("input.txt", "r");
    if (!input) {
        printf("Error opening file.\n");
        return 1;
    }

    fgets(key, sizeof(key), input); // Read key (26 letters)
    fgets(ciphertext, sizeof(ciphertext), input);
    key[strcspn(key, "\n")] = 0;
    ciphertext[strcspn(ciphertext, "\n")] = 0;
    fclose(input);

    if (strlen(key) != 26) {
        printf("Invalid key length. Must be 26 characters.\n");
        return 1;
    }

    for (int i = 0; i < 26; i++) {
        keyMap[i] = toupper(key[i]);
    }

    decryptSubstitution(ciphertext, plaintext, keyMap);
    printf("%s\n", plaintext);
    return 0;
}
