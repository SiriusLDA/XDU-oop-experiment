#include <bits/stdc++.h>
using namespace std;
class Admin
{
    private:
    //For login
    string account;
    string password;
    int VerifiedSign;
    public:
    Admin(string account, string password);
    void Login();
    void Operation();
};

class Customer
{
    private:
    //For register
    string phone;
    string name;
    //For login
    string account;
    string password;

    public:
    int Register(string phone, string name);
    int Login(string account, string password);
    int ChangePassword(string new_password);
    void Search();
    void Buy();
};