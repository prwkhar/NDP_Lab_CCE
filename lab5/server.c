#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>

#define PORT 4444

void handle_exit(int sig) {
    printf("\nServer shutting down...\n");
    exit(0);
}

int main() {
    int sockfd, ret;
    struct sockaddr_in serverAddr;
    int newSocket;
    struct sockaddr_in newAddr;
    socklen_t addr_size;
    char buffer[1024];
    pid_t childpid;

    // Handle SIGINT (Ctrl+C) to gracefully close the server
    signal(SIGINT, handle_exit);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        printf("[-] Error in connection.\n");
        exit(1);
    }
    printf("[+] Server Socket is created.\n");

    memset(&serverAddr, '\0', sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    ret = bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if (ret < 0) {
        printf("[-] Error in binding.\n");
        exit(1);
    }
    printf("[+] Bind to port %d\n", PORT);

    if (listen(sockfd, 10) == 0) {
        printf("[+] Listening...\n");
    } else {
        printf("[-] Error in binding.\n");
        exit(1);
    }

    while (1) {
        addr_size = sizeof(newAddr);
        newSocket = accept(sockfd, (struct sockaddr*)&newAddr, &addr_size);
        if (newSocket < 0) {
            exit(1);
        }
        printf("Connection accepted from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));

        if ((childpid = fork()) == 0) {
            close(sockfd); // Child does not need server socket

            while (1) {
                bzero(buffer, sizeof(buffer)); // Clear buffer before receiving
                recv(newSocket, buffer, 1024, 0);

                if (strcmp(buffer, ":exit\n") == 0) {
                    printf("Disconnected from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
                    break;
                } else {
                    printf("Client: %s", buffer);
                    send(newSocket, buffer, strlen(buffer), 0);
                }
            }

            close(newSocket);
            exit(0);
        }
    }

    close(sockfd);
    return 0;
}
