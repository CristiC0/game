#include "game.h"
Game::
    ~Game()
{
    if (board)
        delete[] board;
}

Game::Game(int x, int y)
{
    start = false;
    width = x;
    height = y;
    board = new Cell[x * y];
    memset(board, 0, x * y * sizeof(Cell));
    oMines = ((22 - rand() % 11) * x * y) / 100;
    mMines = 0;
    int mx, my, m = 0;
    for (; m < oMines; m++)
    {
        do
        {
            mx = rand() % width;
            my = rand() % height;
        } while (board[mx + width * my].mine);
        board[mx + width * my].mine = true;
    }
    graphs[0] = ' ';
    graphs[1] = '.';
    graphs[2] = '*';
    graphs[3] = '?';
    graphs[4] = '!';
    graphs[5] = 'X';
}

void Game::play()
{
    string c, r, a;
    int col, row;
    while (!start)
    {
        drawBoard();
        cout << "Enter column, row and an action( c r a ):\nActions: o => open, f => flag, ? => unknown\n";
        cin >> c >> r >> a;
        if (c[0] > 'Z')
            c[0] -= 32;
        if (a[0] > 'Z')
            a[0] -= 32;
        col = c[0] - 65;
        row = r[0] - 49;
        makeMove(col, row, a);
    }
}

void Game::makeMove(int x, int y, string a)
{
    Cell *fd = &board[width * y + x];
    if (fd->open && fd->value < CLOSED)
    {
        cout << "This cell is already open!";
        Sleep(3000);
        return;
    }
    if (a[0] == 'O')
        openCell(x, y);
    else if (a[0] == 'F')
    {
        fd->open = true;
        fd->value = FLAG;
        mMines++;
        checkWin();
    }
    else
    {
        fd->open = true;
        fd->value = UNKNOWN;
    }
}

bool Game::openCell(int x, int y)
{
    if (!isInside(x, y))
        return false;
    if (board[x + y * width].mine)
        gameOver();
    else
    {
        if (board[x + y * width].value == FLAG)
        {
            board[x + y * width].value = CLOSED;
            board[x + y * width].open = false;
            mMines--;
        }
        recOpen(x, y);
        checkWin();
    }
    return true;
}

void Game::drawBoard()
{
    system("cls");
    cout << "Marked mines: " << mMines << " from " << oMines << "\n\n";
    for (int x = 0; x < width; x++)
        cout << "  " << (char)(65 + x) << " ";
    cout << "\n";
    int yy;
    for (int y = 0; y < height; y++)
    {
        yy = y * width;
        for (int x = 0; x < width; x++)
            cout << "+---";

        cout << "+\n";
        Cell *fd;
        for (int x = 0; x < width; x++)
        {
            fd = &board[x + yy];
            cout << "| ";
            if (!fd->open)
                cout << (char)graphs[1] << " ";
            else
            {
                if (fd->value > 9)
                    cout << (char)graphs[fd->value - 9] << " ";
                else
                {
                    if (fd->value < 1)
                        cout << "  ";
                    else
                        cout << (char)(fd->value + 48) << " ";
                }
            }
        }
        cout << "| " << y + 1 << "\n";
    }
    for (int x = 0; x < width; x++)
        cout << "+---";

    cout << "+\n\n";
}

void Game::checkWin()
{
    int z = width * height - oMines, yy;
    Cell *fd;
    for (int y = 0; y < height; y++)
    {
        yy = width * y;
        for (int x = 0; x < width; x++)
        {
            fd = &board[x + yy];
            if (fd->open && fd->value != FLAG)
                z--;
        }
    }
    if (!z)
        lastMsg("Congratulations, you won the game!");
}

void Game::gameOver()
{
    int yy;
    Cell *fd;
    for (int y = 0; y < height; y++)
    {
        yy = width * y;
        for (int x = 0; x < width; x++)
        {
            fd = &board[x + yy];
            if (fd->value == FLAG)
            {
                fd->open = true;
                fd->value = fd->mine ? MINE : ERR;
            }
            else if (fd->mine)
            {
                fd->open = true;
                fd->value = MINE;
            }
        }
    }
    lastMsg("B O O O M M M M M !");
}

void Game::lastMsg(string s)
{
    start = true;
    drawBoard();
    cout << s << "\n\n";
}

bool Game::isInside(int x, int y) { return (x > -1 && y > -1 && x < width && y < height); }

void Game::recOpen(int x, int y)
{
    if (!isInside(x, y) || board[x + y * width].open)
        return;
    int bc = getMineCount(x, y);
    board[x + y * width].open = true;
    board[x + y * width].value = bc;
    if (bc)
        return;

    for (int yy = -1; yy < 2; yy++)
        for (int xx = -1; xx < 2; xx++)
        {
            if (xx == 0 && yy == 0)
                continue;
            recOpen(x + xx, y + yy);
        }
}

int Game::getMineCount(int x, int y)
{
    int m = 0;
    for (int yy = -1; yy < 2; yy++)
        for (int xx = -1; xx < 2; xx++)
        {
            if (xx == 0 && yy == 0)
                continue;
            if (isInside(x + xx, y + yy) && board[x + xx + (y + yy) * width].mine)
                m++;
        }

    return m;
}
