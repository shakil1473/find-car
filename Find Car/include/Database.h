#ifndef DATABASE_H
#define DATABASE_H
#include <mysql.h>
#include <windows.h>
#include <string>
#include <iostream>
using namespace std;

class Database
{
    string pasName;
    string pasUsername;
    string pasPassword;
public:
    Database();
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    int createConnection();
    int checkAvailability(string userName);
    int insertIntoDataBase(string name,string username,string password);
    virtual ~Database();
};

#endif // DATABASE_H


