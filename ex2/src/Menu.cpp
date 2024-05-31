#include "Menu.hpp"
#include "People.hpp"
#include "Goods.hpp"
#include "ShoppingCartData.hpp"
using namespace std;
//Menu function for admin
void Menu::SwitchUser(Admin admin, vector<Customer>& Customers, vector<Goods>& Store, vector<vector<ShoppingCartData>>& ShoppingCart, vector<vector<HistoryData>> History)
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
        Menu::AdminMainInterface(admin,Customers, Store, ShoppingCart, History);
    }
    else if(choice==2)
    {
        Menu::CustomerMainInterface(admin, Customers, Store, ShoppingCart, History);
    }
    else exit(0);
}

void Menu::AdminMainInterface(Admin admin, vector<Customer>& Customers, vector<Goods>& Store, vector<vector<ShoppingCartData>>& ShoppingCart, vector<vector<HistoryData>> History)
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
        Menu::AdminLogin(admin, Customers, Store, ShoppingCart, History);
    }
    else
    {
        Menu::SwitchUser(admin, Customers, Store, ShoppingCart, History);
    }
}

void Menu::AdminLogin(Admin admin, vector<Customer>& Customers, vector<Goods>& Store, vector<vector<ShoppingCartData>>& ShoppingCart, vector<vector<HistoryData>> History)
{
    int verified=admin.Login();
    if(verified==1)
    {
        Menu::AdminControlPanal(admin, Customers, Store, ShoppingCart, History);
    }
    else Menu::AdminLogin(admin, Customers, Store, ShoppingCart, History);
}

void Menu::AdminControlPanal(Admin admin, vector<Customer>& Customers, vector<Goods>& Store, vector<vector<ShoppingCartData>>& ShoppingCart, vector<vector<HistoryData>> History)
{
    cout<<"---------------------------------------\n";
    cout<<"Welcome to the admin control panal\n";
    cout<<"Input your choice to continue\n";
    cout<<"  1.    Display all goods\n";
    cout<<"  2.    Add goods\n";
    cout<<"  3.    Modify goods\n";
    cout<<"  4.    Delete goods\n";
    cout<<"Others. Return to the login page\n";
    cout<<"---------------------------------------\n\n";
    int choice;
    cin>>choice;
    if(choice==1)
    {
        Goods::DisplayStore(Store);
        Menu::AdminControlPanal(admin, Customers, Store, ShoppingCart, History);
    }
    else if(choice==2)
    {
        Goods::AddGoods(Store);
        Menu::AdminControlPanal(admin, Customers, Store, ShoppingCart, History);
    }
    else if(choice==3)
    {
        Goods::ModifyGoods(Store);
        Menu::AdminControlPanal(admin, Customers, Store, ShoppingCart, History);
    }
    else if(choice==4)
    {
        Goods::DeleteGoods(Store);
        Menu::AdminControlPanal(admin, Customers, Store, ShoppingCart, History);
    } 
    else Menu::AdminMainInterface(admin, Customers, Store, ShoppingCart, History);
}

//Menu function for customer
void Menu::CustomerMainInterface(Admin admin, vector<Customer>& Customers, vector<Goods>& Store, vector<vector<ShoppingCartData>>& ShoppingCart, vector<vector<HistoryData>> History)
{
    cout<<"---------------------------------------\n";
    cout<<"Welcome, customer\n";
    cout<<"Input your choice to continue\n";
    cout<<"  1.    Register\n";
    cout<<"  2.    Login\n";
    cout<<"  3.    Search goods in store\n";
    cout<<"Others. Return to the main menu\n";
    cout<<"---------------------------------------\n\n";
    int choice;
    cin>>choice;
    if(choice==1)
    {
        Customer::Register(Customers);
        vector<ShoppingCartData> new_sp;
        vector<HistoryData> new_his;
        ShoppingCart.push_back(new_sp);
        History.push_back(new_his); //create new object after registering 
        cout<<"You can login now\n";
        Menu::CustomerMainInterface(admin, Customers, Store, ShoppingCart, History);
    }
    else if(choice==2)
    {
        Menu::CustomerLogin(admin, Customers, Store, ShoppingCart, History);
    }
    else if(choice==3)
    {
        Goods::SearchGoodsInStore(Store);
        Menu::CustomerMainInterface(admin, Customers, Store, ShoppingCart, History);
    }
    else Menu::SwitchUser(admin, Customers, Store, ShoppingCart, History);
}

void Menu::CustomerLogin(Admin admin, vector<Customer>& Customers, vector<Goods>& Store, vector<vector<ShoppingCartData>>& ShoppingCart, vector<vector<HistoryData>> History)
{
    int index=Customer::Login(Customers);
    if(index>=0)
    {
        Menu::CustomerControlPanal(admin, Customers,index, Store, ShoppingCart, History);
    }
    else if(index==-1)//wrong password
    {
        Menu::CustomerLogin(admin, Customers, Store, ShoppingCart, History);
    }
    else//account doesn't exist
    {
        Menu::CustomerMainInterface(admin, Customers, Store, ShoppingCart, History);
    }
}

