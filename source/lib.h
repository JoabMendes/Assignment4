
/* Prints the menu for the player screen */
void printMenu();

/* Generates a random number from 1 to 3 */
int makeRand();

/* Function that receives a file descriptor, read one char and convert it to integer */
int readEnemyOpt(int fd);

/* displayGame() function auxiliar */
void printObejct(char * player, int obj);

/* Shows a formated output of the matching results */
void displayGame(int refereeOpt,int playerOpt);

/* Function used on the referee program to send a answer back to the player */
void answerPlayer(int clientFd, int refereeOpt);





