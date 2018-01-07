#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// headers 
#include "hash.h"

// show hashes (TESTING PURPOSES)
void show_hash(char *hash_val, long block_size) 
{
    for (int i = 0; i < block_size; i++) {
        printf("%.2hhx ", hash_val[i]);
    }
    printf("\n");
}

// generate hashes 
void hash(char *hash_val, char *file)
{

    // open file 
    FILE * fp; 
    fp = fopen(file, "r"); 

    // buffer variable and counter 
    int c;
    long i;  

    // hash size 
    int block_size = 8; 
      
    // read over file
    while(!feof(fp)){

        // set buffer to current char
        c = fgetc(fp); 

        // xor value
        hash_val[(i % block_size)] ^= c; 

        i++; 
    }

    // reset value for next function call
    i = 0; 

    // close file
    fclose(fp); 
}

// compare two hashes
bool compare_hash(char *hash_val_1, char *hash_val_2)
{

    // size of hash 
    int block_size = 64;

    // loop over hash
    for (int i = 0; i < block_size; i++) {

        // compare value of both hashes
        if (hash_val_1[i] != hash_val_2[i])
            return false; 
    }
    return true; 
}