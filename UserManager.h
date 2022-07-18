#ifndef USERMANAGER_H
#define USERMANAGER_H

#include "User.h"
#include <mysql/mysql_driver.h>
#include <mysql/mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>

class UserManager {
private:
    sql::mysql::MySQL_Driver *driver;
    std::unique_ptr<sql::Connection> con;
    std::unique_ptr<sql::PreparedStatement> pstmt;
    std::unique_ptr<sql::ResultSet> res;

    std::string hashPassword(const std::string& password, const std::string& salt);
    std::string generateSalt();

public:
    UserManager();
    bool registerUser(const std::string& username, const std::string& password);
    bool loginUser(const std::string& username, const std::string& password);
};

#endif
