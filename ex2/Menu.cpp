#include "Menu.hpp"
#include "People.hpp"

//Menu function for admin
void Menu::SwitchUser(Admin admin, vector<Customer>& Customers)
{
    cout<<"---------------------------------------\n";
    cout<<"Welcome to the shopping cart system\n";
    cout<<"Input your choice to continue\n";
    cout<<"  1.    Continue as admin\n";
    cout<<"  2.    Continue as customer\n";
    cout<<"Others. Exit\n";
    cout<<"---------------------------------------\n\n";
    int choice;
    cin>>choice;
    if(choice==1)
    {
        Menu::AdminMainInterface(admin,Customers);
    }
    else if(choice==2)
    {
        Menu::CustomerMainInterface(admin, Customers);
    }
    else exit(0);
}

void Menu::AdminMainInterface(Admin admin, vector<Customer>& Customers)
{
    cout<<"---------------------------------------\n";
    cout<<"Welcome, admin\n";
    cout<<"Input your choice to continue\n";
    cout<<"  1.    Login\n";
    cout<<"Others. Return to the main menu\n";
    cout<<"---------------------------------------\n\n";
    int choice;
    cin>>choice;
    if(choice==1)
    {
        Menu::AdminLogin(admin, Customers);
    }
    else
    {
        Menu::SwitchUser(admin, Customers);
    }
}

void Menu::AdminLogin(Admin admin, vector<Customer>& Customers)
{
    int verified=admin.Login();
    if(verified==1)
    {
        Menu::AdminControlPanal(admin, Customers);
    }
    else Menu::AdminLogin(admin, Customers);
}

void Menu::AdminControlPanal(Admin admin, vector<Customer>& Customers)
{
    cout<<"---------------------------------------\n";
    cout<<"Welcome to the admin control panal\n";
    cout<<"Input your choice to continue\n";
    cout<<"  1.    Operation\n";
    cout<<"Others. Return to the login page\n";
    cout<<"---------------------------------------\n\n";
    int choice;
    cin>>choice;
    if(choice==1)
    {
        admin.Operation();
        Menu::AdminControlPanal(admin, Customers);
    } 
    else Menu::AdminMainInterface(admin, Customers);
}

//Menu function for customer
void Menu::CustomerMainInterface(Admin admin, vector<Customer>& Customers)
{
    cout<<"---------------------------------------\n";
    cout<<"Welcome, customer\n";
    cout<<"Input your choice to continue\n";
    cout<<"  1.    Register\n";
    cout<<"  2.    Login\n";
    cout<<"  3.    Search goods\n";
    cout<<"Others. Return to the main menu\n";
    cout<<"---------------------------------------\n\n";
    int choice;
    cin>>choice;
    if(choice==1)
    {
        Customer::Register(Customers);
        cout<<"You can login now\n";
        Menu::CustomerMainInterface(admin, Customers);
    }
    else if(choice==2)
    {
        Menu::CustomerLogin(admin, Customers);
    }
    else if(choice==3)
    {
        Customer::Search();
        Menu::CustomerMainInterface(admin, Customers);
    }
    else Menu::SwitchUser(admin, Customers);
}

void Menu::CustomerLogin(Admin admin, vector<Customer>& Customers)
{
    int index=Customer::Login(Customers);
    if(index>=0)
    {
        Menu::CustomerControlPanal(admin, Customers,index);
    }
    else if(index==-1)
    {
        Menu::CustomerLogin(admin, Customers);
    }
    else
    {
        Menu::CustomerMainInterface(admin, Customers);
    }
}

void Menu::CustomerControlPanal(Admin admin, vector<Customer>& Customers, int index)
{
    cout<<"---------------------------------------\n";
    cout<<"Welcome to the customer control panal\n";
    cout<<"Input your choice to continue\n";
    cout<<"  1.    Search goods\n";
    cout<<"  2.    Buy goods\n";
    cout<<"  3.    Change password\n";
    cout<<"Others. Return to the login page\n";
    cout<<"---------------------------------------\n\n";
    int choice;
    cin>>choice;
    if(choice==1)
    {
        Customer::Search();
        Menu::CustomerControlPanal(admin, Customers, index);
    }
    else if(choice==2)
    {
        Customer::Buy();
        Menu::CustomerControlPanal(admin, Customers, index);
    }
    else if(choice==3)
    {
        Customer::ChangePassword(Customers, index);
        Menu::CustomerControlPanal(admin, Customers, index);
    }
    else
    {
        Menu::CustomerMainInterface(admin, Customers);
    }

}