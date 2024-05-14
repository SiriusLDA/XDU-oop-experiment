#include <bits/stdc++.h>
using namespace std;
class Menu
{
    public:
    static void SwitchUser(Admin admin, vector<Customer>& Customers);

    static void AdminMainInterface(Admin admin, vector<Customer>& Customers);
    static void AdminLogin(Admin admin, vector<Customer>& Customers);
    static void AdminControlPanal(Admin admin, vector<Customer>& Customers);
    
    static void CustomerMainInterface(Admin admin, vector<Customer>& Customers);
    static void CustomerLogin(Admin admin, vector<Customer>& Customers);
    static void CustomerControlPanal(Admin admin, vector<Customer>& Customers, int index);
};