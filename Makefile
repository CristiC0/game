all: main.o game.o cell.o
	g++ -o minesweeper main.o game.o cell.o

main.o: main.cpp game.o
	g++ -c main.cpp

game.o: game.cpp game.h cell.o
	g++ -c game.cpp

cell.o: cell.cpp cell.h
	g++ -c cell.cpp