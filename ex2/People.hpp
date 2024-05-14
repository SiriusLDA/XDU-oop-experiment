#include <bits/stdc++.h>
using namespace std;
class Admin
{
    private:
    //For login
    string account;
    string password;
    public:

    Admin(string account, string password);
    int Login();
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

    Customer(string phone, string name, string account, string password);
    static void LoadCustomerData(vector<Customer>& Customers);
    static void SaveCustomerData(vector<Customer>& Customers);
    static int ReturnAccountIndex(vector<Customer> Customers, string account);

    static void Register(vector<Customer> &Customers);
    static int Login(vector<Customer> &Customers);
    static void ChangePassword(vector<Customer> &Customers, int index);
    static void Search();
    static void Buy();
};