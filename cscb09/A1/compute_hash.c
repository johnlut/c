#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

// Hash manipulation functions in hash_functions.c
void hash(char *hash_val, long block_size);
int check_hash(const char *hash1, const char *hash2, long block_size);

#ifndef MAX_BLOCK_SIZE
#define MAX_BLOCK_SIZE 1024
#endif

/* Converts hexstr, a string of hexadecimal digits, into hash_val, an an array of char.
 * Each pair of digits in hexstr is converted to its numeric 8-bit value and stored in
 * an element of hash_val.
 * Preconditions: 
 *    - hash_val must have enough space to store block_size elements
 *    - hexstr must be block_size * 2 characters in length
 */

void xstr_to_hash(char *hash_val, char *hexstr, int block_size) {
    for (int i = 0; i < block_size * 2; i += 2) {
        char str[3];
        str[0] = hexstr[i];
        str[1] = hexstr[i + 1];
        str[2] = '\0';
        hash_val[i / 2] = strtol(str, NULL, 16);
    }
}

/* Print the values of the char array hash_val in hex
 * Note that each char (8 bits) corresponds to two digits in hex (4 bits per digit)
 * In case you are wondering about the %.2hhx in printf:
 * -- The 2 makes sure that for each char always two digits are printed in hex notation, so that for example
 * for a '\0' (all bits in the byte are zero) two zeros are printed in hex notation, rather than one.
 * -- The hh makes sure that printf treats the char properly, since %x by default expects an int.
 */

void show_hash(char *hash_val, long block_size) {
    for (int i = 0; i < block_size; i++) {
        printf("%.2hhx ", hash_val[i]);
    }
    printf("\n");
}

// Checks if given char array corresponds to a positive integer.
bool isInt(char number[]) {
    //check if input is negative
    if (number[0] == '-')
        return false;
    //check if all remaining characters are numbers
    for (int i = 0; number[i] != 0; i++) {
        //if number[i] is not a digit return false
        if (!isdigit(number[i]))
            return false;
    }
    return true;
}

// Checks if given char array is a valid block_size.
bool isValidBlockSize(char number[]) {
    //check if string is an int
    if (!isInt(number))
        return false;
    //convert given string into an int
    int converted = atoi(number);
    //check if int is in valid range
    if (converted > 0 && converted < MAX_BLOCK_SIZE)
        return true;
    else
        return false;
}

int main(int argc, char **argv) {
    char hash_val[MAX_BLOCK_SIZE] = { '\0' };
    long block_size;

    //check if valid number of arguments is given
    if (argc < 2 || argc > 3) {
        printf("Usage: compute_hash BLOCK_SIZE [ COMPARISON_HASH ]\n");
        exit(1);
    }
    //check if first argument is valid
    if (!isValidBlockSize(argv[1])) {
        printf(
                "The block size should be a positive integer less than or equal to %d\n",
                MAX_BLOCK_SIZE);
        exit(1);
    }
    //set block_size from input
    block_size = atoi(argv[1]);
    //generate hash
    hash(hash_val, block_size);

    //execute if given one argument
    if (argc == 2) {
        show_hash(hash_val, block_size);
    }
    //execute if given two arguments
    else {
        int compare = check_hash(hash_val, argv[2], block_size);
        printf("%d\n", compare);
    }

    return 0;
}

