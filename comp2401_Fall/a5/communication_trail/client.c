#include "defs.h"

int main(){
    int client;
    char buffer[MAX_BUFF];
    setupClientSocket(&client,"127.0.0.1");
    // sendData(client,"-1");
    printf("Enter the data need to be sent : ");scanf("%s",&buffer);
    sendData(client,buffer);
}

// #include "defs.h"

// int main() {
//     int clientSocket;
//     char buffer[MAX_BUFF];
//     setupClientSocket(&clientSocket, "127.0.0.1");

//     // Send data to server
//     char message[] = "-1";
//     sendData(clientSocket, message);
//     printf("Sent to server: %s\n", message);

//     // Close socket
//     close(clientSocket);

//     return 0;
// }
