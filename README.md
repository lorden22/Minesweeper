# Minesweeper Project

## Overview

This project is a simple implementation of the classic Minesweeper game in C++. The game includes user registration and login functionality using a MySQL database to store user credentials securely with proper hashing

## Features

- **User Registration and Login**: Users can register and login, with credentials stored in a MySQL database.
- **Password Hashing**: Passwords are hashed using OpenSSL for security.
- **Game Mechanics**: Implements the core mechanics of Minesweeper in a terminal based game, including mine placement and user movement
z
## Prerequisites

- **C++11 or higher**: Ensure you have a compiler that supports C++11.
- **MySQL Connector/C++**: Required for database interaction.
- **OpenSSL**: Used for password hashing.
- **CMake**: Recommended for building the project.

## Setup and Compilation

1. **Install Dependencies**:
   ```bash
   brew install mysql-connector-c++ openssl cmake

2. **Clone the Repository:
   ```bash
   git clone https://github.com/lorden22/Minesweeper.git
   cd minesweeper

3. **Build and Run the Project
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ../minesweeper
