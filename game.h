#pragma once
#include <iostream>
#include <string>
#include <windows.h>
#include "cell.h"
using namespace std;

class Game
{
public:
    ~Game();

    Game(int x, int y);

    void play();

private:
    void makeMove(int x, int y, string a);

    bool openCell(int x, int y);

    void drawBoard();

    void checkWin();

    void gameOver();

    void lastMsg(string s);

    bool isInside(int x, int y);

    void recOpen(int x, int y);

    int getMineCount(int x, int y);

    int width, height, mMines, oMines;
    Cell *board;
    bool start;
    int graphs[6];
};
