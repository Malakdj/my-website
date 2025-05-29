#include <bitset>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// Initial Permutation Table
int initial_perm[64] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9 , 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
};

// Final Permutation Table
int final_perm[64] = {
    40, 8 , 48, 16, 56, 24, 64, 32,
    39, 7 , 47, 15, 55, 23, 63, 31,
    38, 6 , 46, 14, 54, 22, 62, 30,
    37, 5 , 45, 13, 53, 21, 61, 29,
    36, 4 , 44, 12, 52, 20, 60, 28,
    35, 3 , 43, 11, 51, 19, 59, 27,
    34, 2 , 42, 10, 50, 18, 58, 26,
    33, 1 , 41, 9 , 49, 17, 57, 25
};

// Expansion D-box Table
int expansion_d[48] = {
    32, 1 , 2 , 3 , 4 , 5 ,
    4 , 5 , 6 , 7 , 8 , 9 ,
    8 , 9 , 10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32, 1
};

// S-box Table
int s[8][4][16] = {
    // S1
    {{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
     {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
     {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
     {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}},
    // S2
    {{15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
     {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
     {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
     {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}},
    // S3
    {{10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
     {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
     {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
     {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}},
    // S4
    {{7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
     {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
     {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
     {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}},
    // S5
    {{2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
     {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
     {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
     {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}},
    // S6
    {{12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
     {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
     {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
     {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}},
    // S7
    {{4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
     {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
     {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
     {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}},
    // S8
    {{13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
     {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
     {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
     {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}}
};

// Permutation P Table
int per[32] = {
    16, 7 , 20, 21,
    29, 12, 28, 17,
    1 , 15, 23, 26,
    5 , 18, 31, 10,
    2 , 8 , 24, 14,
    32, 27, 3 , 9 ,
    19, 13, 30, 6 ,
    22, 11, 4 , 25
};

// Key Permutation Tables
int pc1[56] = {
    57, 49, 41, 33, 25, 17, 9,
    1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27,
    19, 11, 3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
    14, 6, 61, 53, 45, 37, 29,
    21, 13, 5, 28, 20, 12, 4
};

int pc2[48] = {
    14, 17, 11, 24, 1, 5,
    3, 28, 15, 6, 21, 10,
    23, 19, 12, 4, 26, 8,
    16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32
};

int shift_table[16] = {
    1, 1, 2, 2, 2, 2, 2, 2,
    1, 2, 2, 2, 2, 2, 2, 1
};

// Hex to Binary
string hex2bin(string s) {
    string mp[16] = {"0000","0001","0010","0011","0100","0101","0110","0111",
                     "1000","1001","1010","1011","1100","1101","1110","1111"};
    string bin = "";
    for (char c : s) {
        if (c >= '0' && c <= '9') bin += mp[c - '0'];
        else bin += mp[toupper(c) - 'A' + 10];
    }
    return bin;
}

// Binary to Hex
string bin2hex(string s) {
    string mp[16] = {"0","1","2","3","4","5","6","7",
                     "8","9","A","B","C","D","E","F"};
    string hex = "";
    for (int i = 0; i < s.size(); i += 4) {
        int num = stoi(s.substr(i, 4), nullptr, 2);
        hex += mp[num];
    }
    return hex;
}

// Permutation
string permute(string k, const int* arr, int n) {
    string ans = "";
    for (int i = 0; i < n; i++) ans += k[arr[i] - 1];
    return ans;
}

// XOR
string xor_str(string a, string b) {
    string ans = "";
    for (int i = 0; i < a.size(); i++) {
        ans += (a[i] == b[i]) ? '0' : '1';
    }
    return ans;
}

// Left circular shift
string left_shift(string key_chunk, int shifts) {
    string shifted = key_chunk.substr(shifts) + key_chunk.substr(0, shifts);
    return shifted;
}

string adjust_key_parity(string key_bin) {
    for (int i = 0; i < 8; i++) {
        int parity = 0;
        for (int j = 0; j < 8; j++) {
            if (j != 7) parity ^= (key_bin[i*8 + j] - '0');
        }
        key_bin[i*8 + 7] = (parity % 2) ? '0' : '1';
    }
    return key_bin;
}
// Adjust key parity bits


// Generate 16 round keys
vector<string> generate_round_keys(string key_bin) {
    vector<string> round_keys;
    
    // Adjust parity bits first
    key_bin = adjust_key_parity(key_bin);
    
    // Apply PC-1 permutation (64-bit -> 56-bit)
    string key_pc1 = permute(key_bin, pc1, 56);
    
    // Split into left and right halves
    string left = key_pc1.substr(0, 28);
    string right = key_pc1.substr(28);
    
    // Generate 16 round keys
    for (int i = 0; i < 16; i++) {
        // Apply left shifts
        left = left_shift(left, shift_table[i]);
        right = left_shift(right, shift_table[i]);
        
        // Combine and apply PC-2 (56-bit -> 48-bit)
        string combined = left + right;
        string round_key = permute(combined, pc2, 48);
        
        round_keys.push_back(round_key);
    }
    
    return round_keys;
}

// S-box
string sbox_substitution(string input) {
    string output = "";
    for (int i = 0; i < 48; i += 6) {
        string block = input.substr(i, 6);
        int row = (block[0] - '0') * 2 + (block[5] - '0');
        int col = stoi(block.substr(1, 4), nullptr, 2);
        int val = s[i / 6][row][col];
        output += bitset<4>(val).to_string();
    }
    return output;
}

// DES Decryption
string des_decrypt(string ct_bin, string key_bin) {
    vector<string> round_keys = generate_round_keys(key_bin);
    
    string ct = permute(ct_bin, initial_perm, 64);
    string left = ct.substr(0, 32), right = ct.substr(32);

    // Use round keys in reverse order for decryption
    for (int round = 15; round >= 0; round--) {
        string right_expanded = permute(right, expansion_d, 48);
        string xored = xor_str(right_expanded, round_keys[round]);
        string sbox_out = sbox_substitution(xored);
        string permutated = permute(sbox_out, per, 32);
        string new_right = xor_str(left, permutated);
        left = right;
        right = new_right;
    }

    string combined = right + left;
    return permute(combined, final_perm, 64);
}

// Main function for decryption only
int main() {
    ifstream file("input.txt");
    if (!file) {
        cerr << "Cannot open input.txt" << endl;
        return 1;
    }

    string ct_hex, key_hex;
    getline(file, ct_hex);  // Read ciphertext
    getline(file, key_hex); // Read key
    file.close();

    if (ct_hex.size() != 16 || key_hex.size() != 16) {
        cerr << "Ciphertext and key must be 16 hex characters (64 bits)." << endl;
        return 1;
    }

    string ct_bin = hex2bin(ct_hex);
    string key_bin = hex2bin(key_hex);

    // Decryption
    string pt_bin = des_decrypt(ct_bin, key_bin);
    string pt_hex = bin2hex(pt_bin);

    cout << "Decrypted Plaintext (Binary): " << pt_bin << endl;
    cout << "Decrypted Plaintext (Hex): " << pt_hex << endl;

    return 0;
}