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
    if(userType=='p')
    {
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
    else if(userType=='c')
    {
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
    else if(userType == 'c')
    {
        qstate = mysql_query(conn,"select * from driver");
        if(!qstate)
        {
            res = mysql_store_result(conn);
            while(row=mysql_fetch_row(res))
            {
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

void Database::passengerInfoChange(string userName)
{
    system("cls");
    cout<<endl;
    cout << "\t\t\t\t    Find Car" << endl;
    cout << "\t\t\t\t   ----------" << endl;
    cout<<endl<<endl;
    cout<<"\t\t\t\t     Settings " << endl;
    cout<<"\t\t\t\t    ----------"<<endl<<endl;

    int connected;
    string newPassword;
    string updateQuery;
    connected = createConnection();
    if(connected)
    {
        cout<<"\t\t\t\tEnter New Password : ";
        getline(cin,newPassword);

        string getAllDataQuery= "select * from passenger";


        const char* query = getAllDataQuery.c_str();

        int queryState=mysql_query(conn,query);

        if(!queryState)
        {
            int queryStateUpdate;
            res = mysql_store_result(conn);
            while(row = mysql_fetch_row(res))
            {
                updateQuery = "update passenger set pas_password = '"+newPassword+"' where pas_username = '"+userName+"'";
                const char* update = updateQuery.c_str();

                queryStateUpdate=mysql_query(conn,update);

            }
            if(!queryStateUpdate)
                cout<<"\t\t\t\tData updated successfully"<<endl;
            cin.ignore();
        }
    }
}

int Database::driverInfoChange(string username,string changedInfo,int option)
{

    int connected;
    connected = createConnection();
    string changedInfoName;
    if(option==1)
    {
        changedInfoName = "road";
    }
    else if(option==2)
    {
        changedInfoName="password";
    }
    else if(option==3)
    {
        changedInfoName="mobile";
    }
    else if(option == 4)
    {
        changedInfoName = "current_location";
    }
    else if(option == 5)
    {
        changedInfoName = "available";
    }

    if(connected)
    {
        string getAllDataQuery;
        if(option == 2||option==3)
        {
            getAllDataQuery= "select * from driver";
        }

        else
        {
            getAllDataQuery = "select * from available_driver";
        }


        const char* query = getAllDataQuery.c_str();


        int queryState=mysql_query(conn,query);

        if(!queryState)
        {
            res = mysql_store_result(conn);
            while(row = mysql_fetch_row(res))
            {
                string updateQuery;
                if(option==2||option==3)
                {
                    string updateRowName;
                    if(option==2)
                        updateRowName = "password";
                    else if(option==3)
                        updateRowName = "mobile";
                    if(row[1]==username)
                    {

                        updateQuery = "update driver set "+ updateRowName+ " = '"+changedInfo+"' where username = '"+username+"'";

                        const char* update = updateQuery.c_str();


                        int queryState=mysql_query(conn,update);
                        if(!queryState)
                            cout<<"\t\t\t\tData updated successfully"<<endl;
                    }

                }
                else
                {
                    if(row[0]==username)
                    {
                        updateQuery = "update available_driver set "+changedInfoName+" = '"+changedInfo
                                      +"' where driver_id = '"+username+"'";

                        const char* update = updateQuery.c_str();

                        int queryState=mysql_query(conn,update);
                        if(!queryState)
                            cout<<"\t\t\t\tData updated successfully"<<endl;
                    }
                }

            }
        }
    }
}

int Database::insertIntoDataBase(string pName,string pUsername,string pPassword)
{

    int usernaemAvailable;

    dName=pName;
    dUsername=pUsername;
    dPassword = pPassword;

    usernaemAvailable = checkUserNameAvailability(pUsername,'p');

    if(!usernaemAvailable)
    {
        cout<<endl;
        cout<<"\t\t\t  username is not available"<<endl;
        cin.ignore();
        return 0;
    }
    else
    {
        insertQuery = "insert into passenger values('"+dName+"','"+dUsername+"','"+dPassword+"')";
        query = insertQuery.c_str();


        queryState=mysql_query(conn,query);


        if(!queryState)
        {
            cout<<endl;
            cout<<"\t\t\t\taccount created successfully.."<<endl;
            cin.ignore();
            return 1;
        }

        else
            return 0;
    }

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
        cout<<endl;
        cout<<"\t\t\t\tRoute added successfully.."<<endl;
        cin.ignore();
        return 1;
    }

    else
        return 0;


}


int Database::insertIntoDataBase(string username,string road,string currentLocation,int available)
{

    string currentlyAvailable = "1";

    insertQuery = "insert into  available_driver values('"+username+"','"+road+"','"+currentLocation+"','"+currentlyAvailable+"')";
    query = insertQuery.c_str();


    queryState=mysql_query(conn,query);


    if(!queryState)
    {
        cout<<"\t\t\t\tYour account has been created successfully."<<endl;
        cin.ignore();
        return 1;
    }
    else
        return 0;
}

int Database::insertIntoDataBase(string driverName,string driverUsername,string driverPassword,string mobile)
{

    int usernaemAvailable;

    dName=driverName;
    dUsername=driverUsername;
    dPassword = driverPassword;
    dMobile = mobile;

    usernaemAvailable = checkUserNameAvailability(driverUsername,'c');

    if(!usernaemAvailable)
    {
        cout<<endl;
        cout<<"\t\t\t\tusername is not available"<<endl;
        cin.ignore();
        return 0;
    }
    else
    {
        insertQuery = "insert into driver values('"+dName+"','"+dUsername+"','"+dPassword+"','"+dMobile+"')";
        query = insertQuery.c_str();


        queryState=mysql_query(conn,query);


        if(!queryState)
        {
            return 1;
        }

        else
            return 0;
    }

}

void Database::deleteUser(string username,char userType)
{
    int connected;
    int queryState;
    int delQueryState;
    int delQueryDriverAvail;
    string deleteQuery;
    string getAllQuery;
    string deleteQureyFromAvailableDriver;

    connected= createConnection();
    if(connected)
    {
        const char* query;
        const char* delQuery;
        const char* deleteQueryDriverAvail;
        if(userType=='d')
        {
            getAllQuery = "select * from driver";
            query = getAllQuery.c_str();
            queryState = mysql_query(conn,query);
            if(!queryState)
            {
                res=mysql_store_result(conn);
                while(row=mysql_fetch_row(res))
                {
                    deleteQuery = "delete from driver where username = '"+username+"'";
                    delQuery = deleteQuery.c_str();


                    deleteQureyFromAvailableDriver= "delete from available_driver where  driver_id  ='"+username+"'";
                    deleteQueryDriverAvail = deleteQureyFromAvailableDriver.c_str();


                    delQueryState = mysql_query(conn,delQuery);
                    delQueryDriverAvail = mysql_query(conn,deleteQueryDriverAvail);

                }
                if(!delQueryState&&!delQueryDriverAvail)
                    cout<<"\t\t\t\tAccount Deleted"<<endl;
            }
        }
        else if(userType=='p')
        {
            getAllQuery = "select * from passenger";
            query = getAllQuery.c_str();
            queryState=mysql_query(conn,query);
            if(!queryState)
            {
                res = mysql_store_result(conn);
                while(row=mysql_fetch_row(res))
                {
                    deleteQuery = "delete from passenger where  pas_username ='"+username+"'";
                    delQuery = deleteQuery.c_str();
                    delQueryState = mysql_query(conn,delQuery);


                }
                if(!delQueryState)
                    cout<<"\t\t\t\tAccount Deleted"<<endl;

            }
        }
        cin.ignore();
    }



}

Database::~Database()
{
    //dtor
}
