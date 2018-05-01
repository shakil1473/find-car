#include "../include/Admin.h"
#include <iomanip>
Admin::Admin()
{
    //ctor
}

void Admin::logIn()
{
    system("cls");
    cout<<endl;
    cout << "\t\t\t\t   Find Car" << endl;
    cout << "\t\t\t\t  ----------" << endl;
    cout<<""<<endl<<endl;
    cout<<"\t\t\t\t     Admin " << endl;
    cout<<"\t\t\t\t    -------"<<endl<<endl;

    cout<<"\t\t\t\tusername: ";
    getline(cin,adminUserName);

    cout<<"\t\t\t\tpassword: ";
    getline(cin,adminPassword);

    if(adminUserName=="shakil"&&adminPassword=="1473")
        home();
    else
    {
        cout<<"username or password is incorrect."<<endl;
        logIn();
    }
}
void Admin::home()
{

    Database database;
    int connected;
    int anyReview;
    int checkReview;
    system("cls");
    cout<<endl;
    cout << "\t\t\t\t   Find Car" << endl;
    cout << "\t\t\t\t  ----------" << endl;
    cout<<""<<endl<<endl;
    cout<<"\t\t\t\t     Admin " << endl;
    cout<<"\t\t\t\t    -------"<<endl<<endl;

    connected = database.createConnection();

    if(connected)
    {



        int option;
        do
        {
            system("cls");
            cout<<endl;
            cout << "\t\t\t\t   Find Car" << endl;
            cout << "\t\t\t\t  ----------" << endl;
            cout<<""<<endl<<endl;
            cout<<"\t\t\t\t     Admin's Home " << endl;
            cout<<"\t\t\t\t    --------------"<<endl<<endl;
            anyReview = anyUserReview();
        if(anyReview)
        {

            cout<<"\t\t\t\t**Unread Notifications**"<<endl<<endl;

        }
            cout<<"\t\t\t\t 1.Add New Route"<<endl;
            cout<<"\t\t\t\t 2.Edit Route "<<endl;
            cout<<"\t\t\t\t 3.Remove Route"<<endl;
            cout<<"\t\t\t\t 4.Show Route"<<endl;
            cout<<"\t\t\t\t 5.Show Users"<<endl;
            cout<<"\t\t\t\t 6.Notifications"<<endl;
            cout<<"\t\t\t\t 7.Log Out"<<endl;
            cout<<endl;
            cout<<"\t\t\t\t Choose Option : ";
            cin>>option;

            switch(option)
            {
            case 1:
                addRoute();
                break;
            case 2:
                editRoute();
                break;
            case 3:
                removeRoute();
                break;
            case 4:
                system("cls");
                cout<<endl;
                cout << "\t\t\t\t   Find Car" << endl;
                cout << "\t\t\t\t  ----------" << endl;
                cout<<""<<endl<<endl;
                cout<<"\t\t\t\t     Admin Panel " << endl;
                cout<<"\t\t\t\t    -------------"<<endl<<endl;
                cout<<""<<endl<<endl;
                cout<<"\t\t\t\t     ADD ROUTE " << endl;
                cout<<"\t\t\t\t    -----------"<<endl<<endl;
                showRoad();
                cin.ignore();
                cin.ignore();
                break;
            case 5:
                allUsers();
                break;
            case 6:
                cin.ignore();
                readUserReview();
                break;


            }

        }
        while(option != 7);

    }

}
int Admin::anyUserReview()
{

    Database database;
    database.createConnection();
    int qstate = mysql_query(database.conn,"select * from review");
    string seen = "0";
    if(!qstate)
    {
        database.res = mysql_store_result(database.conn);
        while(database.row = mysql_fetch_row(database.res))
        {

            if(database.row[1]==seen)
            {
                return 1;
            }

        }
    }
    return 0;
}
void Admin::readUserReview()
{
    system("cls");
    cout<<endl;
    cout << "\t\t\t\t   Find Car" << endl;
    cout << "\t\t\t\t  ----------" << endl;
    cout<<""<<endl<<endl;
    cout<<"\t\t\t\t     Admin " << endl;
    cout<<"\t\t\t\t    -------"<<endl<<endl;
    cout<<"\t\t\t\t User Reviews "<<endl;
    cout<<"\t\t\t\t--------------"<<endl<<endl;

    Database database;
    database.createConnection();

    int countReview = 0;

    int qstate = mysql_query(database.conn,"select * from review");

    string seen = "0";
    string upadeteSeen = "1";
    if(!qstate)
    {
        database.res = mysql_store_result(database.conn);
        while(database.row = mysql_fetch_row(database.res))
        {

            if(database.row[1]==seen)
            {
                cout<<database.row[0]<<endl;
                cin.ignore();
                string insertQuery = "update review set seen = '"+upadeteSeen+"' where seen = '"+seen+"'";
                string deleteQuery = "Delete from review where seen = '"+upadeteSeen+"'";

                const char* query = insertQuery.c_str();
                const char* queryDel = deleteQuery.c_str();

                int queryState=mysql_query(database.conn,query);
                queryState = mysql_query(database.conn,queryDel);
                countReview++;
            }

        }
    }
    if(!countReview)
        {
            cout<<"No New Notifications.."<<endl;
            cin.ignore();
        }


}


