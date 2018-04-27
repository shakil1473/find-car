#ifndef DRIVER_H
#define DRIVER_H
#include<iostream>
#include<string>
#include<mysql.h>
#include<windows.h>
#include"Database.h"

using namespace std;

class Driver
{

string driverName;
string driverUsername;
string driverPassword;
string route;
string mobile;
string changedInfo;
public:
    Driver();
    void logIn();
    void signUp();
    void home(string username);
    void showRoads();
    void changeInfo(string username,int option);
    virtual ~Driver();
};

#endif // DRIVER_H
