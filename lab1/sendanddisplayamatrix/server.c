#include <stdio.h>
#include <stdlib.h>
#include<sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include<netinet/in.h>

int main(){
    char server_message[256]="socket programming in c";

    //creating the server socket

    //AF_INET is for the IPv4
    //SOCK_STREAM if for the TCP protocol
    int server_socket=socket(AF_INET,SOCK_STREAM,0);//by default i am using tcp protocol therefore we put 0
    
    //define the server address
    struct sockaddr_in server_address;
    server_address.sin_family=AF_INET;
    server_address.sin_port=htons(8080);
    server_address.sin_addr.s_addr=INADDR_ANY;

    //bind the ip and port to the server
    bind(server_socket,(struct sockaddr*)& server_address,sizeof(server_address));

    //listen the port
    listen(server_socket,5);

    //accept the incoming connection from the client
    int client_socket;
    client_socket=accept(server_socket,NULL,NULL);

    int r,c;
    recv(client_socket,&r,sizeof(int),0);
    recv(client_socket,&c,sizeof(int),0);
    int mat[r][c];
    recv(client_socket,mat,sizeof(int)*r*c,0);
    
    printf("matrix recieved\n");
    for(int i=0;i<r;i++)
    {
        for(int j=0;j<c;j++)
        {
            printf("%d ",mat[i][j]);
        }
        printf("\n");
    }
    printf("server closed....");
    close(client_socket);
    close(server_socket);
    
}