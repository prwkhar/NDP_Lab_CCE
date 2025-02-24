#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>

main()
{
    int s,r,recb,sntb,x;
    int ca;
    printf("INPUT PORT NUMBER");
    scanf("%d",&x);
    socklen_t len;
    struct sockaddr_in server,client;
    char buff[50];
    s=socket(AF_INET,SOCK_)
}

