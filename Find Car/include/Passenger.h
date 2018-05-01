#ifndef PASSENGER_H
#define PASSENGER_H

#include <iostream>
#include <string>
#include <mysql.h>
#include <windows.h>
#include "Database.h"
#include "Admin.h"
using namespace std;

class Passenger
{

    string pasName;
    string pasUsername;
    string pasPassword;
public:
    Passenger();
    void logIn();
    void signUp();
    void home(string userName);
    void findCar();
    void showCars();
    void showDriver(string driverUsername,string currentLocation);

};

#endif // PASSENGER_H
