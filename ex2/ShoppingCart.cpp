#include <bits/stdc++.h>
#include "ShoppingCart.hpp"
using namespace std;

//Set account and password for admin
Admin::Admin(string account, string password)
{
    this->account=account;
    this->password=password;
    VerifiedSign=0;
}

void Admin::Login()
{
    string account, password;
    cout<<"Input admin account and password:\n";
    cout<<"Format: [account] [password]\n";
    cin>>account>>password;
    if(this->account==account && this->password==password)
    {
        cout<<"Login Successful\n";
        VerifiedSign=1;
    }
    else
    {
        cout<<"Wrong account or password, please try again\n\n";
    }
}

void Admin::Operation()
{
    while(VerifiedSign==0)
    {
        cout<<"You are not logged in, please login first\n";
        Admin::Login();
    }
    cout<<"Operation Successful";
}


