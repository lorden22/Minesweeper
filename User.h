#ifndef USER_H
#define USER_H

#include <string>

class User {
public:
    std::string username;
    std::string hashed_password;
    std::string salt;
};

#endif
