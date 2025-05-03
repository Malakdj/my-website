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

void alberti_decrypt(const char *ciphertext, char *plaintext, char key, int rotate_interval) {
    int shift = find_pos(outer_disk, toupper(key));
    if (shift == -1) {
        printf("Invalid key! Use A-Z.\n");
        return;
    }
    
    int rotation_counter = 0;
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char lower_char = tolower(ciphertext[i]);
            int pos = find_pos(inner_disk, lower_char);
            plaintext[i] = outer_disk[(pos - shift + 26) % 26];
            
            rotation_counter++;
            if (rotation_counter % rotate_interval == 0) {
                shift = (shift + 1) % 26;
            }
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}

int main() {
    char ciphertext[1000];
    char plaintext[1000];
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
    fgets(ciphertext, sizeof(ciphertext), input);
    ciphertext[strcspn(ciphertext, "\n")] = 0;
    fclose(input);

    alberti_decrypt(ciphertext, plaintext, key, rotate_interval);
    printf("%s", plaintext);
    return 0;
}