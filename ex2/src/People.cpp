
#include "People.hpp"
using namespace std;
#define Customer_Info_PATH "D:/CodingProjects/oop-experiment/ex2/db/Customer_Info.txt"
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


//Customer function
Customer::Customer(string phone, string name, string account, string password)
{
    this->phone=phone;
    this->name=name;
    this->account=account;
    this->password=password;
}

void Customer::CheckCustomerExist()
{
    ifstream file(Customer_Info_PATH);
    if(!file)//not exist
    {
        ofstream newFile(Customer_Info_PATH); //crete file
        file.close();
    }
    else return;
}

void Customer::LoadCustomerData(vector<Customer>& Customers) //load customer info from file
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
    int size=Customers.size();
    for(int i=0;i<size;i++)
    {
        if(Customers[i].account==Account)
        {
            cout<<"This account has been occupied\n";
            return;
        }
    }
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

