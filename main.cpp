#include <iostream>
#include <windows.h>
#include "game.h"
using namespace std;

int main(int argc, char *argv[])
{
    srand(GetTickCount());
    Game g(4, 6);
    g.play();
    return system("pause");
}