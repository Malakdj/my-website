#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encryptPolybe(char *plaintext, char *ciphertext) {
    int i, j = 0;
    
    for (i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            char c = toupper(plaintext[i]);
            if (c == 'J') c = 'I'; 
            int index = c - 'A';
            if (index > 8) index--; 
            int row = index / 5 + 1;
            int col = index % 5 + 1;
            ciphertext[j++] = row + '0';
            ciphertext[j++] = col + '0';
        } else if (isspace(plaintext[i])) {
            ciphertext[j++] = ' ';
        } else {
            ciphertext[j++] = plaintext[i];
        }
    }
    ciphertext[j] = '\0';
}

int main() {
    char plaintext[1000];
    char key[100]; 
    char ciphertext[2000];

    FILE *input = fopen("input.txt", "r");
    if (!input) {
        printf("Error opening file.\n");
        return 1;
    }

    fgets(key, sizeof(key), input); 
    fgets(plaintext, sizeof(plaintext), input);
    plaintext[strcspn(plaintext, "\n")] = 0;

    fclose(input);

    encryptPolybe(plaintext, ciphertext);
    printf("%s\n", ciphertext);
    
    return 0;
}
