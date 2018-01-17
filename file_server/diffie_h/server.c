#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <unistd.h> 
#include <sys/types.h>
#include <sys/socket.h> 
#include <netinet/in.h>

#include <math.h> 

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
    int nsent; 
    int nrecv; 

    unsigned long client_key; 
    unsigned long shared_key; 

   // shared private key
    unsigned long p = 337016056721; 
    unsigned long q = 192837465;

    // server private key
    unsigned long a = 24242424;     

    // server public key
    unsigned long a_pub = ((long int) powl(q, a))%p; 

    // send client server public key
    //char server_key[sizeof(buffer)]; 
    sprintf(buffer, "%ld", a_pub); 
    nsent = send(client_fd, buffer, strlen(buffer), 0); 
    memset(buffer, '\0', sizeof(buffer)); 

    // recieve client key 
    nrecv = recv(client_fd, buffer, sizeof(buffer), 0); 
    client_key = atoi(buffer); 

    // compute shared secret key
    shared_key = ((long int) powl(client_key, a))%p; 

    printf("shared secret key: %lu\n", shared_key);

    // close sockets
    close(client_fd);
    close(sock_fd);
    return 0; 
}