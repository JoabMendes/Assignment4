#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include  <fcntl.h>

#include <signal.h>
#include <unistd.h>

#include <sys/un.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "lib.h"


int main(){
	//Referee Code
	int serverFd, serverLen, clientFd;
	struct sockaddr_un serverUNIXAddress; //For address of server
	struct sockaddr* serverSockAddrPtr;   //Point to server address

	serverSockAddrPtr = (struct sockaddr*) &serverUNIXAddress;
	serverLen = sizeof(serverUNIXAddress);

	//Unix socket, bidrectional, protocol 0, default
	serverFd = socket(AF_UNIX, SOCK_STREAM, 0);
	serverUNIXAddress.sun_family = AF_UNIX; //DOMAIN
	strcpy(serverUNIXAddress.sun_path, "turn") ;//set name of socket
	unlink("turn");

	bind(serverFd, serverSockAddrPtr, serverLen);//create the socket file
	listen(serverFd, 5);

	printf("Paper, Scissors, Rock game start.\n");
	int status;
	while(1){ //wait forever
		printf("Waiting for player...\n");
		clientFd = accept(serverFd, 0, 0);
		if(fork() == 0){ //if connect create child
			printf("Player: ready. \n");
			printf("Go.\n");
			//Create Random number
			int refereeOpt = makeRand();
			//Read the number of the player
			int playerOpt = readEnemyOpt(clientFd); //Read a call from client
			if(playerOpt != 0){
				displayGame(refereeOpt, playerOpt); //Display the result number
			}else{
				printf("Player: disconnected.\n\n");
			}
			
			//Converts the integer of the option to a char
			answerPlayer(clientFd, refereeOpt);
			
			exit(0);
		}else{
			wait(&status);
			close(clientFd); //Close connnection with client
		}
	}

	return 0;
}

