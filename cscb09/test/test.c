#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>



main()
{
    FILE * fp; 
    fp = fopen("myfile.txt", "r"); 
    int c;
    long i;  

    int block_size = 5; 
    char hash_val[block_size + 1] = { '\0' };  

    while(!feof(fp)){

        c = fgetc(fp); 

        hash_val[(i % block_size)] ^= c; 

        //printf("%c", c); 

        i++; 
    }

    printf("hello\n"); 

    close(fp); 

    for (int i = 0; i < block_size; i++) {
        printf("%.2hhx ", hash_val[i]);
    }
    printf("\n");

    return(0); 

}
