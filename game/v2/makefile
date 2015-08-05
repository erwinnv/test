run: game.exe
	./game.exe
game.exe: game.o map.o
	gcc -std=c99 -Wall -Wpedantic game.o map.o -o game.exe

game.o: game.c
	gcc -c -std=c99 -Wall -Wpedantic game.c

map.o: map.c
	gcc -c -std=c99 -Wall -Wpedantic map.c

interactive: game_interactive.exe
	./game_interactive.exe

game_interactive.exe: game_interactive.o map.o
	gcc -std=c99 -Wall -Wpedantic game_interactive.o map.o -o game_interactive.exe
	
game_interactive.o: game_interactive.c
	gcc -c -std=c99 -Wall -Wpedantic game_interactive.c
