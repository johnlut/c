#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h> 
#include <string.h>

void walk_dir(char * root)
{

    DIR * dir;
    struct dirent * entry; 
    struct stat sb;

    if ((dir = opendir(root)) == NULL) 
    {
        perror("file not found"); 
        exit(1); 
    }

    while((entry = readdir(dir)) != NULL)
    {

        char * name = entry->d_name; 
         
        lstat(name, &sb);

        printf("name: %s\n", name);
        
        
        if(S_ISDIR(sb.st_mode)) 
        {
            if(strcmp(".", name) == 0 || strcmp("..", name) == 0)
                    continue;

            printf("dir: %s\n", name);
        }

        else if(S_ISDIRSREG(sb.st_mode))
        {
            printf("file: %s\n", name);
        }
        

    }
    closedir(dir); 


}



int main()
{
    char path[] = "/mnt/c/home/cscb09/test";

    walk_dir(path);

    //listdir(path);  


    return 0; 
}