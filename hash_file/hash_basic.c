#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 

int main()
{

    FILE * file_fd; 
    file_fd = fopen("text.txt", "r"); 

    char c; 

    char hash[65]; 
    int hash_size = 64; 
    memset(hash, '\0', sizeof(hash)); 

    int i = 0; 

    while(!feof(file_fd))
    {
        c = fgetc(file_fd); 

        hash[i%hash_size] ^= c; 

        i++; 
    }

    
    for (int i = 0; i < hash_size; i++) {
        printf("%.2hhx ", hash[i]);
    }
    printf("\n");


    fclose(file_fd); 

    return 0; 
}