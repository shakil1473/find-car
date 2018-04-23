#include "../include/Driver.h"

Driver::Driver()
{
    //ctor
}

void Driver::logIn()
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
        cout << "username   : ";
        getline(cin,username);
        cout << "password   : ";
        getline(cin,password);

        validUser = database.checkUserValidity(username,password,'c');
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

void Driver::signUp()
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
            getline(cin,driverName);

            cout<<"Username : ";
            getline(cin,driverUsername);

            cout<<"Password : ";
            getline(cin,driverPassword);

            cout<<"Mobile No: ";
            getline(cin,mobile);
            insertSuccessful = database.insertIntoDataBase(driverName,driverUsername,driverPassword,mobile);

        }
        while(!insertSuccessful);
        if(insertSuccessful)
        {
            cout<<"log in to be choose your road and to be available by passengers"<<endl;

        }
        logIn();

    }

}
void Driver::home()
{
    Database database;
    int connected;
    connected=database.createConnection();
    cin.ignore();
}

Driver::~Driver()
{
    //dtor
}
