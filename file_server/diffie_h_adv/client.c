#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <unistd.h> 
#include <sys/types.h>
#include <sys/socket.h> 
#include <netinet/in.h>
#include<arpa/inet.h>

#include <math.h> 

int auth(int client_fd); 

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
    auth(sock_fd); 

    // close sockets
    close(sock_fd);
    return 0;
}

int auth(int sock_fd)
{

    int nsent; 
    int nrecv; 
    char buffer[255]; 

    unsigned long server_key; 
    unsigned long shared_key; 

    // shared private key
    unsigned long p = 337016056721; 
    unsigned long q = 192837465;

    // client private key
    unsigned long b = 56565656;  

    // client public key
    unsigned long b_pub = ((long int) powl(q, b))%p;  

    // recieve server key
    printf("receiving server key\n");
    nrecv = recv(sock_fd, buffer, sizeof(buffer), 0); 
    server_key = atoi(buffer); 
    memset(buffer, '\0', sizeof(buffer)); 

    // send client key
    printf("sening client key\n");
    sprintf(buffer, "%ld", b_pub); 
    nsent = send(sock_fd, buffer, strlen(buffer), 0); 

    // computer shared key
    shared_key = ((long int) powl(server_key, b))%p; 

    printf("shared secret key: %lu\n", shared_key);


    return 0; 
}