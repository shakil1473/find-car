#include "../include/Database.h"


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
int Database::checkUserNameAvailability(string userName,char userType)
{

    int qstate;
    if(userType=='p'){
            qstate = mysql_query(conn,"select * from passenger");

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
    }
    else if(userType=='c'){
            qstate = mysql_query(conn,"select * from driver");

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
    }
    return 1;

}

int Database::checkUserValidity(string username,string password,char userType)
{

    int userAvailabe = 0;
    int qstate;
    if(userType == 'p')
    {

        qstate = mysql_query(conn,"select * from passenger");
        if(!qstate)
        {
            res = mysql_store_result(conn);
            while(row= mysql_fetch_row(res))
            {
                if(row[1]==username&&row[2]==password)
                {
                    userAvailabe = 1;
                    return userAvailabe;
                }
            }
        }
    }
    else if(userType == 'c'){
        cout<<"checking driver table"<<endl;
        qstate = mysql_query(conn,"select * from driver");
        if(!qstate){
            res = mysql_store_result(conn);
            while(row=mysql_fetch_row(res)){
                if(row[1]==username&&row[2]==password)
                {
                    userAvailabe = 1;
                    return userAvailabe;
                }
            }
        }
    }
    else
        return 0;
}

int Database::insertIntoDataBase(string pickUpOne,string pickUpTwo,string fair,char route)
{

    dPickUpOne = pickUpOne;
    dPickUpTwo = pickUpTwo;
    dFair = fair;

    insertQuery = "insert into route(pickup_one,pickup_two,fair) value('"+dPickUpOne+"','"+dPickUpTwo+"','"+dFair+"')";
    query = insertQuery.c_str();

    queryState=mysql_query(conn,query);

    if(!queryState)
    {
        cout<<"Route added successfully.."<<endl;
        cin.ignore();
        return 1;
    }

    else
        return 0;


}

int Database::insertIntoDataBase(string name,string username,string password)
{

    int usernaemAvailable;

    dName=name;
    dUsername=username;
    dPassword = password;

    usernaemAvailable = checkUserNameAvailability(username,'p');

    if(!usernaemAvailable)
    {
        cout<<"username is not available"<<endl;
        return 0;
    }
    else
    {
        insertQuery = "insert into passenger values('"+dName+"','"+dUsername+"','"+dPassword+"')";
        query = insertQuery.c_str();


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

int Database::insertIntoDataBase(string driverName,string driverUsername,string driverPassword,string mobile){

    int usernaemAvailable;

    dName=driverName;
    dUsername=driverUsername;
    dPassword = driverPassword;
    dMobile = mobile;

    usernaemAvailable = checkUserNameAvailability(driverUsername,'c');

    if(!usernaemAvailable)
    {
        cout<<"username is not available"<<endl;
        return 0;
    }
    else
    {
        insertQuery = "insert into driver values('"+dName+"','"+dUsername+"','"+dPassword+"','"+dMobile+"')";
        query = insertQuery.c_str();


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
