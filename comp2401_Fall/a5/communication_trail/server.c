#include "defs.h"

int main(){
    int server,client;
    char buffer[MAX_BUFF];
    setupServerSocket(&server);
    printf("Sever socket established\n");
    acceptConnection(server,&client);
    printf("Client added\n");
    int id;
    id = rcvData(client,buffer);
    printf("data : %s",buffer);

}

// #include "defs.h"

// int main() {
//     int listenSocket, clientSocket;
//     char buffer[MAX_BUFF];

//     // Setup server socket
//     setupServerSocket(&listenSocket);

//     printf("Server is listening...\n");

//     // Accept connection from client
//     acceptConnection(listenSocket, &clientSocket);
//     printf("Connection accepted from client\n");

//     // Receive and display data from client
//     rcvData(clientSocket, buffer);
//     printf("Received from client: %s\n", buffer);

//     // Close sockets
//     close(listenSocket);
//     close(clientSocket);

//     return 0;
// }
