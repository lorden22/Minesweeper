#include <iostream>
#include "Minesweeper.h"
#include "UserManager.h"

int main() {
    UserManager userManager;
    Minesweeper game(10, 10, 10);

    int choice;
    std::string username, password;

    std::cout << "1. Register\n2. Login\nChoose an option: ";
    std::cin >> choice;

    if (choice == 1) {
        std::cout << "Enter username: ";
        std::cin >> username;
        std::cout << "Enter password: ";
        std::cin >> password;

        if (!userManager.registerUser(username, password)) {
            return 1;
        }
    } else if (choice == 2) {
        std::cout << "Enter username: ";
        std::cin >> username;
        std::cout << "Enter password: ";
        std::cin >> password;

        if (!userManager.loginUser(username, password)) {
            return 1;
        }
    } else {
        std::cout << "Invalid choice.\n";
        return 1;
    }

    while (!game.isGameOver()) {
        game.display();
        int x, y;
        std::cout << "Enter your move (x y): ";
        std::cin >> x >> y;
        game.play(x, y);
    }

    return 0;
}
