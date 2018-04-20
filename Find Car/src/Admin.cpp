#include "../include/Admin.h"
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
            cout<<"you don't have any unread review"<<endl;
            cin.ignore();
        }
        int option;
        do{
            cout<<"\t\t\t\t 1.Add New Route"<<endl;
        cout<<"\t\t\t\t 2.Edit Route "<<endl;
        cout<<"\t\t\t\t 3.Remove Route"<<endl;
        cout<<"\t\t\t\t 4.Log Out"<<endl;
        cin>>option;

        switch(option){
        case 1:
            addRoute();
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        }

        }while(option != 4);

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
    cin.ignore();
    Database database;
    int connected;
    connected = database.createConnection();
    if(connected)
    {
        string carRoute;
        string carFair;
        cout<<"Enter route  : ";
        getline(cin,carRoute);
        cout<<"Car Fair     : ";
        getline(cin,carFair);
        database.insertIntoDataBase(carRoute,carFair);
    }


}

Admin::~Admin()
{
    //dtor
}
