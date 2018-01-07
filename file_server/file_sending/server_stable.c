#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <unistd.h> 
#include <sys/types.h>
#include <sys/socket.h> 
#include <netinet/in.h>
#include <sys/stat.h>

//#define MIN(a,b) (((a)<(b))?(a):(b))

int send_file(int sock_fd, int client_fd, FILE * file_fd); 

int main(int argc, char *argv[])
{

    // variables
    int port = 9001;
    int sock_fd;
    int client_fd;
    int msg_len;
    struct sockaddr_in server;
    struct sockaddr_in client; 
    //char buffer[255];
    
    socklen_t client_len; 

    // create socket
    sock_fd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sock_fd < 0)
    {
        perror("server: socket");
        exit(1);
    }

    // configure server struct
    server.sin_family = AF_INET; 
    server.sin_port = htons(port); 
    server.sin_addr.s_addr = INADDR_ANY;
    memset(server.sin_zero, '\0', sizeof(server.sin_zero));

    // bind socket
    if (bind(sock_fd, (struct sockaddr *)&server, sizeof(struct sockaddr_in)) < 0) 
    {
        perror("server: bind");
        close(sock_fd);
        exit(1);
    }

    // listen to socket
    listen(sock_fd, 5); 

    // accept a client
    client_len = sizeof(client); 
    client_fd = accept(sock_fd, (struct sockaddr *) &client, &client_len);
    if(client_fd < 0)
    {
        perror("server: accept"); 
        close(sock_fd);
        exit(1);
    }

    // CLIENT CONNECTED // 

    FILE * file_fd; 
    size_t nread; 
    size_t nsent; 
    struct stat st;  
    int to_send;
    char buffer[24];  

    // open file
    file_fd = fopen("file.txt", "r"); 
    if(file_fd == NULL) 
    {
        perror("server: file open"); 
        exit(1);
    }

    // get file size 
    if(stat("file.txt", &st) < 0)
    {
        perror("server: file stat"); 
        exit(1);
    } 
    to_send = st.st_size; 
    printf("size of file: %d bytes\n", to_send);

    // send size of file
    sprintf(buffer, "%d", to_send);  
    nsent = write(client_fd, buffer, sizeof(buffer));   
    if(nsent < 0)
    {
        perror("server: send file size"); 
        exit(1); 
    }

    // clear buffer 
    memset(buffer, '\0', sizeof(buffer));

    // send file
    while (to_send > 0)
    {

        nread = fread(buffer, 1, sizeof(buffer), file_fd); 
        if(nread < 0)
        {
            perror("server: read file"); 
            exit(1); 
        }

        nsent = write(client_fd, buffer, nread);
        if(nsent < 0)
        {
            perror("server: send file"); 
            exit(1); 
        }

        to_send -= nsent; 

        memset(buffer, 0, sizeof(buffer)); 
        printf("sent: %zu bytes, %d bytes left\n", nsent, to_send);
    }

    // close sockets
    close(client_fd);
    close(sock_fd);
    return 0; 
}

int send_file(int sock_fd, int client_fd, FILE * file_fd)
{





    return 0; 
} 