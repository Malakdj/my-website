#include <stdio.h>
#include <string.h>
#include <ctype.h>

const char polybiusSquare[5][5] = {
    {'A', 'B', 'C', 'D', 'E'},
    {'F', 'G', 'H', 'I', 'K'},
    {'L', 'M', 'N', 'O', 'P'},
    {'Q', 'R', 'S', 'T', 'U'},
    {'V', 'W', 'X', 'Y', 'Z'}
};

void decryptPolybe(char *ciphertext, char *plaintext) {
    int i = 0, j = 0;
    while (ciphertext[i] != '\0') {
        if (isspace(ciphertext[i])) {
            plaintext[j++] = ' ';
            i++;
        } else if (isdigit(ciphertext[i]) && isdigit(ciphertext[i+1])) {
            int row = (ciphertext[i] - '0') - 1;
            int col = (ciphertext[i+1] - '0') - 1;
            if (row >= 0 && row < 5 && col >= 0 && col < 5) {
                plaintext[j++] = tolower(polybiusSquare[row][col]);
            }
            i += 2;
        } else {
            plaintext[j++] = tolower(ciphertext[i++]);
        }
    }
    plaintext[j] = '\0';
}

int main() {
    char ciphertext[2000];
    char key[100]; // not used for Polybe
    char plaintext[1000];

    FILE *input = fopen("input.txt", "r");
    if (!input) {
        printf("Error opening file.\n");
        return 1;
    }

    fgets(key, sizeof(key), input); // Skip the key line
    fgets(ciphertext, sizeof(ciphertext), input);
    ciphertext[strcspn(ciphertext, "\n")] = 0;

    fclose(input);

    decryptPolybe(ciphertext, plaintext);
    printf("%s\n", plaintext);

    return 0;
}
