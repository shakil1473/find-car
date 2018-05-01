#include "../include/Driver.h"
#include <iomanip>

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

    cout<<"Log In"<<endl;
    cout<<endl;


    do
    {
        system("cls");
            cout<<endl;
            cout << "\t\t\t\t   Find Car" << endl;
            cout << "\t\t\t\t  ----------" << endl;
            cout<<endl<<endl;
            cout<<"\t\t\t\t    Log In " << endl;
            cout<<"\t\t\t\t   --------"<<endl<<endl;
        cout << "\t\t\t\tusername   : ";
        getline(cin,username);
        cout << "\t\t\t\tpassword   : ";
        getline(cin,password);

        validUser = database.checkUserValidity(username,password,'c');
        if(validUser)
            home(username);
        else
        {
            cout<<endl;
            cout<<"\t\t\t   ERROR!"<<endl;
            cout<<"\t\t\t   The username or password that you've entered doesn't match any account."<<endl;
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
    int insertSuccessfulD = 0;
    int insertSuccessfulA = 0;

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
            getline(cin,driverName);

            cout<<"\t\t\t\tUsername : ";
            getline(cin,driverUsername);

            cout<<"\t\t\t\tPassword : ";
            getline(cin,driverPassword);

            cout<<"\t\t\t\tMobile No: ";
            getline(cin,mobile);
            if(driverName.length()!=0&&driverUsername.length()!=0&&driverPassword.length()!=0&&mobile.length()!=0)
            {
                insertSuccessfulD = database.insertIntoDataBase(driverName,driverUsername,driverPassword,mobile);
                cout<<endl;
            }
            else
                cout<<"\t\t\t   Please insert all the informations."<<endl;



        }
        while(!insertSuccessfulD);
        do
        {


            string road;
            string currentLocation;
            int available = 0;
            cout<<endl;
            cout<<"\t\t\t\t Select your road "<<endl;
            cout<<"\t\t\t\t------------------"<<endl<<endl;
            showRoads();
            cout<<endl;
            cout<<"\t\t\t\tRoad Number : ";
            getline(cin,road);

            cout<<"\t\t\t\tYour Current Location : ";
            getline(cin,currentLocation);

            insertSuccessfulA = database.insertIntoDataBase(driverUsername,road,currentLocation,available);

            if(insertSuccessfulA)
            {

                cout<<"\t\t\t  From now passengers will find you in the apps"<<endl;

                cout<<"\t\t\t  To be unavailable, lonIn your account and follow instructions."<<endl;

                cout<<"\t\t\t  Thanks for joining us"<<endl;

                cin.ignore();
                logIn();
            }
        }
        while(!insertSuccessfulD);

    }
}
void Driver::home(string userName)
{

    int option;
    do
    {
        system("cls");
        cout<<endl;
        cout << "\t\t\t\t   Find Car" << endl;
        cout << "\t\t\t\t  ----------" << endl;
        cout<<endl<<endl;
        cout<<"\t\t\t\t    Home " << endl;
        cout<<"\t\t\t\t   ------"<<endl<<endl;

        cout<<"\t\t\t\t\tuser : "<<userName<<endl<<endl<<endl;

        cout<<"\t\t\t\t 1.Change Route"<<endl;
        cout<<"\t\t\t\t 2.Change Password"<<endl;
        cout<<"\t\t\t\t 3.Change Mobile No"<<endl;
        cout<<"\t\t\t\t 4.Change Current Location"<<endl;
        cout<<"\t\t\t\t 5.Change Available Status"<<endl;
        cout<<"\t\t\t\t 6.Delete Account"<<endl;
        cout<<"\t\t\t\t 7.Log Out"<<endl;
        cout<<endl;
        cout<<"\t\t\t\tChoose your option : ";
        cin>>option;
        cin.ignore();
        if(option!=7 && option!=6)
        {
            changeInfo(userName,option);
        }
        else if(option==6)
        {
            Database database;
            database.deleteUser(userName,'d');
            break;
        }
        else if(option==7)
        {
            break;
        }
        else if(option<0 || option > 7)
        {
            cout<<endl;
            cout<<"\t\t\t  Enter option correctly"<<endl;
        }

    }
    while(option<7 && option>0);


}
void Driver::showRoads()
{
    Database database;
    int connected;
    connected = database.createConnection();
    if(connected)
    {
        cout<<" Route No "<<setw(20) <<"  Pick Up One  "<<setw(20)<<"  Pick Up Two  "<<setw(20)<<" Fair "<<endl;
        cout<<"----------"<<setw(20) <<"---------------"<<setw(20)<<"---------------"<<setw(20)<<"------"<<endl;
        string insertQuery = "select * from route";

        const char* query = insertQuery.c_str();


        int queryState=mysql_query(database.conn,query);

        if(!queryState)
        {
            database.res = mysql_store_result(database.conn);
            while(database.row = mysql_fetch_row(database.res))
            {
                string pickUpOne =database.row[1];//pick up 1 name
                string pickUpTwo = database.row[2];//pick up 2 name
                int lengthOne = pickUpOne.length();//length of pick up one
                int lengthTwo = pickUpTwo.length();

                //setw() used to keep gap..takes argument gap num..
                cout<<"   "<<database.row[0]<<"    "<<setw(13)<<database.row[1]<<setw(25-lengthOne)
                    <<database.row[2]<<setw(29-lengthTwo)<<database.row[3]<<endl;

            }
        }
    }
}

void Driver::changeInfo(string username,int option)
{
    system("cls");
            cout<<endl;
            cout << "\t\t\t\t   Find Car" << endl;
            cout << "\t\t\t\t  ----------" << endl;
            cout<<endl<<endl;
            cout<<"\t\t\t\t    Settings "<< endl;
            cout<<"\t\t\t\t   ----------"<<endl<<endl;

    if(option==1)
    {
        showRoads();
        cout<<endl;
        cout<<"\t\t\t\tEnter New Route  : ";
        getline(cin,changedInfo);
    }
    else if(option==2)
    {
        cout<<"\t\t\t\tEnter New Password  : ";
        getline(cin,changedInfo);
    }
    else if(option==3)
    {
        cout<<"\t\t\t\tEnter New Mobile No  : ";
        getline(cin,changedInfo);
    }

    else if(option==4)
    {
        cout<<"\t\t\t\tEnter Current Location   : ";
        getline(cin,changedInfo);
    }
    else if(option==5)
    {
        cout<<"\t\t\t\tChange Available status(available - 1, unavailable - 0)  : ";
        getline(cin,changedInfo);
    }

    Database dataBase;
    dataBase.driverInfoChange(username,changedInfo,option);
    cin.ignore();

}
Driver::~Driver()
{
    //dtor
}
