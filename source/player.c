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
	//Player Code
	int clientFd, serverLen, result;
	struct sockaddr_un serverUNIXAddress; //For address of server
	struct sockaddr* serverSockAddrPtr;   //Point to server address

	serverSockAddrPtr = (struct sockaddr*) &serverUNIXAddress;
	serverLen = sizeof(serverUNIXAddress);

	//Unix socket, bidrectional, protocol 0, default
	clientFd = socket(AF_UNIX, SOCK_STREAM, 0);
	serverUNIXAddress.sun_family = AF_UNIX; //DOMAIN
	strcpy(serverUNIXAddress.sun_path, "turn") ;//set name of socket

	do{
		result = connect(clientFd, serverSockAddrPtr, serverLen);
		if(result == -1){
			sleep(1);
		}
	}while(result == -1);

	printMenu();
	char playerOpt;
	scanf("%c", &playerOpt);
	if(playerOpt == '1' || playerOpt == '2' || playerOpt == '3'){
		char * ans = &playerOpt; //Create pointer to use in write()
		write(clientFd, ans, sizeof(ans)+1); //Send the the player option to server

		int playerOpt = atoi(ans); //Convert ans to integer 
		// atoi in mac: atoi(ans)/10;
		int computerOpt = readEnemyOpt(clientFd); //Get the answer from the server
		displayGame(computerOpt, playerOpt); //Display the result
		
	}else if(playerOpt == '4'){
		printf("Bye.\n");
	}else{
		printf("Invalid option, execute the program again.\n");
	}

	close(clientFd);
	exit(0);
	return 0;
}

