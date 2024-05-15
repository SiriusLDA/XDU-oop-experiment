#include <bits/stdc++.h>
#include "People.hpp"
#include "Menu.hpp"
using namespace std;
int main()
{
    vector<Customer> Customers;
    Admin admin("admin","114514");
    Customer::LoadCustomerData(Customers);
    while(1)
    {
        Menu::SwitchUser(admin, Customers);
    }
}