#Compiles the referee program
referee: referee.o lib.o
	gcc referee.o lib.o -o referee
referee.o: referee.c lib.h
	gcc -c referee.c

#Compiles the player program
player: player.o lib.o
	gcc player.o lib.o -o player
player.o: player.c lib.h
	gcc -c player.c

#Compiles the library used in player and referee programs
lib.o: lib.c lib.h
	gcc -c lib.c
	
clean:
	rm *.o player referee
clean_o:
	rm *.o

	