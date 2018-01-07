#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define MIN(a,b) (((a)<(b))?(a):(b))

int main() 
{

    FILE * fd_src; 
    FILE * fd_dst; 

    char buffer[27]; 
    size_t nread; 
    size_t nwritten; 
    struct stat st; 

    fd_src = fopen("text.txt", "r"); 
    fd_dst = fopen("new_text.txt", "w"); 

    if(fd_src == NULL)
    {
        perror("source file open failed"); 
        exit(1); 
    }

    if(fd_dst == NULL)
    {
        perror("destination file open failed"); 
        exit(1); 
    }

    stat("text.txt", &st); 
    int size = st.st_size; 
    printf("size of file: %d bytes\n", size);

    int to_write = size; 
    //printf("size of file: %d bytes\n", to_write);

    int offset; 

    while((nread = fread(buffer, 1, sizeof(buffer), fd_src)) > 0)
    {
        offset = MIN(sizeof(buffer), to_write); 

        //printf("%s\n",buffer);
        nwritten = fwrite(buffer, 1, offset, fd_dst);

        to_write -= nwritten;  
        printf("wrote: %zu bytes, %d bytes left\n", nwritten, to_write);

        memset(buffer, 0, sizeof(buffer));
    }
    

    //fread(buffer, 1, sizeof(buffer), fp); 

    //printf("%s\n",buffer);

    fclose(fd_src);
    fclose(fd_dst);
    return 0; 
}