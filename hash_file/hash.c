#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 

#define HASH_SIZE 16

void print_hash(char * hash, int block_size); 

int hash(char * hash, file * file_fd); 

int main()
{

    FILE * file_fd; 
    file_fd = fopen("text.txt", "r"); 

    int block_size = HASH_SIZE; 
    char hash[HASH_SIZE + 1]; 
    memset(hash, '\0', sizeof(hash)); 

    hash(hash, file_fd); 

    

    fclose(file_fd); 
    return 0; 
}