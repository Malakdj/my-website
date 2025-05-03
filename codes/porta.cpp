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

void encryptPorta(const char* plaintext, const char* key, char* ciphertext) {
    int j = 0;
    for (int i = 0; plaintext[i] != '\0'; i++) {
        char c = toupper(plaintext[i]);
        if (isalpha(c)) {
            int index = getIndex(key[j % strlen(key)]);
            const char* rowA = portaTable[index][0];
            const char* rowB = portaTable[index][1];
            const char* pos = strchr(rowA, c);
            if (pos) {
                int idx = pos - rowA;
                ciphertext[j++] = rowB[idx];
            } else {
                ciphertext[j++] = c;
            }
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

    FILE* input = fopen("input.txt", "r");
    if (!input) {
        printf("Error opening file.\n");
        return 1;
    }

    fgets(key, sizeof(key), input);
    fgets(plaintext, sizeof(plaintext), input);
    key[strcspn(key, "\n")] = 0;
    plaintext[strcspn(plaintext, "\n")] = 0;
    fclose(input);

    encryptPorta(plaintext, key, ciphertext);
    printf("Encrypted text: %s\n", ciphertext);
    return 0;
}
