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
public:
    Driver();
    void logIn();
    void signUp();
    void home();
    virtual ~Driver();
};

#endif // DRIVER_H
