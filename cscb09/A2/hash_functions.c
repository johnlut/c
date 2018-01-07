#include <stdio.h>
#include <string.h>


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
