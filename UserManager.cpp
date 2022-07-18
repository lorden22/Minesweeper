#include "UserManager.h"
#include <openssl/sha.h>
#include <openssl/rand.h>
#include <iomanip>
#include <sstream>
#include <iostream>

UserManager::UserManager() {
    driver = sql::mysql::get_mysql_driver_instance();
    con.reset(driver->connect("tcp://127.0.0.1:3306", "root", "password"));
    con->setSchema("minesweeper_db");
}

std::string UserManager::hashPassword(const std::string& password, const std::string& salt) {
    std::string saltedPassword = password + salt;
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)saltedPassword.c_str(), saltedPassword.size(), hash);

    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return ss.str();
}

std::string UserManager::generateSalt() {
    unsigned char buffer[16];
    RAND_bytes(buffer, sizeof(buffer));
    std::stringstream ss;
    for (int i = 0; i < sizeof(buffer); ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)buffer[i];
    }
    return ss.str();
}

bool UserManager::registerUser(const std::string& username, const std::string& password) {
    try {
        pstmt.reset(con->prepareStatement("SELECT username FROM users WHERE username = ?"));
        pstmt->setString(1, username);
        res.reset(pstmt->executeQuery());

        if (res->next()) {
            std::cout << "Username already exists. Please choose a different username.\n";
            return false;
        }

        std::string salt = generateSalt();
        std::string hashedPassword = hashPassword(password, salt);

        pstmt.reset(con->prepareStatement("INSERT INTO users (username, hashed_password, salt) VALUES (?, ?, ?)"));
        pstmt->setString(1, username);
        pstmt->setString(2, hashedPassword);
        pstmt->setString(3, salt);
        pstmt->execute();

        std::cout << "User registered successfully.\n";
        return true;
    } catch (sql::SQLException &e) {
        std::cerr << "SQL Error: " << e.what() << std::endl;
        return false;
    }
}

bool UserManager::loginUser(const std::string& username, const std::string& password) {
    try {
        pstmt.reset(con->prepareStatement("SELECT hashed_password, salt FROM users WHERE username = ?"));
        pstmt->setString(1, username);
        res.reset(pstmt->executeQuery());

        if (res->next()) {
            std::string dbHashedPassword = res->getString("hashed_password");
            std::string dbSalt = res->getString("salt");
            std::string hashedPassword = hashPassword(password, dbSalt);

            if (hashedPassword == dbHashedPassword) {
                std::cout << "Login successful. Welcome " << username << "!\n";
                return true;
            } else {
                std::cout << "Invalid username or password.\n";
                return false;
            }
        } else {
            std::cout << "Invalid username or password.\n";
            return false;
        }
    } catch (sql::SQLException &e) {
        std::cerr << "SQL Error: " << e.what() << std::endl;
        return false;
    }
}
