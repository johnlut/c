#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <unistd.h> 
#include <sys/types.h>
#include <sys/socket.h> 
#include <netinet/in.h>
#include<arpa/inet.h>

#define MIN(a,b) (((a)<(b))?(a):(b))

#define FILE_TO_REC "file2.txt"

int main(int argc, char *argv[])
{

    // variables
    int port = 9001; 
    int sock_fd; 
    struct sockaddr_in server; 
    

    socklen_t server_len;

    // creat socket
    sock_fd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sock_fd < 0)
    {
        perror("client: socket"); 
        exit(1);
    }

    // configure server struct
    server.sin_family = AF_INET; 
    server.sin_port = htons(port); 
    server.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    memset(server.sin_zero, '\0', sizeof(server.sin_zero));

    // connect to server
    server_len = sizeof(server); 
    if(connect(sock_fd, (struct sockaddr *) &server, server_len) < 0)
        {
            perror("client: connect"); 
            close(sock_fd);
            exit(1); 
        } 

    // CLIENT CONNECTED // 
    
    FILE * file_fd; 
    size_t nrecv; 
    size_t nwrit;
    int to_get; 
    int offset; 
    char buffer[24]; 

    // open new file
    file_fd = fopen("file2.txt", "w"); 
    if(file_fd == NULL) 
    {
        perror("client: file open");
        exit(1);
    }

    // get size of file
    nrecv = read(sock_fd, buffer, sizeof(buffer));
    if(nrecv < 0) 
    {
        perror("client: get file size"); 
        exit(1);
    }

    to_get = atoi(buffer);

    // clear buffer 
    memset(buffer, '\0', sizeof(buffer));

    printf("recieving file of size %d bytes\n", to_get);

   // recv file
    while(to_get > 0)   
    {
        offset = MIN(sizeof(buffer), to_get);   

        nrecv = read(sock_fd, buffer, offset);
        if(nrecv < 0) 
        {
            perror("client: file recv");
            exit(1); 
        }
        nwrit = fwrite(buffer, 1, nrecv, file_fd); 
        if(nwrit < 0) 
        {
            perror("client: file writing");
            exit(1); 
        }

        to_get -= nrecv; 

        memset(buffer, 0, sizeof(buffer)); 
        printf("recieved: %zu bytes, %d bytes left\n", nrecv, to_get);
    }

    // close sockets
    fclose(file_fd);
    close(sock_fd);
    return 0;
}
