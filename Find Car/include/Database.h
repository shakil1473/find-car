#ifndef DATABASE_H
#define DATABASE_H
#include <mysql.h>
#include <windows.h>
#include <string>
#include <iostream>
using namespace std;

class Database
{
    string dName;
    string dUsername;
    string dPassword;
    string dMobile;
    string dPickUpOne;
    string dPickUpTwo;
    string dFair;
public:
    Database();
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;

    string insertQuery;
    int queryState;
    const char* query;

    int createConnection();
    int checkUserNameAvailability(string userName,char userType);
    int checkUserValidity(string userName,string password,char userType);

    int driverInfoChange(string username,string changedInfo,int option);

    int insertIntoDataBase(string name,string username,string password);
    int insertIntoDataBase(string pickUpOne,string pickUpTwo,string fair,char route);
    int insertIntoDataBase(string username,string road,string currentLocation,int available);
    int insertIntoDataBase(string driverName,string driverUsername,string driverPassword,string mobile);

    void deleteUser(char userType);
    virtual ~Database();
};

#endif // DATABASE_H


