#include "Board.h"
#include <iostream>
#include <cstdlib>

Board::Board(int width, int height, int mines) : WIDTH(width), HEIGHT(height), MINES(mines) {
    srand(time(0));
    initializeBoard();
}

void Board::initializeBoard() {
    board.resize(HEIGHT, std::vector<char>(WIDTH, '0'));
    displayBoard.resize(HEIGHT, std::vector<char>(WIDTH, '*'));
    placeMines();

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (board[y][x] != 'M') {
                int mineCount = 0;
                for (int i = -1; i <= 1; i++) {
                    for (int j = -1; j <= 1; j++) {
                        if (x + j >= 0 && x + j < WIDTH && y + i >= 0 && y + i < HEIGHT && board[y + i][x + j] == 'M') {
                            mineCount++;
                        }
                    }
                }
                board[y][x] = mineCount + '0';
            }
        }
    }
}

void Board::placeMines() {
    int placedMines = 0;
    while (placedMines < MINES) {
        int x = rand() % WIDTH;
        int y = rand() % HEIGHT;
        if (board[y][x] != 'M') {
            board[y][x] = 'M';
            placedMines++;
        }
    }
}

void Board::display() const {
    for (const auto& row : displayBoard) {
        for (const auto& cell : row) {
            std::cout << cell << ' ';
        }
        std::cout << '\n';
    }
}

bool Board::isMine(int x, int y) const {
    return board[y][x] == 'M';
}

void Board::reveal(int x, int y) {
    displayBoard[y][x] = board[y][x];
}

bool Board::isRevealed(int x, int y) const {
    return displayBoard[y][x] != '*';
}

char Board::getCell(int x, int y) const {
    return board[y][x];
}

bool Board::isZero(int x, int y) const {
    return board[y][x] == '0';
}
