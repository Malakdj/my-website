#include <stdio.h>
#include <string.h>
#include <ctype.h>

void decryptOTP(char *ciphertext, char *key, char *plaintext) {
    int textLen = strlen(ciphertext);
    int keyLen = strlen(key);
    int i;

    for (i = 0; i < textLen; i++) {
        if (isalpha(ciphertext[i])) {
            // Convert to uppercase and get 0-25 values
            int cipherChar = toupper(ciphertext[i]) - 'A';
            int keyChar = toupper(key[i % keyLen]) - 'A';
            
            // Perform OTP decryption (subtraction mod 26)
            int plainChar = (cipherChar - keyChar + 26) % 26;
            
            // Convert back to uppercase character
            plaintext[i] = plainChar + 'A';
        } else {
            // Leave non-alphabetic characters unchanged
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[i] = '\0';
}

int main() {
    char ciphertext[1000];
    char key[1000];
    char plaintext[1000];

    // Read from input.txt
    FILE *input = fopen("input.txt", "r");
    if (!input) {
        printf("Error opening input file\n");
        return 1;
    }

    fgets(key, sizeof(key), input);
    key[strcspn(key, "\n")] = '\0';
    fgets(ciphertext, sizeof(ciphertext), input);
    ciphertext[strcspn(ciphertext, "\n")] = '\0';
    fclose(input);

    // Check if key is at least as long as ciphertext
    if (strlen(key) < strlen(ciphertext)) {
        printf("Error: Key must be at least as long as ciphertext\n");
        return 1;
    }

    decryptOTP(ciphertext, key, plaintext);
    printf("%s", plaintext);
    return 0;
}