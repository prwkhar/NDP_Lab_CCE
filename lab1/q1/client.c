#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8000
#define BUFFER_SIZE 1024

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Socket creation failed");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Connection failed");
        exit(1);
    }

    printf("Connected to the server.\n");

    while (1) {
        int choice, n, num, i;
        printf("\nMenu:\n1. Search Number\n2. Sort Ascending\n3. Sort Descending\n4. Split Odd/Even\n5. Exit\nEnter choice: ");
        scanf("%d", &choice);

        if (choice == 5) {
            send(client_socket, "exit", 4, 0);
            printf("Exiting...\n");
            break;
        }

        printf("Enter number of elements: ");
        scanf("%d", &n);

        int arr[50];
        printf("Enter elements: ");
        for (i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
        }

        if (choice == 1) {
            printf("Enter number to search: ");
            scanf("%d", &num);
            sprintf(buffer, "%d %d ", choice, n);
        } else {
            sprintf(buffer, "%d %d ", choice, n);
        }

        for (i = 0; i < n; i++) {
            char numStr[10];
            sprintf(numStr, "%d ", arr[i]);
            strcat(buffer, numStr);
        }

        if (choice == 1) {
            char numStr[10];
            sprintf(numStr, "%d", num);
            strcat(buffer, numStr);
        }

        send(client_socket, buffer, strlen(buffer), 0);
        recv(client_socket, buffer, BUFFER_SIZE, 0);
        printf("\nServer Response:\n%s\n", buffer);
    }

    close(client_socket);
    return 0;
}
