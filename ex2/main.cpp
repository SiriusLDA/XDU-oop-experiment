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
    vector<Goods> Store; //创建商店
    vector<vector<ShoppingCartData>> ShoppingCart; //两层vector嵌套，为每个用户创建购物车
    vector<vector<HistoryData>> History;
    
    Customer::CheckCustomerExist();
    Goods::CheckStoreExist();
    Customer::LoadCustomerData(Customers);
    Goods::LoadStoreData(Store); //加载商店数据
    int size=Customers.size();
    for(int i=0;i<size;i++)
    {
        vector<ShoppingCartData> new_sp;//创建一个空的存放购物车数据的内层容器
        vector<HistoryData> new_his;
        ShoppingCart.push_back(new_sp); //将空容器添加到外层容器中
        History.push_back(new_his);
        ShoppingCartData::LoadShoppingCartData(ShoppingCart[i],Customers,i); //加载购物车数据
        HistoryData::LoadHistoryData(History[i],Customers,i);
    }
    Admin admin("admin","114514");

    while(1)
    {
        Menu::SwitchUser(admin, Customers, Store, ShoppingCart, History);
    }
    return 0;
}