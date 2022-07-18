#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include "Board.h"

class Minesweeper {
private:
    Board board;
    bool gameOver;

public:
    Minesweeper(int width, int height, int mines);
    void display() const;
    void play(int x, int y);
    bool isGameOver() const;
};

#endif
