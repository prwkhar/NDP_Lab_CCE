Final verdict and revision
Lab1
TCP => 
Server - server_socket, bind, listen, client_socket=accept . (here we have to make two sockets)
Client – socket and connect (we use network socket for both sending and receiving the data from the server).
UDP =>
Server – server_socket , bind , recvfrom , sendto
Client – socket, sendto and recvfrom (no need for bind here)

Lab2

To open a file -- FILE * fptr = fopen(“filename” , “r”);
To write in a file -- FILE* fptr = fopen(“filename” , “w”);
To get each line -- while(fgets(line,sizeof(line),fptr)!=NULL)
To check whether a word is there in line -- strstr(line, word); <it returns a position pointer>
To put a line in a file -- fputs(line,tempfile)
To close a file -- fclose(fptr)
To remove a file -- remove(“filename”)
To get each character -- while((ch =  fgetc(file))!=EOF) 

Basic string functions-
Strcpy – copy
Strcmp – compare
Strcat – append the string

Lab 3

Full Duplex connection ----> 

Pid_t pid =fork();
 If(pid==-1){frok failed}
If(pid==0){
//child process 
//create a while loop so that it can continue reading messages
}
Else{
Again a while loop so that it can continue sending messages to server 
}
}

So basically parent is sending messages all the time and child is receiving messages all the time 
In client side also we have to do the same thing (don’t forget to reset the buffer each time)


Half Duplex Communication ----->

Its basically depends on number of send and receive command you have used 
And all the commands will execute one by one handling one operation at a time

Additional process it commands

For countin process ----> just make a global variable count process
To get pid of process ----> getpid()
To get parent id of process ----> getppid();
To fork a process ----> pid_t pid =fork();  -1 error, 0 child , else parent


Lab 4 

Lab 4 is basically using structure in c programming and using above command wherever they are required 

Lab 5

Multiple client communication can be achieved using fork

Pid_t pid= fork();

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


Client in this case is normal

Child closes parent socket
Parent closes child socket

And at the end we obv close the main parent socket.