void Menu::CustomerControlPanal(Admin admin, vector<Customer>& Customers, int Customer_index, vector<Goods>& Store, vector<vector<ShoppingCartData>>& ShoppingCart, vector<vector<HistoryData>> History)
{
    cout<<"---------------------------------------\n";
    cout<<"Welcome to the customer control panal\n";
    cout<<"Input your choice to continue\n";
    cout<<"  1.    Search goods in store\n";
    cout<<"  2.    Display all goods in store\n";
    cout<<"  3.    Search goods in shopping cart\n";
    cout<<"  4.    Display all goods in shopping cart\n";
    cout<<"  5.    Add goods to shopping cart\n";
    cout<<"  6.    Delete goods in shopping cart\n";
    cout<<"  7.    Modify goods in shopping cart\n";
    cout<<"  8.    Add goods to settlement list\n";
    cout<<"  9.    Delete goods in pending settlement list\n";
    cout<<"  10.   Settle goods in pending settlement list\n";
    cout<<"  11.   Display shopping history\n";
    cout<<"  12.   Analysis shopping history\n";
    cout<<"Others. Return to the login page\n";
    cout<<"---------------------------------------\n\n";
    ShoppingCartData::CheckShoppingCartExist(Customers, Customer_index);
    ShoppingCartData::LoadShoppingCartData(ShoppingCart[Customer_index], Customers, Customer_index);
    HistoryData::CheckHistoryExist(Customers, Customer_index);
    HistoryData::LoadHistoryData(History[Customer_index], Customers, Customer_index);
    
    int choice;
    cin>>choice;
    if(choice==1)
    {
        Goods::SearchGoodsInStore(Store);
        Menu::CustomerControlPanal(admin, Customers, Customer_index, Store, ShoppingCart, History);
    }
    else if(choice==2)
    {
        Goods::DisplayStore(Store);
        Menu::CustomerControlPanal(admin, Customers, Customer_index, Store, ShoppingCart, History);
    }
    else if(choice==3)
    {
        ShoppingCartData::SearchGoodsInShoppingCart(ShoppingCart[Customer_index]);
        Menu::CustomerControlPanal(admin, Customers, Customer_index, Store, ShoppingCart, History);
    }
    else if(choice==4)
    {
        ShoppingCartData::DisplayShoppingCart(ShoppingCart[Customer_index]);
        Menu::CustomerControlPanal(admin, Customers, Customer_index, Store, ShoppingCart, History);
    }
    else if(choice==5)
    {
        ShoppingCartData::AddToShoppingCart(ShoppingCart[Customer_index],Store, Customers, Customer_index);
        Menu::CustomerControlPanal(admin, Customers, Customer_index, Store, ShoppingCart, History);
    }
    else if(choice==6)
    {
        ShoppingCartData::DeleteGoodsInShoppingCart(ShoppingCart[Customer_index],Store, Customers, Customer_index);
        Menu::CustomerControlPanal(admin, Customers, Customer_index, Store, ShoppingCart, History);
    }
    else if(choice==7)
    {
        ShoppingCartData::ModifyGoodsInShoppingCart(ShoppingCart[Customer_index],Store, Customers, Customer_index);
        Menu::CustomerControlPanal(admin, Customers, Customer_index, Store, ShoppingCart, History);
    }
    else if(choice==8)
    {
        ShoppingCartData::AddtoSettlementList(ShoppingCart[Customer_index],Customers, Customer_index);
        Menu::CustomerControlPanal(admin, Customers, Customer_index, Store, ShoppingCart, History);
    }
    else if(choice==9)
    {
        ShoppingCartData::RemoveFromSettlementList(ShoppingCart[Customer_index], Customers, Customer_index);
        Menu::CustomerControlPanal(admin, Customers, Customer_index, Store, ShoppingCart, History);
    }
    else if(choice==10)
    {
        ShoppingCartData::SettleGoods(ShoppingCart[Customer_index],History[Customer_index], Customers, Customer_index);
        Menu::CustomerControlPanal(admin, Customers, Customer_index, Store, ShoppingCart, History);
    }
    else if(choice==11)
    {
        HistoryData::DisplayHistory(History[Customer_index]);
        Menu::CustomerControlPanal(admin, Customers, Customer_index, Store, ShoppingCart, History);
    }
    else if(choice==12)
    {
        HistoryData::HistoryAnalysis(History[Customer_index]);
        Menu::CustomerControlPanal(admin, Customers, Customer_index, Store, ShoppingCart, History);
    }
    else
    {
        Menu::CustomerMainInterface(admin, Customers, Store, ShoppingCart, History);
    }

}