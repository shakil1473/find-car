#include "Passenger.h"


Passenger::Passenger()
{
}

void Passenger::logIn()
{

    Database database;
    int connectionSuccess=0;
    connectionSuccess=database.createConnection();

    string username;
    cout << "username		:";
    getline(cin,username);

    string password;
    cout << "password		: ";
    getline(cin,password);

}

void Passenger::signUp()
{

    Database database;

    int connected = 0;
    int insertSuccessful = 0;

    connected = database.createConnection();

    if(connected)
    {
        do
        {
            cout<<"Name     : ";
            getline(cin,pasName);

            cout<<"Username : ";
            getline(cin,pasUsername);

            cout<<"Password : ";
            getline(cin,pasPassword);

            insertSuccessful = database.insertIntoDataBase(pasName,pasUsername,pasPassword);
        }
        while(!insertSuccessful);
    }
}

void Passenger::home()
{
    cout << "welcome to home" << endl;
}
void Passenger::passengerHome()
{

}

Passenger::~Passenger()
{
}

