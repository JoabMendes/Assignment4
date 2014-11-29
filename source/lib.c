#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include  <fcntl.h>

#include <unistd.h>

#include "lib.h"


/* Prints the menu for the player screen */
void printMenu(){
	printf("Welcome to the Paper, Scissors and Rock game.\n");
	printf("You can choose:\n");
	printf("1 - Paper\n");
	printf("2 - Scissors\n");
	printf("3 - Rock\n");
	printf("4 - Quit\n");
	printf("Go\n");
	printf("Please enter your choice:\n");
}

/* Generates a random number from 1 to 3 */
int makeRand(){
	srand(time(NULL)); //Set seed as current time
	return rand()%3 + 1; //Return the a random number 1-3
}

/* Function that receives a file descriptor, read one char and convert it to integer */
int readEnemyOpt(int fd){
	char opt[1];
	read(fd, opt, 1);
	return atoi(opt); //atoi converts the chat to a integer
}

/* displayGame() function auxiliar */
//Will display the object of each player
void printObejct(char * player, int obj){
	switch(obj){
		case 1:
			printf("%s: Paper\n", player);
			break;
		case 2:
			printf("%s: Scissors\n", player);
			break;
		case 3:
			printf("%s: Rock\n", player);
			break;
		default:
			break;
	}
}

/* Shows a formated output of the matching results */
void displayGame(int refereeOpt, int playerOpt){
	printf("\n");
	printObejct("Player", playerOpt); //Show the player's option
	printObejct("Computer", refereeOpt); //Show the computer's option
	if(refereeOpt != playerOpt){ //if it's not match
		//Verify if computer won
		if(refereeOpt == 1 && playerOpt == 3){
			printf("Computer wins.\n\n");
		}else if(refereeOpt == 3 && playerOpt == 2){
			printf("Computer wins.\n\n");
		}else if(refereeOpt == 2 && playerOpt == 1){
			printf("Computer wins.\n\n");
		}else{ //otherwise the player won
			printf("Player wins.\n\n");
		}
	}else{
		printf("This turn was a draw!\n\n");
	}
}

/* Function used on the referee program to send a answer back to the player */
void answerPlayer(int clientFd, int refereeOpt){
	char opt = (char)(((int)'0')+refereeOpt); //convert in to char
	char *ans = &opt; //pointer to char
	write(clientFd, ans, sizeof(ans)+1); //write with the file descriptor
}

