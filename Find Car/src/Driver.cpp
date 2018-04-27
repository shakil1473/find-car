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
        cout << "username   : ";
        getline(cin,username);
        cout << "password   : ";
        getline(cin,password);

        validUser = database.checkUserValidity(username,password,'c');
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
            cout<<"Name     : ";
            getline(cin,driverName);

            cout<<"Username : ";
            getline(cin,driverUsername);

            cout<<"Password : ";
            getline(cin,driverPassword);

            cout<<"Mobile No: ";
            getline(cin,mobile);
            insertSuccessfulD = database.insertIntoDataBase(driverName,driverUsername,driverPassword,mobile);
            cout<<"Please press enter again"<<endl;


        }
        while(!insertSuccessfulD);
        do
        {


            string road;
            string currentLocation;
            int available = 0;

            cout<<"Select your road "<<endl;
            showRoads();
            getline(cin,road);

            cout<<"Your Current Location : ";
            getline(cin,currentLocation);

            insertSuccessfulA = database.insertIntoDataBase(driverUsername,road,currentLocation,available);

            if(insertSuccessfulA)
            {

                cout<<"From now passengers will find you in the apps"<<endl;
                cout<<"To be unavailable, lonIn your account and follow instructions."<<endl;
                cout<<"Thanks for joining us"<<endl;
                cin.ignore();
                logIn();
            }
        }
        while(!insertSuccessfulD);

    }
}
void Driver::home(string userName)
{
    cout<<"\t\t\t\t\tuser : "<<userName<<endl<<endl<<endl;
    cout<<"\t\t\t\t\tHOME"<<endl<<endl;
    int option;
    do
    {
        cout<<"1.Change Route"<<endl;
        cout<<"2.Change Password"<<endl;
        cout<<"3.Change Mobile No"<<endl;
        cout<<"4.Change Current Location"<<endl;
        cout<<"5.Change Available Status"<<endl;
        cout<<"6.Delete Account"<<endl;
        cout<<"7.Exit"<<endl;
        cout<<"Choose your option : ";
        cin>>option;
        cin.ignore();
        if(option!=7 && option!=6){
            changeInfo(userName,option);
        }
        else if(option==6){
            Database database;
            database.deleteUser('d');
            break;
        }
        else if(option==7){
            break;
        }
        else if(option<0 || option > 7){
            cout<<"Enter option correctly"<<endl;
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
                cout<<"   "<<database.row[0]<<"    "<<setw(13)<<database.row[1]<<setw(25-lengthOne)<<database.row[2]<<setw(29-lengthTwo)<<database.row[3]<<endl;

            }
        }
    }
}

void Driver::changeInfo(string username,int option){
    if(option==1){
            showRoads();
        cout<<"Enter New Route  : ";
            getline(cin,changedInfo);
    }
    else if(option==2){
        cout<<"Enter New Password  : ";
            getline(cin,changedInfo);
    }
    else if(option==3){
        cout<<"Enter New Mobile No  : ";
            getline(cin,changedInfo);
    }

    else if(option==4){
        cout<<"Enter Current Location   : ";
            getline(cin,changedInfo);
    }
    else if(option==5){
        cout<<"Change Available status(available - 1, unavailable - 0)  : ";
            getline(cin,changedInfo);
    }

    Database dataBase;
    dataBase.driverInfoChange(username,changedInfo,option);

}
Driver::~Driver()
{
    //dtor
}