void Admin::writeUserReview(string suggestoions)
{
    review = suggestoions;
    seen = '0';
    Database database;
    int connected;
    connected = database.createConnection();


    if(connected)
    {
        string insertQuery = "insert into review values('"+review+"','"+seen+"')";

        const char* query = insertQuery.c_str();


        int queryState=mysql_query(database.conn,query);


        if(!queryState)
        {
            cout<<"Thanks for your valuable suggestions"<<endl;

        }
    }
    cin.ignore();


}

void Admin::addRoute()
{
    system("cls");
    cout<<endl;
    cout << "\t\t\t\t   Find Car" << endl;
    cout << "\t\t\t\t  ----------" << endl;
    cout<<""<<endl<<endl;
    cout<<"\t\t\t\t     Admin Panel " << endl;
    cout<<"\t\t\t\t    -------------"<<endl<<endl;
    cout<<""<<endl<<endl;
    cout<<"\t\t\t\t     ADD ROUTE " << endl;
    cout<<"\t\t\t\t    -----------"<<endl<<endl;

    Database database;
    int connected;
    connected = database.createConnection();
    cout<<"\t\t\t\t Current Roads "<<endl;
    cout<<"\t\t\t\t--------------"<<endl<<endl;
    showRoad();
    cout<<endl<<endl;
    if(connected)
    {

        cin.ignore();
        string pickUpOne;
        string pickUpTwo;
        string carFair;
        cout<<"\t\t\t\tEnter pick up point One  : ";
        getline(cin,pickUpOne);
        cout<<"\t\t\t\tEnter pick up point Two  : ";
        getline(cin,pickUpTwo);
        cout<<"\t\t\t\tCar Fair                 : ";
        getline(cin,carFair);
        database.insertIntoDataBase(pickUpOne,pickUpTwo,carFair,'r');
    }


}
void Admin::editRoute()
{
    system("cls");
    cout<<endl;
    cout << "\t\t\t\t   Find Car" << endl;
    cout << "\t\t\t\t  ----------" << endl;
    cout<<""<<endl<<endl;
    cout<<"\t\t\t\t     Admin Panel " << endl;
    cout<<"\t\t\t\t    -------------"<<endl<<endl;
    cout<<""<<endl<<endl;
    cout<<"\t\t\t\t     Edit Route " << endl;
    cout<<"\t\t\t\t    ------------"<<endl<<endl;

    Database database;
    int connected;
    string editRouteNumber;
    string routeFair;
    string pickUpOne;
    string pickUpTwo;

    connected = database.createConnection();
    cout<<"\t\t\t\t Current Roads "<<endl;
    cout<<"\t\t\t\t--------------"<<endl<<endl;
    showRoad();
    cout<<endl<<endl;
    if(connected)
    {
        cin.ignore();

        cout<<"\t\t\t\tEnter the road number to edit : ";
        getline(cin,editRouteNumber);
        cout<<"\t\t\t\tEnter new pick up one :";
        getline(cin,pickUpOne);
        cout<<"\t\t\t\tEnter new pick up two :";
        getline(cin,pickUpTwo);
        cout<<"\t\t\t\tEnter new route fair :";
        getline(cin,routeFair);

        string getAllDataQuery = "select * from route";

        const char* query = getAllDataQuery.c_str();


        int queryState=mysql_query(database.conn,query);

        if(!queryState)
        {
            database.res = mysql_store_result(database.conn);
            while(database.row = mysql_fetch_row(database.res))
            {

                if(database.row[0]==editRouteNumber)
                {
                    string updateQuery = "update route set pickup_one = '"+pickUpOne+"',pickup_two = '"+pickUpTwo+"',fair ='"+routeFair+"' where route_id = '"+editRouteNumber+"'";

                    const char* update = updateQuery.c_str();


                    int queryState=mysql_query(database.conn,update);
                    if(!queryState)
                        cout<<endl;
                    cout<<"\t\t\t\tData updated successfully"<<endl;
                }

            }
        }


    }
    cin.ignore();
}
void Admin::removeRoute()
{

    system("cls");
    cout<<endl;
    cout << "\t\t\t\t   Find Car" << endl;
    cout << "\t\t\t\t  ----------" << endl;
    cout<<""<<endl<<endl;
    cout<<"\t\t\t\t     Admin Panel " << endl;
    cout<<"\t\t\t\t    -------------"<<endl<<endl;
    cout<<""<<endl<<endl;
    cout<<"\t\t\t\t     Remove Route " << endl;
    cout<<"\t\t\t\t    --------------"<<endl<<endl;
    Database database;
    int connected;
    string removeRouteNumber;
    connected = database.createConnection();
    cout<<"\t\t\t\t Current Roads "<<endl;
    cout<<"\t\t\t\t--------------"<<endl<<endl;
    showRoad();
    cout<<endl<<endl;
    if(connected)
    {
        cin.ignore();
        cout<<"\t\t\t\tEnter the road number to remove : ";
        getline(cin,removeRouteNumber);

        string getALLDataQuery = "select * from route";

        const char* query = getALLDataQuery.c_str();

        int queryState = mysql_query(database.conn,query);

        if(!queryState)
        {
            database.res = mysql_store_result(database.conn);
            while(database.row = mysql_fetch_row(database.res))
            {


                int queryState = mysql_query(database.conn,query);
                database.createConnection();
                if(database.row[0]==removeRouteNumber)
                {
                    string deleteQuery = "delete from route where route_id = " +removeRouteNumber+";" ;
                    const char* delQuery = deleteQuery.c_str();
                    int queryState=mysql_query(database.conn,delQuery);
                    if(!queryState)
                    {
                        cout<<"\t\t\t\tData deleted successfully"<<endl;
                    }

                }
            }
        }
    }
    cin.ignore();


}
void Admin::showRoad()
{


    Database database;
    int connected;
    connected = database.createConnection();
    if(connected)
    {
        cout<<" Route No "<<setw(20) <<"  From/Destination  "<<setw(20)<<"  Destination/From  "<<setw(20)<<" Fair "<<endl;
        cout<<"----------"<<setw(20) <<"--------------------"<<setw(20)<<"--------------------"<<setw(20)<<"------"<<endl;
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
void Admin::allUsers()
{

    system("cls");
    cout<<endl;
    cout << "\t\t\t\t   Find Car" << endl;
    cout << "\t\t\t\t  ----------" << endl;
    cout<<""<<endl<<endl;
    cout<<"\t\t\t\t     Admin Panel " << endl;
    cout<<"\t\t\t\t    -------------"<<endl<<endl;
    cout<<""<<endl<<endl;
    cout<<"\t\t\t\t     All Users " << endl;
    cout<<"\t\t\t\t    -----------"<<endl<<endl;

    Database database;

    int connected;

    connected = database.createConnection();
    if(connected)
    {

        string getAll = "select * from driver";

        const char* query = getAll.c_str();


        int queryState=mysql_query(database.conn,query);

        if(!queryState)
        {
            cout<<"\t\t\t\t Drivers :"<<endl;
            cout<<"\t\t\t\t----------"<<endl;
            cout<<" Driver's Name "<<endl;
            cout<<"---------------"<<endl;
            database.res = mysql_store_result(database.conn);
            while(database.row = mysql_fetch_row(database.res))
            {
                cout<<database.row[0]<<endl;
            }
        }
        getAll = "select * from passenger";

        query = getAll.c_str();


        queryState=mysql_query(database.conn,query);

        if(!queryState)
        {
            cout<<"\t\t\t\t Passengers :"<<endl;
            cout<<"\t\t\t\t-------------"<<endl;
            cout<<" Passenger's Name "<<endl;
            cout<<"------------------"<<endl;
            database.res = mysql_store_result(database.conn);
            while(database.row = mysql_fetch_row(database.res))
            {
                cout<<database.row[0]<<endl;
            }
        }
    }
    cin.ignore();
    cin.ignore();
}
Admin::~Admin()
{
    //dtor
}
