#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdbool.h>

void hash(char *hash_val, char *file)
{

    FILE * fp; 
    fp = fopen(file, "r"); 
    int c;
    long i;  

    int block_size = 64; 
      

    while(!feof(fp)){

        c = fgetc(fp); 

        hash_val[(i % block_size)] ^= c; 

        i++; 
    }

    i = 0; 

    fclose(fp); 

    

}

void show_hash(char *hash_val, long block_size) {
    for (int i = 0; i < block_size; i++) {
        printf("%.2hhx ", hash_val[i]);
    }
    printf("\n");
}

bool compare_hash(char *hash_val_1, char *hash_val_2, char *file_1, char *file_2)
{

    int block_size = 64; 

    for (int i = 0; i < block_size; i++) {
        printf("%d \t %d \n",hash_val_1[i], hash_val_2[i]);
        if (hash_val_1[i] != hash_val_2[i])
            return FALSE; 
    }

    return TRUE; 


}

main()
{
    /* CHECK THE HASH FUNCTION
    char hash_val[65] = { '\0' };
    char *file = "myfile.txt";

    hash(hash_val, file); 

    printf("almost done");

    show_hash(hash_val, 64); 

    printf("done\n");  
    */

    char hash_val_1[65] = { '\0' };
    char hash_val_2[65] = { '\0' };
    char *file_1 = "sample2.txt";
    char *file_2 = "sample1.txt"; 
    
    hash(hash_val_1, file_1);
    hash(hash_val_2, file_2);

    show_hash(hash_val_1, 64);
    show_hash(hash_val_2, 64);

    int  a = compare_hash(hash_val_1, hash_val_2, file_1, file_2);

    printf("%d\n",a); 


}
