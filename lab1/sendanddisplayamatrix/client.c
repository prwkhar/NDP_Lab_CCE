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

    //input matrix
    int r;
    int c;
    printf("enter no of row\n");
    scanf("%d",&r);
    printf("enter no of col\n");
    scanf("%d",&c);
    int a[r][c];
    printf("enter the element of matrix\n");
    for(int i=0;i<r;i++)
    {
        for (int j=0;j<c;j++)
        {
            scanf("%d",&a[i][j]);
        }
    }
    
    //sending the matrix
    send(network_socket,&r,sizeof(int),0);
    send(network_socket,&c,sizeof(int),0);
    send(network_socket,a,sizeof(int)*r*c,0);


    printf("matrix sent-->\n");
    for(int i=0;i<r;i++)
    {
        for(int j=0;j<c;j++)
        {
            printf("%d ",a[i][j]);
        }
        printf("\n");
    }
    printf("data sent to the server");
    close(network_socket);
}