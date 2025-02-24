#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>

int main(){
    //create a socket
    int network_socket=socket(AF_INET,SOCK_STREAM,0);

    //specify the address of the socket
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port= htons(8080);
    server_address.sin_addr.s_addr=INADDR_ANY;

    //connection request

    int conn=connect(network_socket,(struct sockaddr*)& server_address,sizeof(server_address));
    if(conn==-1)
    printf("there is some error in the connection");

    //recieve the data from the server
    char msg[256]={0};
    recv(network_socket,&msg,sizeof(msg),0);

    printf("the server sends the data ---> %s\n",msg);
    close(network_socket);
    return 0;
}