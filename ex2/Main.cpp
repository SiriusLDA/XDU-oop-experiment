#include <bits/stdc++.h>
#include "People.hpp"
#include "Menu.hpp"
using namespace std;
#define Customer_Info_PATH "Customer_Info.txt"

//Admin function
Admin::Admin(string account, string password)
{
    this->account=account;
    this->password=password;
}

int Admin::Login()
{
    string account, password;
    cout<<"Input admin account and password to log in\n";
    cout<<"Format: [account] [password]\n";
    cin>>account>>password;
    if(this->account==account && this->password==password)
    {
        cout<<"Login Successful\n";
        return 1;
    }
    else
    {
        cout<<"Wrong account or password, please try again\n";
        return 0;
    }
}

void Admin::Operation()
{
    cout<<"Operation Successful\n";
}

//Customer function
Customer::Customer(string phone, string name, string account, string password)
{
    this->phone=phone;
    this->name=name;
    this->account=account;
    this->password=password;
}

void Customer::LoadCustomerData(vector<Customer>& Customers)
{
    Customers.clear(); //clear the vector first
    fstream file;
    file.open(Customer_Info_PATH, ios::in);
    string line;
    while(getline(file, line))
    {
        istringstream iss(line);
        string Phone, Name, Account, Password;
        iss>>Phone>>Name>>Account>>Password;
        Customers.emplace_back(Phone, Name, Account, Password); //load data and push to vector
    }
    file.close();
}

void Customer::SaveCustomerData(vector<Customer>& Customers) //Save all info in vector to file
{
    ofstream file;
    file.open(Customer_Info_PATH, ios::trunc); //rewrite file, which means the file can be modified
    int size=Customers.size();
    for(int i=0;i<size;i++)
    {
        file<<Customers[i].phone<<" "<<Customers[i].name<<" "<<Customers[i].account<<" "<<Customers[i].password<<"\n";
    }
    file.close();
}

int Customer::ReturnAccountIndex(vector<Customer> Customers, string account) //return account index
{
    int size=Customers.size();
    for(int i=0; i<size; i++)
    {
        if(account==Customers[i].account) return i;
    }
    return -1;
}

void Customer::Register(vector<Customer>& Customers)
{
    string Phone, Name, Account, Password;
    cout<<"Input your phone, name, account and password to register\n";
    cout<<"Format: [phone] [name] [account] [password]\n";
    cin>>Phone>>Name>>Account>>Password;
    Customer new_cus(Phone, Name, Account, Password);
    Customers.push_back(new_cus);
    SaveCustomerData(Customers);
    cout<<"Register Successful\n";
}

int Customer::Login(vector<Customer> &Customers)
{
    Customer::LoadCustomerData(Customers);

    string Account, Password;
    cout<<"Input your account and password to login\n";
    cout<<"Format: [account] [password]\n";
    cin>>Account>>Password;
    int index=Customer::ReturnAccountIndex(Customers, Account);
    if(index!=-1 && Customers[index].password==Password)
    {
        cout<<"Login Successful\n";
        return index;
    }
    else if(index!=-1 && Customers[index].password!=Password)
    {
        cout<<"Wrong password, please try again\n";
        return -1;
    }
    else
    {
        cout<<"The account does not exist, please register or login again\n";
        return -2;
    }
}

void Customer::ChangePassword(vector<Customer> &Customers, int index)
{
    cout<<"Input new password\n";
    string new_password;
    cin>>new_password;
    Customers[index].password=new_password;
    Customer::SaveCustomerData(Customers);
    cout<<"Change password Successful\n";
}

void Customer::Search()
{
    cout<<"Search Successful\n";
}

void Customer::Buy()
{
    cout<<"Buy successful\n";
}

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