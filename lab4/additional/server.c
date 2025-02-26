#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>

#define MAX_DATA 10
int current_ind = 0;
struct database {
    char title[50];
    char author[50];
    char publisher[50];
};

int main() {
    char server_message[256] = "socket programming in c";

    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    
    struct database db[MAX_DATA] = {
        {"C Programming", "Dennis Ritchie", "Prentice Hall"},
        {"Data Structures", "Mark Weiss", "Pearson"},
        {"Operating Systems", "Abraham Silberschatz", "Wiley"},
        {"Computer Networks", "Andrew Tanenbaum", "Pearson"},
        {"Artificial Intelligence", "Stuart Russell", "Pearson"}
    };
    current_ind = 5;

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // ✅ Fixed syntax error (removed extra `;`)
    if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        perror("binding error");
        exit(1);
    }

    // ✅ Fixed syntax error (removed extra `;`)
    if (listen(server_socket, 5) < 0) {
        perror("listening error");
        exit(1);
    }

    int client_socket;
    client_socket = accept(server_socket, NULL, NULL);

    // ✅ Fixed incorrect check (`< 1` → `< 0`)
    if (client_socket < 0) {
        perror("client socket creation error");
        exit(1);
    }

    send(client_socket, server_message, sizeof(server_message), 0);

    while (1) {
        int opt = 0;
        recv(client_socket, &opt, sizeof(int), 0);
        if (opt == 5)
            break;
        else if (opt == 1) {
            if (current_ind >= MAX_DATA) {
                int issue = 1;
                send(client_socket, &issue, sizeof(int), 0);
                continue;
            }
            char title1[50] = {""};
            char author1[50] = {""};
            char publisher1[50] = {""};
            recv(client_socket, &title1, sizeof(char) * 50, 0);
            recv(client_socket, &author1, sizeof(char) * 50, 0);
            recv(client_socket, &publisher1, sizeof(char) * 50, 0);
            strcpy(db[current_ind].title, title1);
            strcpy(db[current_ind].author, author1);
            strcpy(db[current_ind].publisher, publisher1);
            current_ind++;
        }
        else if (opt == 3) {
            for (int i = 0; i < current_ind; i++) {
                printf("%s\n", db[i].title);
                printf("%s\n", db[i].author);
                printf("%s\n", db[i].publisher);
            }
        }
        else if (opt == 2) {
            char bookdelete[50];
            recv(client_socket, bookdelete, sizeof(bookdelete), 0);

            for (int i = 0; i < current_ind; i++) {
                if (strcmp(bookdelete, db[i].title) == 0) {
                    for (int j = i; j < current_ind - 1; j++) {
                        // ✅ Fixed incorrect struct assignment (used `strcpy`)
                        strcpy(db[j].title, db[j + 1].title);
                        strcpy(db[j].author, db[j + 1].author);
                        strcpy(db[j].publisher, db[j + 1].publisher);
                    }
                    current_ind--;
                    break;
                }
            }
        }
    }
    close(client_socket);
    close(server_socket);
    printf("server exiting");
}
