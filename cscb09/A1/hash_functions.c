#include <stdio.h>
#include <string.h>

void xstr_to_hash(char *hash_val, char *hexstr, int block_size);

void hash(char *hash_val, long block_size) {
    //get input to be hashed
    char str[1024];
    scanf("%[^EOF]s", str);
    //get lenght of input for looping
    //char str[] = "HelloWorld\n";
    int len = strlen(str);
    //loop through each element of input and each
    //element of hash_val modulus with respect to block_size
    for (int i = 0; i < len; i++) {
        hash_val[(i % block_size)] ^= str[i];
    }
}

int check_hash(const char *hash1, const char *hash2, long block_size) {
    //create variable for second hash
    char hash_val_2[block_size];
    //to avoid using the const
    char hash_2[1024];
    strcpy(hash_2, hash2);	
    //populate second hash variable from input
    xstr_to_hash(hash_val_2, hash_2, block_size);
    //loop though each hash and compare
    for (int i = 0; i < block_size; i++) {
        if (hash1[i] != hash_val_2[i])
            return i;
    }
    return block_size;
}

