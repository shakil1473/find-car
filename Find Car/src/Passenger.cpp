#include "../include/Passenger.h"


Passenger::Passenger()
{
}

void Passenger::logIn()
{

    Database database;
    int connectionSuccess=0;
    int validUser = 0;
    int attempt = 0;
    connectionSuccess=database.createConnection();

    string username;
    string password;




    do
    {
        cout << "username   :";
        getline(cin,username);
        cout << "password   : ";
        getline(cin,password);

        validUser = database.checkUserValidity(username,password,'p');
        if(validUser)
            home();
        else
        {
            cout<<"ERROR!"<<endl;
            cout<<"The username or password that you've entered doesn't match any account."<<endl;
            cin.ignore();
        }
        attempt++;
    }
    while(validUser!=1&&attempt<3);

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
        logIn();
    }
}

void Passenger::home()
{
    cout << "welcome to home" << endl;
    cin.ignore();
}
void Passenger::passengerHome()
{

}

Passenger::~Passenger()
{
}

