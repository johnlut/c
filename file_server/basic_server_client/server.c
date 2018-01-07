#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <unistd.h> 
#include <sys/types.h>
#include <sys/socket.h> 
#include <netinet/in.h>

int main(int argc, char *argv[])
{

    // variables
    int port = 9001;
    int sock_fd;
    int client_fd;
    int msg_len;
    struct sockaddr_in server;
    struct sockaddr_in client; 
    char buffer[255];
    
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

    while(1)
    {
        // reset buffer
        memset(buffer, '\0', sizeof buffer); 

        // read message from client
        msg_len = read(client_fd, buffer, sizeof(buffer)); 
        if(msg_len < 0)
        {
            perror("server: reading"); 
            close(sock_fd); 
            exit(1); 
        }

        // print message from client
        printf("client: %s\n", buffer);

        // reset buffer
        memset(buffer, '\0', sizeof(buffer)); 

        // get message to send to client
        fgets(buffer, sizeof buffer, stdin); 

        // send message to client
        msg_len = write(client_fd, buffer, strlen(buffer));
        if(msg_len < 0)
        {
            perror("server: writing"); 
            close(sock_fd); 
            exit(1); 
        }

        // exit connection
        int i = strncmp("exit", buffer, 4); 

        if(i == 0)
        {
            break; 
        }
    }

    // close sockets
    close(client_fd);
    close(sock_fd);
    return 0; 
}