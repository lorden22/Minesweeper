#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <ctime>

class Board {
private:
    std::vector<std::vector<char> > board;
    std::vector<std::vector<char> > displayBoard;
    const int WIDTH;
    const int HEIGHT;
    const int MINES;

    void initializeBoard();
    void placeMines();

public:
    Board(int width, int height, int mines);
    void display() const;
    bool isMine(int x, int y) const;
    void reveal(int x, int y);
    bool isRevealed(int x, int y) const;
    char getCell(int x, int y) const;
    bool isZero(int x, int y) const;
    int getWidth() const { return WIDTH; }
    int getHeight() const { return HEIGHT; }
};

#endif
