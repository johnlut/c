#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>    
#include <stdbool.h>

#include "ftree.h"
#include "hash.h"

//#define PORT 50000
#define MAX_BACKLOG 5

void serve_client(int fd);

void create_fileinfo(char *serial, struct fileinfo f); 

int main() 
{
    int PORT = SECRET; 
    // set up variables
    char client_message[1024];
    int read_size;
    int sock_fd;
    struct sockaddr_in server;
    int client_fd; 

    // create socket
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);

    // error check
    if (sock_fd < 0) {
        perror("server: socket");
        exit(1);
    }

    // bind socket to an address
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);  
    server.sin_addr.s_addr = INADDR_ANY;
    memset(&server.sin_zero, 0, 8);  

    // error check
    if (bind(sock_fd, (struct sockaddr *)&server, sizeof(struct sockaddr_in)) < 0) {
        perror("server: bind");
        close(sock_fd);
        exit(1);
    }

    // create queue in kernel for new connection requests
    if (listen(sock_fd, MAX_BACKLOG) < 0) {
        perror("server: listen");
        close(sock_fd);
        exit(1);
    }
    while(1){
        // accept a new connection
        client_fd = accept(sock_fd, NULL, NULL);

        // error check
        if (client_fd < 0) {
            perror("server: accept");
            close(sock_fd);
            exit(1);
        }

        printf("new connection\n");

        // stay connected to client
        while( (read_size = recv(client_fd , client_message , 2000 , 0)) > 0 )
        {
            // message from client 
            printf("%s\n",client_message);
            
            // buffer for message back to server
            char server_message[10] = {'\0'}; 

            // create empty fileinfo to compare to server files
            // struct fileinfo f;

            // populate file info from recieved serial
            //create_fileinfo(client_message, f); 

            /*
            I wans unable to figure out how to serialize 
            and deserialize so this is all i got 
            */
            
            // try to open file\folder 
                
                // if null -> send MISMATCH
                    
                    // if file recieve file 
                        
                        // confirm file recieved with TRANSMIT_OK   
                                     
                    // if folder create folder and set permissions 

                // if open 
                    
                    // if file 

                        // generate file and compare
                            
                            // if hash match -> do nothing
                                
                            // if hash mismatch -> send mismatch 
                                
                                // recieve file 
                                
                                    // confirm file recieved with TRANSMIT_OK 

                    // if folder update permissions


            write(client_fd , client_message , strlen(client_message));

            // if client sends exit drop connection
            if(!strcmp(client_message, "exit"))
            {   
                close(client_fd);
                break;
            }

            // reset message and response buffer 
            memset(client_message, '\0', sizeof(client_message));
            memset(server_message, '\0', sizeof(server_message));
        }    
    }
    close(client_fd);
    close(sock_fd);

    return 0;
}

// populate fileinfo f with info from serial 
void create_fileinfo(char *serial, struct fileinfo f)
{

    // create buffers for each field
    // char path_buffer[MAXPATH];
    // char mode_buffer[24];
    // char hash_buffer[HASH_SIZE];
    // char size_buffer[24];  

    // read in first X bytes into each buffer 
    
    // populate struct fields 
}