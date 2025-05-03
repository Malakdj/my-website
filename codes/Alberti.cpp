#include <stdio.h>
#include <string.h>
#include <ctype.h>

const char outer_disk[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char inner_disk[] = "abcdefghijklmnopqrstuvwxyz";

int find_pos(const char *disk, char c) {
    for (int i = 0; i < 26; i++) {
        if (disk[i] == c) return i;
    }
    return -1;
}

void alberti_encrypt(const char *plaintext, char *ciphertext, char key, int rotate_interval) {
    int shift = find_pos(outer_disk, toupper(key));
    if (shift == -1) {
        printf("Invalid key! Use A-Z.\n");
        return;
    }
    
    int rotation_counter = 0;
    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            char upper_char = toupper(plaintext[i]);
            int pos = find_pos(outer_disk, upper_char);
            ciphertext[i] = inner_disk[(pos + shift) % 26];
            
            rotation_counter++;
            if (rotation_counter % rotate_interval == 0) {
                shift = (shift + 1) % 26;
            }
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[strlen(plaintext)] = '\0';
}

int main() {
    char plaintext[1000];
    char ciphertext[1000];
    char key;
    int rotate_interval;

    // Read from input.txt
    FILE *input = fopen("input.txt", "r");
    if (!input) {
        printf("Error opening input file\n");
        return 1;
    }

    fscanf(input, "%c\n", &key);
    fscanf(input, "%d\n", &rotate_interval);
    fgets(plaintext, sizeof(plaintext), input);
    plaintext[strcspn(plaintext, "\n")] = 0;
    fclose(input);

    alberti_encrypt(plaintext, ciphertext, key, rotate_interval);
    printf("%s", ciphertext);
    return 0;
}