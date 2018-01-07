#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <dirent.h>
#include <string.h>

// headers 
#include "ftree.h"
#include "hash.h"

// compare sizes of two files
bool check_size(char *file_1, char *file_2)
{

    // initialized a stat for each file
    struct stat st_1; 
    struct stat st_2; 

    // open each files stats
    stat(file_1, &st_1);
    stat(file_2, &st_2);

    // set vavirables to each of the files sizes
    int size_1 = st_1.st_size;
    int size_2 = st_2.st_size; 

    // compare sizes 
    if (size_1 == size_2)
        return true; 

    return false; 
}

// copy file from sources to dest 
void copy(char *source, char *dest)
{

    // create file pointers for each file
    FILE *fp1;
    FILE *fp2;  

    // stat variable for permission get/set 
    struct stat sb; 

    // character buffer
    char c; 

    // open source file
    fp1 = fopen(source, "r");

    // check if file was opened
    if (source == NULL) {
        perror("cant open source file");
        exit(1);
    }

    // open dest file
    fp2 = fopen(dest, "w");

    // check if file was opened
    if (dest == NULL) {
        perror("cant open dest file");
        fclose(fp1);
        exit(1);
    }

    // copy contents from source to dest
    while( ( c = fgetc(fp1) ) != EOF )
        fputc(c, fp2);

    // set files permissions
    stat(source, &sb); 
    chmod(dest, sb.st_mode & 07777);

    // close files 
    fclose(fp1);
    fclose(fp2);

}

// create directory 
void make_dir(char *dir)
{

    // create stat for check for dir 
    struct stat st;

    // if the directory doesnt exist 
    if (stat(dir, &st) == -1) {

        // make a new directory 
        mkdir(dir, 0700);
   }
}

// copy a file if it needs to copied 
void copy_file(char *source, char *dest) 
{

    // if files are the same size
    if(check_size(source, dest)) {

        // creat empty hashes 
        char hash_val_1[65] = { '\0' };
        char hash_val_2[65] = { '\0' };

        // generate hashes
        hash(hash_val_1, source);
        hash(hash_val_2, dest);

        // print hashes (TESTING)
        // show_hash(hash_val_1, 64);
        // show_hash(hash_val_2, 64);

      
        // compare hashes
        // if hashes are the same
        if(!compare_hash(hash_val_1, hash_val_2)) {

        // copy file
        copy(source, dest); 
        }
    }

    // if files are different size 
    else {

        // copy file
        copy(source, dest); 
    }
}

// copy a directory including files child directories 
void copy_dir(char *root_dir, char *dest_dir)
{
    // open source dir
    DIR *dir = opendir(root_dir);

    // directory entries
    struct dirent *ent;

    // entry info 
    struct stat sb;

    // if the directory is not empty 
    if (dir != NULL)
    {
        // set current to dir to source
        chdir(root_dir);

        // go through each entry 
        while((ent = readdir(dir)) != NULL) 
        {   
            // get name of entry 
            char * d_name = ent->d_name; 

            // get stats of entry 
            lstat(d_name,&sb);

            // if a directory
            if(S_ISDIR(sb.st_mode)) 
            {
                // ignore current and parent folder, respectively
                if(strcmp(".",d_name) == 0 || strcmp("..",d_name) == 0)
                    continue;
                
                // append current folder onto dest 
                char *new_dest_mid = strcat(dest_dir, "/");
                char *new_dest = strcat(new_dest_mid, d_name);

                // append current folder onto source 
                char *new_root_mid = strcat(root_dir, "/");
                char *new_root = strcat(new_root_mid, d_name);

                // make corresponding directory in dest
                make_dir(new_dest); 
                
                // create new process
                int childpid; 
                childpid = fork(); 

                // child
                if(childpid == 0) {
                    copy_dir(new_root, new_dest);
                }
                
                // parent 
                else {
                    wait(NULL); 
                }
            }
            
            // if a file or link (SHOULDVE OMITED SYMLINKS)
            else 
            {   

                // temp variables for file directory
                char temp_root_dir[1024];
                char temp_dest_dir[1024];
                strcpy(temp_root_dir, root_dir); 
                strcpy(temp_dest_dir, dest_dir); 

                // create source file directory
                char *source_file_mid = strcat(temp_root_dir, "/");
                char *source_file = strcat(source_file_mid, d_name);
                
                // creat dest file directory 
                char *dest_file_mid = strcat(temp_dest_dir, "/");
                char *dest_file = strcat(dest_file_mid, d_name);

                // copy file 
                copy_file(source_file, dest_file); 
            }

        }
        // go to parent 
        chdir("..");

        // close last dir
        closedir(dir);
        
    }
    //check for error
    else
    {
        perror("opening dir");
    }   
}

// copy file tree
int copy_ftree(const char *source_dir, const char *dest_dir)
{

    // strings for function input 
    char source[1024]; 
    char dest[1024]; 

    // popular strings 
    strcpy(source, source_dir);
    strcpy(dest, dest_dir);

    // check if operation can be done 
    // look in destination directory and check if 
    // source directory is a substring of dest directory
   
    // copy the directory 
    copy_dir(source, dest); 

    return 1; 
}
