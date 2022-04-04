/*
* Author: Meghana Vadassery
* Date: 12/5/21
* Description: This program acts as the client in a bidirection communication between two programs -- itself and the server.
  The client takes in a valid netID for a student, along with the port number and IP address of the server with which it wishes to connect with. If communication is established, then the server sends back a message along with a number. The client program encrypts this message using the Caesar cipher, in which all letters of the message are shifted forward by however many spaces given. The client returns this message, and if it is correct, the server sends another one back. This process may continue for as many times as the server likes, until it sends a final message with a flag. The sockets are then closed, ending communication.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

// finalString is a character array used by both the main function and th encryptMessage function, so it remains in the heap for easier access.

char finalString[1000];

//this function handles the encryption of the server's message and formatting a message for the client to send. It takes in the pointer for the server's message.

char *encryptMessage (char *serverMessage) {

  int key;
  char *token;
  char string[200];
  char newString[200];

  // memset resets the newString and finalString arrays. It sets every value to 0.
  memset(newString, 0, 200);
  memset(finalString, 0, 1000);

  //token uses strtok to split the server's message into seperate parts, all divided by the space. The server's message follows the format: cs230 STATUS __(number of shifts) _________(message to be encrypted)\n
  token = strtok(serverMessage, " ");
  int i = 0;
  while (token != NULL) {
    i++;
    token = strtok(NULL, " ");
    // the third word of the server's message is the number of shifts or, if it's the last message, it must be 'bye'. When i == 2, token now contains that third word. We compare it to the word "bye\n". if it's a match, we give final string the word "bye" and return it.
    if (i == 2) {
      if (strcmp(token, "bye\n") == 0){
	strcpy(finalString, "bye");
	return finalString;
      }
      //Otherwise, using AsciiToInteger, we convert the number into an integer stored in int key
      key = atoi(token);
    }
    // The fourth word is the message to be encrypted. We will move it to string
    if (i == 3) {
      strcpy(string, token);
    }
  }
  i = 0;
  int k;
  // while the ith position of string is not empty...
  while (string[i] != 0) {
    // the backslash \ has an ASCII value of 10. If we find that during out iteration through the array, we must stop. We can copy \n into the newString (\n acts as a single newline character
    if (string[i] == 10) {
      newString[i] = string[i];
      break;
    }
    //move the letter up by key positions
    k = string[i] + key;
    //if we go past the ASCII value of Z (which is 90), we must loop back. So we subtract 91 and then add 65
    if (k > 90) {
      newString[i] = 65 + (k-91);
    } else {
      newString[i] = k;
    }
    i++;
  }
  // copy the first part of our response, cs230, and then concatonate the encrytped message
  strcpy(finalString, "cs230 ");
  return  strcat(finalString, newString);
  
}


int main(int argc, char* argv[])
{
  // if the number of arguments are less than 4, we can exit from the program
  if (argc < 4) {
    printf("Error. Needs more arguments.\n");
    exit(0);
  }
  
    int socketDesc;
    struct sockaddr_in server_addr;
    char serverMsg[2000];
    char clientMsg[2000];
    char *newReply;
    
    memset(serverMsg,'\0',sizeof(serverMsg));
    memset(clientMsg,'\0',sizeof(clientMsg));
    
    
    // Create socket:
    socketDesc = socket(AF_INET, SOCK_STREAM, 0);
    
    // if the socket cannot be created, it returns a value less than 0
    if(socketDesc < 0){
        printf("Cannot create socket\n");
        return -1;
    }
    
    printf("Socket created\n");

    // Set port and IP the same as server-side:
    server_addr.sin_family = AF_INET;
    //the port number will be the third argument in the command line (we count ./client to be argv[0]
    server_addr.sin_port = htons(atoi(argv[2]));
    //inet_addr converts a string ip address to an actual address that the program can decipher
    server_addr.sin_addr.s_addr = inet_addr(argv[3]);
    
    // Send connection request to server:
    if(connect(socketDesc, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){
        printf("Unable to connect\n");
        return -1;
    }

    printf("Connected with server successfully\n");

    // send a message from the client that is in the format cs230 HELLO ______(netID)\n
    strcpy(clientMsg, "cs230 HELLO ");
    strcat(clientMsg, argv[1]);
    strcat(clientMsg, "\n");

    // Send the message to server:
    if(send(socketDesc, clientMsg, strlen(clientMsg), 0) < 0){
       printf("Unable to send message\n");
       return -1;
     }

    if(recv(socketDesc, serverMsg, sizeof(serverMsg), 0) < 0){
        printf("Cannot recieve server's message\n");
       return -1;
    }

    int count = 0;
    
    while (1) {
      newReply = encryptMessage(serverMsg);
      //if server says 'bye', then encryptMessage must have returned "bye"
      if (strcmp(newReply, "bye") == 0) {
        break;
      }
      
      if(send(socketDesc, newReply, strlen(newReply), 0) < 0){
	printf("Unable to send message: %s\n", newReply);
	return -1;
      }
      
      if(recv(socketDesc, serverMsg, sizeof(serverMsg), 0) < 0){
	printf("Unable to receive server's message\n");
	return -1;
      }
      
      printf("Server response: %s\n",serverMsg);

      count++;
    }

    printf("Close Connection, total attempts = %d\n", count);
    close(socketDesc);
    return 0;
    
}
