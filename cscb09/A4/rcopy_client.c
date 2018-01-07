#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <dirent.h>
#include <limits.h>


#include "ftree.h"
#include "hash.h"
// port at which the server will be listening
// #define PORT 50000

void send_rec(char *message, char *response, int sock_fd);
void browse_dir(char *root_dir, int sock_fd);    

int main(int argc, char **argv) 
{
    int PORT = SECRET; 
    // setting up the file descriptor
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);

    // setting up the sockaddr_in to connect to
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);

    // seeting up for server and client on same machine
    // ] 
    // local ip is 127.0.0.1 
    if (inet_pton(AF_INET, "127.0.0.1", &server.sin_addr)< 0) {
        perror("client: inet_pton");
        close(sock_fd);
        exit(1);
    }

    // connect to the server
    if (connect(sock_fd, (struct sockaddr *) &server, sizeof(server)) == -1) {
        perror("client: connect");
        close(sock_fd);
        exit(1);
    }

    printf("client: connected\n");


    // connect with server
    while(1)
    {   

        // buffer directory to send 
        char dir_name[MAXPATH];
        
        printf("Enter directory: ");
        scanf("%s" , dir_name);
        

        browse_dir(dir_name, sock_fd);

        break;
    }

    return 0;

}

// send and recieve data from server
void send_rec(char *message, char *response, int sock_fd)
{

    char server_reply[1024];

    // send data
    if( send(sock_fd , message , strlen(message) , 0) < 0)
    {
        perror("client: send failed");
        //return 1;
    }
     
    // get reply
    if( recv(sock_fd, server_reply , 2000 , 0) < 0)
    {
        perror("client: no reply");
        //break;
    }
    
    // print reply
    printf("server wrote: %s\n\n", server_reply);

    // save reply into variable
    strcpy(response, server_reply);
    
    // reset servery reply 
    memset(server_reply, '\0', sizeof(server_reply));

}

// serialize struct 
void serialize(char *buffer, struct fileinfo f)
{

    // buffer for serialized struct
    char ret[312];  

    // copy data from struct into a buffer
    char path_buffer[MAXPATH];
    strcpy(path_buffer, f.path); 
    char mode_buffer[24];
    sprintf(mode_buffer, "%d", f.mode);
    char hash_buffer[HASH_SIZE];
    strcpy(hash_buffer, f.hash); 
    char size_buffer[24];  
    sprintf(size_buffer, "%d", (int)f.size);   

    // combine data into a string
    strcat(ret, path_buffer);
    strcat(ret, ";");
    strcat(ret, mode_buffer);
    strcat(ret, ";");
    strcat(ret, hash_buffer);
    strcat(ret, ";");
    strcat(ret, size_buffer);

    //add null terminator
 

    // copy serialzed string into buffer to be sent
    strcpy(buffer, ret);
    
    // reset buffers
    memset(path_buffer, '\0', sizeof(path_buffer));
    memset(mode_buffer, '\0', sizeof(mode_buffer));   
    memset(hash_buffer, '\0', sizeof(hash_buffer));
    memset(size_buffer, '\0', sizeof(size_buffer));
    memset(ret, '\0', sizeof(ret));
}

void browse_dir(char *root_dir, int sock_fd)
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
            char *d_name = ent->d_name; 

            // get stats of entry 
            lstat(d_name,&sb);

            // create empty struct to be sent 
            struct fileinfo f; 

            // if a directory
            if(S_ISDIR(sb.st_mode)) 
            {
                // ignore current and parent folder, respectively
                if(strcmp(".",d_name) == 0 || strcmp("..",d_name) == 0)
                    continue;
                
                // populate struct
                char *path = realpath(d_name, NULL);
                strcpy(f.path, path);
                f.mode = (sb.st_mode); 
                f.size = (sb.st_size);    

                // creat buffer for serialization
                char buffer[312];

                // serialize
                serialize(buffer, f);
                
                //printf("serialized: %s\n", buffer);
                
                // vairable for server response
                char response[10];

                // send serial to server
                send_rec(buffer, response, sock_fd);

                // decide what to do 
                
                    // if match -> update permissions
                    
                    // if mismatch 
                        // creat directory
                        // set permissions
                        // wait for TRANSMIT_OK 
                    
                    // if match error -> report error
                
                    // if transmit error -> report error
                
                // reset message and response buffer 
                memset(buffer, '\0', sizeof(buffer));
                memset(response, '\0', sizeof(response));

                // recursion 
                browse_dir(d_name, sock_fd);
            }
            
            // if a file or link (SHOULDVE OMITED SYMLINKS)
            else 
            {    
                // get full file path   
                char *path = realpath(d_name, NULL);

                // hash file
                char hash_val[HASH_SIZE] = { '\0' };
                hash(hash_val, path); 
                //show_hash(hash_val, 8);
                
                // populate struct 
                strcpy(f.path, path);
                strcpy(f.hash, hash_val);
                f.mode = (sb.st_mode); 
                f.size = (sb.st_size);    

                // create buffer for serialization
                char buffer[312];
                
                // serialize
                serialize(buffer, f);
                
                //printf("serialized: %s\n", buffer);

                // vairable for server response
                char response[10];

                // send serial to server
                send_rec(buffer, response, sock_fd);

                // decide what to do 
                
                    // if match -> update permissions
                
                    // if mismatch
                        // send file
                        // update permissions
                        // wait for TRANSMIT_OK
                    
                    // if match error -> report error  
                        
                    // if transmit error -> report error
                
                // reset message and response buffer 
                memset(buffer, '\0', sizeof(buffer));
                memset(response, '\0', sizeof(response));
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
