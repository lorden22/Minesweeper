#include "Minesweeper.h"
#include <iostream>

Minesweeper::Minesweeper(int width, int height, int mines) : board(width, height, mines), gameOver(false) {}

void Minesweeper::display() const {
    board.display();
}

void Minesweeper::play(int x, int y) {
    if (x < 0 || x >= board.getWidth() || y < 0 || y >= board.getHeight()) {
        std::cout << "Invalid move. Try again.\n";
        return;
    }

    if (board.isMine(x, y)) {
        std::cout << "Game Over! You hit a mine.\n";
        gameOver = true;
        return;
    }

    board.reveal(x, y);
    if (board.isZero(x, y)) {
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (x + j >= 0 && x + j < board.getWidth() && y + i >= 0 && y + i < board.getHeight() && !board.isRevealed(x + j, y + i)) {
                    play(x + j, y + i);
                }
            }
        }
    }
}

bool Minesweeper::isGameOver() const {
    return gameOver;
}
find /path/to/extracted -name mysql_driver.h
