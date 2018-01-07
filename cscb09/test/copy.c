#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
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
            return false; 
    }

    return true; 
}

bool check_size(char *file_1, char *file_2)
{

   struct stat st_1; 
   struct stat st_2; 

   stat(file_1, &st_1);
   stat(file_2, &st_2);

   int size_1 = st_1.st_size;
   int size_2 = st_2.st_size; 

   printf("file1\t file2\n");
   printf("%d\t %d\n", size_1, size_2);

   if (size_1 == size_2)
      return true; 

   return false; 

}

void copy(char *source, char *dest)
{

   FILE *fp1;
   FILE *fp2;  
   char c; 

   fp1 = fopen(source, "r");
   if (source == NULL) {
      puts("cannot open this file");
      exit(1);
   }

   fp2 = fopen(dest, "w");
   if (dest == NULL) {
      puts("Not able to open this file");
      fclose(fp1);
      exit(1);
   }

   while( ( c = fgetc(fp1) ) != EOF )
      fputc(c, fp2);

 
   fclose(fp1);
   fclose(fp2);
   printf("im done b \n"); 

}

void make_dir()
{

   struct stat st = {0};

   if (stat("/home/peaches/cscb09/lutosla1/test/test_dir", &st) == -1) {

      printf("it was true \n");
      mkdir("/home/peaches/cscb09/lutosla1/test/test_dir", 0700);
   }
}

void copyFile(char *root_dir, char *dest_dir) 
{

   // if files are the same size
   if(check_size(root_dir, dest_dir)) {

      // creat empty hashes 
      char hash_val_1[65] = { '\0' };
      char hash_val_2[65] = { '\0' };

      // generate hashes
      hash(hash_val_1, root_dir);
      hash(hash_val_2, dest_dir);

      // print hashes (TESTING)
      show_hash(hash_val_1, 64);
      show_hash(hash_val_2, 64);

      
      // compare hashes
      // if hashes are the same
      if(!compare_hash(hash_val_1, hash_val_2)) {

         // copy file
         copy(root_dir, dest_dir); 
      }
   }

   // if files are different size 
   else {

      // copy file
      copy(root_dir, dest_dir); 
   }
}



 
void main() 
{
   /*
   char *source = "sample1.txt";
   char *dest = "desto.txt"; 

   copy(source, dest);

   printf("nice\n"); 
   */

   /*
   make_dir();

   printf("complete\n");
   */ 
  
   //char *source = "sample1.txt";
   //char *dest = "sample2.txt"; 

   /*
   char *source = "/home/peaches/cscb09/lutosla1/test/test1/file1.txt";
   char *dest = "/home/peaches/cscb09/lutosla1/test/test1/file1.txt";

   bool a =check_size(source, dest); 

   printf("%d\n", a); 
   */


   
   char *source = "/home/peaches/cscb09/lutosla1/test/test1/file1.txt";
   char *dest = "/home/peaches/cscb09/lutosla1/test/test2/file2.txt";

   copyFile(source, dest); 

   printf("great success\n");
   
  
}