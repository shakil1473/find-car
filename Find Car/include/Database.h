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
    string carRoute;
    string carFair;
public:
    Database();
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;

    string insertQuery;
    int queryState;
    const char* query;

    int createConnection();
    int checkAvailability(string userName);
    int insertIntoDataBase(string route,string fair);
    int insertIntoDataBase(string name,string username,string password);
    virtual ~Database();
};

#endif // DATABASE_H


