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
public:
    Driver();
    void logIn();
    void signUp();
    virtual ~Driver();
};

#endif // DRIVER_H
