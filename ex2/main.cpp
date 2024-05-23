#include <bits/stdc++.h>
#include "People.hpp"
#include "Menu.hpp"
#include "Goods.hpp"
#include "ShoppingCartData.hpp"
#include "HistoryData.hpp"
using namespace std;
int main()
{
    //Init
    vector<Customer> Customers;
    vector<Goods> Store;
    vector<vector<ShoppingCartData>> ShoppingCart;
    vector<vector<HistoryData>> History;
    
    Customer::LoadCustomerData(Customers);
    Goods::LoadStoreData(Store);
    int size=Customers.size();
    for(int i=0;i<size;i++)
    {
        vector<ShoppingCartData> new_sp;
        vector<HistoryData> new_his;
        ShoppingCart.push_back(new_sp);
        History.push_back(new_his);
        ShoppingCartData::LoadShoppingCartData(ShoppingCart[i],Customers,i);
        HistoryData::LoadHistoryData(History[i],Customers,i);
    }
    Admin admin("admin","114514");

    while(1)
    {
        Menu::SwitchUser(admin, Customers, Store, ShoppingCart, History);
    }
    return 0;
}