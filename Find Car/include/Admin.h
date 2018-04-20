#ifndef ADMIN_H
#define ADMIN_H
#include<iostream>
#include<string>
#include<mysql.h>
#include<windows.h>
#include "Database.h"

using namespace std;

class Admin
{
    string adminUserName;
    string adminPassword;
    string review;
    string seen;

public:
    Admin();
    void logIn();
    void home();
    void readUserReview();
    void addRoute();
    void writeUserReview(string suggestoions);

    int anyUserReview();
    virtual ~Admin();

};

#endif // ADMIN_H
