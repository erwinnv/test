run: game.exe
	./game.exe

interactive: game_interactive.exe
	./game_interactive.exe

generate: generate_map.exe
	./generate_map.exe

game.exe: game.o map.o
	gcc -mavx2 -Ofast -std=c99 -Wall -Wpedantic game.o map.o -o game.exe

game.o: game.c
	gcc -mavx2 -Ofast -c -std=c99 -Wall -Wpedantic game.c

map.o: map.c
	gcc -mavx2 -Ofast -c -std=c99 -Wall -Wpedantic map.c

game_interactive.exe: game_interactive.o map.o
	gcc -mavx2 -Ofast -std=c99 -Wall -Wpedantic game_interactive.o map.o -o game_interactive.exe
	
game_interactive.o: game_interactive.c
	gcc -mavx2 -Ofast -c -std=c99 -Wall -Wpedantic game_interactive.c

generate_map.o: generate_map.c
	gcc -mavx2 -Ofast -c -std=c99 -Wall -Wpedantic generate_map.c

map_generator.o: map_generator.c
	gcc -mavx2 -Ofast -c -std=c99 -Wall -Wpedantic map_generator.c

generate_map.exe: map.o generate_map.o map_generator.o
	gcc -mavx2 -Ofast -std=c99 -Wall -Wpedantic generate_map.o map.o map_generator.o -o generate_map.exe
