#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define PORT 8080

int main() {
    // Creating the socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        printf("[-]Error in socket creation.\n");
        exit(1);
    }
    printf("[+]Client socket created successfully.\n");

    // Define the server address
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Connect to the server
    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        printf("[-]Connection to server failed.\n");
        exit(1);
    }
    printf("[+]Connected to the server.\n");

    // Receiving welcome message from server

    while (1) {
        printf("\nChoose an option:\n");
        printf("1. Insert a book\n");
        printf("2. Delete a book\n");
        printf("3. View all books\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");

        int choice;
        scanf("%d", &choice);
        send(client_socket, &choice, sizeof(int), 0);  // Send choice to server

        if (choice == 1) {  
            // Insert a book
            char title[50], author[50], publisher[50];

            printf("Enter book title: ");
            scanf(" %[^\n]", title);
            printf("Enter author name: ");
            scanf(" %[^\n]", author);
            printf("Enter publisher name: ");
            scanf(" %[^\n]", publisher);

            send(client_socket, title, sizeof(title), 0);
            send(client_socket, author, sizeof(author), 0);
            send(client_socket, publisher, sizeof(publisher), 0);

            int status;
            recv(client_socket, &status, sizeof(int), 0);
            if (status == 1)
                printf("[-]Database full. Cannot add more books.\n");
            else
                printf("[+]Book inserted successfully!\n");

        } else if (choice == 2) {  
            // Delete a book
            char book_name[50];
            printf("Enter book title to delete: ");
            scanf(" %[^\n]", book_name);
            send(client_socket, book_name, sizeof(book_name), 0);

            int response;
            recv(client_socket, &response, sizeof(int), 0);
            if (response == 1)
                printf("[+]Book deleted successfully!\n");
            else
                printf("[-]Book not found!\n");

        } else if (choice == 3) {  
            // View all books
            char buffer[1024];
            recv(client_socket, buffer, sizeof(buffer), 0);
            printf("Book List:\n%s", buffer);

        } else if (choice == 5) {  
            // Exit the program
            printf("[+]Exiting client.\n");
            close(client_socket);
            exit(0);
        } else {
            printf("[-]Invalid choice. Try again!\n");
        }
    }

    return 0;
}
