#include <stdio.h>
#include <string.h>
#include <ctype.h>

char portaTable[13][2][14] = {
    {"ABCDEFGHIJKLM", "NOPQRSTUVWXYZ"},
    {"ABCDEFGHIJKLM", "OPQRSTUVWXYZN"},
    {"ABCDEFGHIJKLM", "PQRSTUVWXYZNM"},
    {"ABCDEFGHIJKLM", "QRSTUVWXYZNML"},
    {"ABCDEFGHIJKLM", "RSTUVWXYZNMLK"},
    {"ABCDEFGHIJKLM", "STUVWXYZNMLKJ"},
    {"ABCDEFGHIJKLM", "TUVWXYZNMLKJI"},
    {"ABCDEFGHIJKLM", "UVWXYZNMLKJIH"},
    {"ABCDEFGHIJKLM", "VWXYZNMLKJIHG"},
    {"ABCDEFGHIJKLM", "WXYZNMLKJIHGF"},
    {"ABCDEFGHIJKLM", "XYZNMLKJIHGFE"},
    {"ABCDEFGHIJKLM", "YZNMLKJIHGFED"},
    {"ABCDEFGHIJKLM", "ZNMLKJIHGFEDC"}
};

int getIndex(char c) {
    return (toupper(c) - 'A') / 2;
}

void decryptPorta(const char* ciphertext, const char* key, char* plaintext) {
    int j = 0;
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        char c = toupper(ciphertext[i]);
        if (isalpha(c)) {
            int index = getIndex(key[j % strlen(key)]);
            const char* rowB = portaTable[index][1];
            const char* rowA = portaTable[index][0];
            const char* pos = strchr(rowB, c);
            if (pos) {
                int idx = pos - rowB;
                plaintext[j++] = rowA[idx];
            } else {
                plaintext[j++] = c;
            }
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

    FILE* input = fopen("input.txt", "r");
    if (!input) {
        printf("Error opening file.\n");
        return 1;
    }

    fgets(key, sizeof(key), input);
    fgets(ciphertext, sizeof(ciphertext), input);
    key[strcspn(key, "\n")] = 0;
    ciphertext[strcspn(ciphertext, "\n")] = 0;
    fclose(input);

    decryptPorta(ciphertext, key, plaintext);
    printf("Decrypted text: %s\n", plaintext);
    return 0;
}
