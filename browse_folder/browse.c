#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <dirent.h>

int walk_dir(char * root); 
void browse_dir(char * root);

int main()
{


    char dir[24] = "/mnt/c/home/cscb09/test"; 

    //walk_dir(dir); 

    browse_dir(dir); 

    return 0;
}

int walk_dir(char * root)
{

    DIR * dir; 

    struct dirent * entry; 
    struct stat sb; 
    dir = opendir(root); 

    if(dir)
    {
        while((entry = readdir(dir)) != NULL)
        {

            char * name = entry->d_name; 
            lstat(name, &sb);

            printf("%s\n", name); 

            if(S_ISDIR(sb.st_mode))
            {   
                if(strcmp(".", name) == 0 || strcmp("..", name) == 0)
                    continue;

                printf("directory: %s\n", name);

                //walk_dir(name); 
            }

            else
            {
                printf("file: %s\n", name);
            }

        }
        closedir(dir);
    }   

    return 0; 


}

void browse_dir(char *root_dir)
{

   // printf("%s\n",root);

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
            char *d_name = ent->d_name; 

            // get stats of entry 
            lstat(d_name,&sb);

            // if a directory
            if(S_ISDIR(sb.st_mode)) 
            {
                // ignore current and parent folder, respectively
                if(strcmp(".",d_name) == 0 || strcmp("..",d_name) == 0)
                    continue;
                
                printf("dir: %s\n", d_name);

                // recursion 
                browse_dir(d_name);
            }
            
            // if a file or link (SHOULDVE OMITED SYMLINKS)
            else 
            {    
                // get full file path   
                //char *path = realpath(d_name, NULL);
                printf("file: %s\n", d_name);

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