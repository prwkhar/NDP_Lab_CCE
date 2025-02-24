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

void sortNumbers(int arr[], int n, int ascending) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if ((ascending && arr[j] > arr[j + 1]) || (!ascending && arr[j] < arr[j + 1])) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void splitOddEven(int arr[], int n, char *response) {
    char oddNumbers[BUFFER_SIZE] = "Odd: ";
    char evenNumbers[BUFFER_SIZE] = "Even: ";
    
    for (int i = 0; i < n; i++) {
        char numStr[20];
        sprintf(numStr, "%d ", arr[i]);

        if (arr[i] % 2 == 0)
            strcat(evenNumbers, numStr);
        else
            strcat(oddNumbers, numStr);
    }
    
    sprintf(response, "%s\n%s", oddNumbers, evenNumbers);
}

void handleClient(int client_socket) {
    while (1) {
        char buffer[BUFFER_SIZE];
        int received = recv(client_socket, buffer, sizeof(buffer), 0);
        if (received <= 0) {
            printf("\nClient disconnected.\n");
            break;
        }

        buffer[received] = '\0';
        printf("\nReceived: %s", buffer);

        if (strncmp(buffer, "exit", 4) == 0) {
            printf("\nClient requested exit.\n");
            break;
        }

        int choice, n, num, arr[50];
        sscanf(buffer, "%d %d", &choice, &n);
        char *ptr = strchr(buffer, ' ') + 1;
        ptr = strchr(ptr, ' ') + 1;

        for (int i = 0; i < n; i++) {
            sscanf(ptr, "%d", &arr[i]);
            ptr = strchr(ptr, ' ');
            if (ptr) ptr++;
        }

        char response[BUFFER_SIZE] = "";
        switch (choice) {
            case 1:  // Search number
                sscanf(ptr, "%d", &num);
                int found = 0;
                for (int i = 0; i < n; i++) {
                    if (arr[i] == num) {
                        found = 1;
                        break;
                    }
                }
                sprintf(response, "Number %d %s found.", num, found ? "is" : "is not");
                break;
            case 2:  // Sort Ascending
                sortNumbers(arr, n, 1);
                strcpy(response, "Sorted (Ascending): ");
                for (int i = 0; i < n; i++) {
                    char numStr[10];
                    sprintf(numStr, "%d ", arr[i]);
                    strcat(response, numStr);
                }
                break;
            case 3:  // Sort Descending
                sortNumbers(arr, n, 0);
                strcpy(response, "Sorted (Descending): ");
                for (int i = 0; i < n; i++) {
                    char numStr[10];
                    sprintf(numStr, "%d ", arr[i]);
                    strcat(response, numStr);
                }
                break;
            case 4:  // Split odd and even
                splitOddEven(arr, n, response);
                break;
            default:
                strcpy(response, "Invalid choice.");
                break;
        }

        send(client_socket, response, strlen(response), 0);
    }
    
    close(client_socket);
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Socket creation failed");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Binding failed");
        exit(1);
    }

    if (listen(server_socket, 5) == -1) {
        perror("Listening failed");
        exit(1);
    }

    printf("Server listening on port %d...\n", PORT);

    addr_size = sizeof(client_addr);
    while (1) {
        client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &addr_size);
        if (client_socket == -1) {
            perror("Accept failed");
            continue;
        }

        printf("\nClient connected.\n");
        handleClient(client_socket);
    }

    close(server_socket);
    return 0;
}
