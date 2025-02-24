#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8000
#define BUFFER_SIZE 1024

int main() {
    int server_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    char buffer[BUFFER_SIZE];

    server_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_socket == -1) {
        perror("Socket creation failed");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    addr_size=sizeof(client_addr);

    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Binding failed");
        exit(1);
    }

    printf("UDP Server listening on port %d...\n", PORT);
    char str[50];
    int size_client=sizeof(client_addr);
    int l;
    recvfrom(server_socket,&l,sizeof(int),0,(struct sockaddr*)&client_addr,&size_client);
    
    recvfrom(server_socket,&str,l*sizeof(char),0,(struct sockaddr*)&client_addr,&size_client);

    // Remove newline if present
    if (str[l - 1] == '\n') {
        str[l - 1] = '\0';
        l--;
    }
    printf("the string is-->%s\n",str);
    int is=1;
    for(int i=0;i<l/2;i++)
    {
        if(str[i]==str[l-1-i])
        continue;
        is=0;
    }
    size_client=sizeof(client_addr);
    sendto(server_socket,&is,sizeof(int),0,(struct sockaddr*)&client_addr,size_client);
    printf("closing the connection");
    close(server_socket);
    return 0;
}

