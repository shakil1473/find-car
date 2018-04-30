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
            home(username);
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

void Passenger::home(string userName)
{
    cout << "welcome to home" << endl;
    int option;
    Database dataBase;
    do
    {
        cout<<"\t\t\t\t1. Find Car"<<endl;
        cout<<"\t\t\t\t2. Change Password"<<endl;
        cout<<"\t\t\t\t3. Delete Account"<<endl;
        cout<<"\t\t\t\t4. Log Out"<<endl;
        cin>>option;
        cin.ignore();
        switch(option)
        {
        case 1:
            findCar();
            break;
        case 2:
            dataBase.passengerInfoChange(userName);
            break;
        case 3:
            dataBase.deleteUser(userName,'p');
            break;
        }

        if(option>4)
            cout<<"Enter option correctly"<<endl;
    }
    while(option!=3&&option!=4);

}
void Passenger::findCar()
{
    Database database;
    Admin admin;

    int connected;
    string routeNo;
    string available="1";
    string driverUsername;

    admin.showRoad();

    cout<<"Select Your Road : ";
    getline(cin,routeNo);

    connected = database.createConnection();
    if(connected)
    {

        string getAllFromAvail = "select * from available_driver";

        const char* query = getAllFromAvail.c_str();


        int queryState=mysql_query(database.conn,query);

        if(!queryState)
        {

            database.res = mysql_store_result(database.conn);
            cout<<"Available Cars : "<<endl;
            cout<<"Driver Name"<<" "<<"Mobile No"<<endl;
            while(database.row = mysql_fetch_row(database.res))
            {

                if(database.row[1]==routeNo&&database.row[3]==available)
                {
                    //cout<<"inside while"<<database.row[1]<<" "<<routeNo<<" "<<database.row[3]<<endl;
                    //
                    driverUsername = database.row[0];
                    showDriver(driverUsername);
                }

            }
        }
    }
}
void Passenger::showDriver(string userName)
{
    Database database;

    int connected;

    connected = database.createConnection();
    if(connected)
    {

        string getAllFromDriver = "select * from driver";

        const char* query = getAllFromDriver.c_str();


        int queryState=mysql_query(database.conn,query);

        if(!queryState)
        {
            database.res = mysql_store_result(database.conn);
            while(database.row = mysql_fetch_row(database.res))
            {
                if(database.row[1]==userName)
                {
                    cout<<database.row[0]<<" "<<database.row[3]<<endl;
                }
            }
        }
    }
}

