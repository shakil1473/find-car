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
        system("cls");
        cout<<endl;
        cout << "\t\t\t\t   Find Car" << endl;
        cout << "\t\t\t\t  ----------" << endl;
        cout<<endl<<endl;
        cout<<"\t\t\t\t     Log In " << endl;
        cout<<"\t\t\t\t    --------"<<endl<<endl;
        cout << "\t\t\t\tusername   :";
        getline(cin,username);
        cout << "\t\t\t\tpassword   : ";
        getline(cin,password);

        validUser = database.checkUserValidity(username,password,'p');
        if(validUser)
            home(username);
        else
        {
            cout<<endl;
            cout<<"\t\tERROR!"<<endl;
            cout<<"\t\tThe username or password that you've entered doesn't match any account."<<endl;
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
            system("cls");
            cout<<endl;
            cout << "\t\t\t\t   Find Car" << endl;
            cout << "\t\t\t\t  ----------" << endl;
            cout<<endl<<endl;
            cout<<"\t\t\t\t    Sign Up " << endl;
            cout<<"\t\t\t\t   ---------"<<endl<<endl;
            cout<<"\t\t\t\tName     : ";
            getline(cin,pasName);

            cout<<"\t\t\t\tUsername : ";
            getline(cin,pasUsername);

            cout<<"\t\t\t\tPassword : ";
            getline(cin,pasPassword);
            if(pasName.length()!=0&&pasUsername.length()&&pasPassword.length()!=0)
                insertSuccessful = database.insertIntoDataBase(pasName,pasUsername,pasPassword);
            else
            {
                cout<<"Please insert all the information"<<endl;
            }


        }
        while(!insertSuccessful);
        logIn();
    }
}

void Passenger::home(string userName)
{

    int option;
    Database dataBase;
    do
    {
        system("cls");
        cout<<endl;
        cout << "\t\t\t\t   Find Car" << endl;
        cout << "\t\t\t\t  ----------" << endl;
        cout<<""<<endl<<endl;
        cout<<"\t\t\t\t     Home " << endl;
        cout<<"\t\t\t\t    ------"<<endl<<endl;
        cout<<"\t\t\t\t1. Get Car"<<endl;
        cout<<"\t\t\t\t2. Change Password"<<endl;
        cout<<"\t\t\t\t3. Delete Account"<<endl;
        cout<<"\t\t\t\t4. Log Out"<<endl;
        cout<<"\t\t\t\tYou want to : ";
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
    system("cls");
    cout<<endl;
    cout << "\t\t\t\t   Find Car" << endl;
    cout << "\t\t\t\t  ----------" << endl;
    cout<<""<<endl<<endl;
    cout<<"\t\t\t\t     Get Car " << endl;
    cout<<"\t\t\t\t    ---------"<<endl<<endl;

    Database database;
    Admin admin;

    int connected;
    int availableCar = 0;
    string routeNo;
    string available="1";
    string driverUsername;
    string currentLocation;

    admin.showRoad();
    cout<<endl;
    cout<<"\t\t\t\tSelect Your Road : ";
    getline(cin,routeNo);

    system("cls");
    cout<<endl;
    cout << "\t\t\t\t   Find Car" << endl;
    cout << "\t\t\t\t  ----------" << endl;
    cout<<""<<endl<<endl;
    cout<<"\t\t\t\t     Get Car " << endl;
    cout<<"\t\t\t\t    ---------"<<endl<<endl;

    connected = database.createConnection();
    if(connected)
    {

        string getAllFromAvail = "select * from available_driver";

        const char* query = getAllFromAvail.c_str();


        int queryState=mysql_query(database.conn,query);

        if(!queryState)
        {

            database.res = mysql_store_result(database.conn);
            cout<<endl;
            cout<<"\t\t\t\tAvailable Cars : "<<endl;
            cout<<endl;
            cout<<"\t\t\t\t Driver Name "<<"   "<<" Mobile No "<<"   "<<" Current Location "<<endl;
            cout<<"\t\t\t\t-------------"<<"   "<<"-----------"<<"   "<<"------------------"<<endl;
            while(database.row = mysql_fetch_row(database.res))
            {

                if(database.row[1]==routeNo&&database.row[3]==available)
                {
                    driverUsername = database.row[0];
                    currentLocation = database.row[2];
                    showDriver(driverUsername,currentLocation);
                    availableCar++;
                }

            }
        }
    }
    if(!availableCar)
        cout<<"\t\t\t  No car available right now"<<endl;
    cin.ignore();
}
void Passenger::showDriver(string userName,string currentLocation)
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
                    cout<<"\t\t\t\t"<<database.row[0]<<"   "<<database.row[3]<<"   "<<currentLocation<<endl;
                }
            }
        }
    }
}

