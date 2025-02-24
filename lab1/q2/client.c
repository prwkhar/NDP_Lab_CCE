#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdbool.h>

#define PORT 8000
#define BUFFER_SIZE 1024

int main() {
    int client_socket;
    struct sockaddr_in server_addr;

    client_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (client_socket == -1) {
        perror("Socket creation failed");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("enter the string to send\n");
    char str[20];
    fgets(str,20,stdin);
    int l=strlen(str);
    sendto(client_socket,&l,sizeof(int) , 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
    sendto(client_socket,str, strlen(str)*sizeof(char), 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
    int f;
    int size=sizeof(server_addr);
    recvfrom(client_socket,&f,sizeof(int),0, (struct sockaddr*)&server_addr, &size);
    if(f==1)
    printf("yes the string in palindrome");
    else
    printf("no the string is not palindrome");

    printf("work done program is closing");

    close(client_socket);
    return 0;
}