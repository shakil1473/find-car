#include "../include/Admin.h"
#include <iomanip>
Admin::Admin()
{
    //ctor
}

void Admin::logIn()
{

    cout<<"\t\t\t\t Admin Panel "<<endl;
    cout<<"\t\t\t\t-------------"<<endl;

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

    connected = database.createConnection();

    if(connected)
    {

        anyReview = anyUserReview();
        if(anyReview)
        {

            cout<<"Your have unread user's review...To read press 1 otherwise enter any digit : ";
            cin>>checkReview;
            if(checkReview==1)
                readUserReview();
        }
        else
        {
            cout<<"you don't have any unread review.Please press enter."<<endl;
            cin.ignore();
        }
        int option;
        do
        {
            cout<<"\t\t\t\t 1.Add New Route"<<endl;
            cout<<"\t\t\t\t 2.Edit Route "<<endl;
            cout<<"\t\t\t\t 3.Remove Route"<<endl;
            cout<<"\t\t\t\t 4.Show Route"<<endl;
            cout<<"\t\t\t\t 5.Log Out"<<endl;
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
                showRoad();
                cin.ignore();
                cin.ignore();
                break;

            }

        }
        while(option != 5);

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
    cout<<"User Reviews: "<<endl;

    Database database;
    database.createConnection();

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
                string insertQuery = "update review set seen = '"+upadeteSeen+"' where seen = '"+seen+"'";

                const char* query = insertQuery.c_str();

                cout<<"query is: "<<query<<endl;
                cin.ignore();

                int queryState=mysql_query(database.conn,query);
            }

        }
    }
    cin.ignore();
    cin.ignore();

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

        cout<<"query is: "<<query<<endl;
        cin.ignore();

        int queryState=mysql_query(database.conn,query);


        if(!queryState)
        {
            cout<<"Thanks for your valuable suggestions"<<endl;
            cin.ignore();
        }
    }

}

void Admin::addRoute()
{

    Database database;
    int connected;
    connected = database.createConnection();
    cout<<"Current Roads "<<endl;
    showRoad();
    if(connected)
    {
        cin.ignore();
        string carRoute;
        string carFair;
        cout<<"Enter route  : ";
        getline(cin,carRoute);
        cout<<"Car Fair     : ";
        getline(cin,carFair);
        database.insertIntoDataBase(carRoute,carFair);
    }


}
void Admin::editRoute()
{

    Database database;
    int connected;
    string editRouteNumber;
    string routeFair;
    string routeName;

    connected = database.createConnection();
    cout<<"Current Roads "<<endl;
    showRoad();
    if(connected)
    {
        cin.ignore();

        cout<<"Enter the road number to edit : ";
        getline(cin,editRouteNumber);
        cout<<"Enter new route name :";
        getline(cin,routeName);
        cout<<"Enter new route fair :";
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
                    string updateQuery = "update route set route = '"+routeName+"',fair ='"+routeFair+"' where route_id = '"+editRouteNumber+"'";

                    const char* update = updateQuery.c_str();


                    int queryState=mysql_query(database.conn,update);
                    if(!queryState)
                        cout<<"Data updated successfully"<<endl;
                }


            }
        }


    }
}
void Admin::removeRoute()
{

    Database database;
    int connected;
    string removeRouteNumber;
    connected = database.createConnection();
    cout<<"Current Roads "<<endl;
    showRoad();
    if(connected)
    {
        cin.ignore();
        cout<<"Enter the road number to remove : ";
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
                    cout<<delQuery<<endl;
                    int queryState=mysql_query(database.conn,delQuery);
                                   if(!queryState)
                    {
                        cout<<"Data deleted successfully"<<endl;
                    }

                }
            }
        }
    }


}
void Admin::showRoad()
{


    Database database;
    int connected;
    connected = database.createConnection();
    if(connected)
    {
        cout<<" Route No"<<"\t\t\t" <<"     Route     "<<"\t\t\t"<<" Fair "<<endl;
        cout<<"----------"<<"\t\t\t"<<"---------------"<<"\t\t\t"<<"------"<<endl;
        string insertQuery = "select * from route";

        const char* query = insertQuery.c_str();


        int queryState=mysql_query(database.conn,query);

        if(!queryState)
        {
            database.res = mysql_store_result(database.conn);
            while(database.row = mysql_fetch_row(database.res))
            {
                string route =database.row[1];//route name
                int length = route.length();//length of road name

                //setw() used to keep gap..takes argument gap num..
                cout<<"    "<<database.row[0]<<"  \t\t\t"<<database.row[1]<<setw(36-length)<<database.row[2]<<endl;

            }
        }
    }
}
Admin::~Admin()
{
    //dtor
}
