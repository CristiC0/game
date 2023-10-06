#pragma once

typedef unsigned char charValue;
enum cellValues : charValue
{
    OPEN,
    CLOSED = 10,
    MINE,
    UNKNOWN,
    FLAG,
    ERR
};
class Cell
{
public:
    Cell();
    charValue value;
    bool open, mine;
};