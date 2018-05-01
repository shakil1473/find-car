#include <iostream>
#include <windows.h>
#include <mysql.h>
#include "include/Admin.h"
#include "include/Driver.h"
#include "include/Database.h"
#include "include/Passenger.h"


using namespace std;


void whoAmI(int optionChosen)
{

    int whoAmI;

    Admin admin;
    Driver driver;
    Passenger passenger;

    do
    {
        system("cls");
        cout<<endl;
        cout << "\t\t\t\t   Find Car" << endl;
        cout << "\t\t\t\t  ----------" << endl;
        cout<<endl<<endl;

        if(optionChosen ==1)
        {

            cout<<"\t\t\t\t 1.PASSENGER"<<endl;
            cout<<"\t\t\t\t 2.DRIVER"<<endl;
            cout<<"\t\t\t\t 3.ADMIN"<<endl;
            cout<<endl;
            cout<<"\t\t\t\t Your are [to go home press 4] : ";

            cin>>whoAmI;
            cin.ignore();

            switch(whoAmI)
            {

            case 1:
                passenger.logIn();
                break;

            case 2:
                driver.logIn();
                break;

            case 3:
                admin.logIn();
                break;
            case 4:
                return ;
            default:
                break;
            }

        }

        else if(optionChosen == 2)
        {
            cout<<"\t\t\t\t 1.PASSENGER"<<endl;
            cout<<"\t\t\t\t 2.DRIVER"<<endl;
            cout<<endl;
            cout<<"\t\t\t\t Your are Your are [to go home press 3]: ";
            cin>>whoAmI;
            cin.ignore();
            switch(whoAmI)
            {
            case 1:
                passenger.signUp();
                break;

            case 2:
                driver.signUp();
                break;
            case 3:
                return ;
            default:
                break;
            }
        }


        if(whoAmI>3||whoAmI<1)
        {
            cout<<endl;
            cout<<"Choose option correctly.Thanks"<<endl;
            cin.ignore();
        }
    }
    while(whoAmI>4 || whoAmI<1);



}

int main()
{

//    Database database;
//    int connected;
//    connected = database.createConnection();
//    if(connected){}

    Admin admin;
    Database database;

    int chooseOption;
    int connected;
    string suggestions;

    connected = database.createConnection();
    if(connected)
    {
        do
        {

            system("cls");
            cout<<endl;
            cout << "\t\t\t\t       Find Car" << endl;
            cout << "\t\t\t\t      ----------" << endl;
            cout<<endl<<endl;

            cout<<"\t\t\t\t 1.I have an Account"<<endl;
            cout<<"\t\t\t\t 2.Create new Account"<<endl;
            cout<<"\t\t\t\t 3.Suggestion"<<endl;
            cout<<"\t\t\t\t 4.Exit"<<endl;
            cout<<endl;
            cout<<"\t\t\t\t Choose any option : ";


            cin>>chooseOption;
            cin.ignore();
            if(chooseOption<3)
                whoAmI(chooseOption);
            else if(chooseOption == 3)
            {
                system("cls");
                cout<<endl;
                cout << "\t\t\t\t       Find Car" << endl;
                cout << "\t\t\t\t      ----------" << endl;
                cout<<endl<<endl;
                cout<<"\t\t\t\t Suggestions "<<endl;
                cout<<"\t\t\t\t-------------"<<endl;
                getline(cin,suggestions);
                admin.writeUserReview(suggestions);
            }


        }
        while (chooseOption !=4);
    }
    else
        cout<<"sorry there is some problem with database connection"<<endl;


    return 0;
}
