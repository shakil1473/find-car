#include "Database.h"


Database::Database()
{
    //ctor
}
int Database::createConnection()
{


    conn = mysql_init(0);

    conn = mysql_real_connect(conn,"localhost","root","1473","find_car",0,NULL,0);

    if(conn)
        return 1;

    else
        return 0;
}
int Database::checkAvailability(string userName)
{

    int qstate = mysql_query(conn,"select * from passenger");

    if(!qstate)
    {
        res = mysql_store_result(conn);
        while(row = mysql_fetch_row(res))
        {
            if(row[1]==userName)
            {
                return 0;
            }

        }
    }
    return 1;

}

int Database::insertIntoDataBase(string name,string username,string password)
{

    int usernaemAvailable;
    int queryState;

    string insertQuery;


    const char* query;

    pasName=name;
    pasUsername=username;
    pasPassword = password;

    usernaemAvailable = checkAvailability(username);

    if(!usernaemAvailable)
    {
        cout<<"username is not available"<<endl;
        return 0;
    }
    else
    {
        insertQuery = "insert into passenger values('"+pasName+"','"+pasUsername+"','"+pasPassword+"')";
        query = insertQuery.c_str();

        cout<<"query is: "<<query<<endl;
        cin.ignore();

        queryState=mysql_query(conn,query);


        if(!queryState)
        {
            cout<<"account created successfully.."<<endl;
            cin.ignore();
            return 1;
        }

        else
            return 0;
    }

}

Database::~Database()
{
    //dtor
}
