#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <unistd.h> 
#include <sys/types.h>
#include <sys/socket.h> 
#include <netinet/in.h>
#include<arpa/inet.h>


int main(int argc, char *argv[])
{

    // variables
    int port = 9001; 
    int sock_fd; 
    int msg_len; 
    struct sockaddr_in server; 
    char buffer[255]; 

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
    
    while(1)
    {
        // reset buffer
        memset(buffer, '\0', sizeof buffer);

        // get message to send to server
        fgets(buffer, sizeof(buffer), stdin);

        // send message to server
        msg_len = write(sock_fd, buffer, strlen(buffer));
        if(msg_len < 0)
        {
            perror("client: writing");
            close(sock_fd);
            exit(1);
        }

        // reset buffer
        memset(buffer, '\0', sizeof buffer);

        // read message from server
        msg_len = read(sock_fd, buffer, sizeof(buffer));
        if(msg_len < 0)
        {
            perror("client: reading");
            close(sock_fd); 
            exit(1); 
        }
        // print message from server
        printf("server: %s\n", buffer);

        // exit connection
        int i = strncmp("exit", buffer, 4); 

        if(i == 0)
        {
            break; 
        }

    }

    // close sockets
    close(sock_fd);
    return 0;
}
