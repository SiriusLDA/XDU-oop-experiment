#pragma once
#include <bits/stdc++.h>
#include "People.hpp"
#include "ShoppingCartData.hpp"
using namespace std;
class Menu
{
    public:
    friend class ShoppingCartData;
    static void SwitchUser(Admin admin, vector<Customer>& Customers, vector<Goods>& Store, vector<vector<ShoppingCartData>>& ShoppingCart, vector<vector<HistoryData>> History);
    
    private:
    
    static void AdminMainInterface(Admin admin, vector<Customer>& Customers, vector<Goods>& Store, vector<vector<ShoppingCartData>>& ShoppingCart, vector<vector<HistoryData>> History);
    static void AdminLogin(Admin admin, vector<Customer>& Customers, vector<Goods>& Store, vector<vector<ShoppingCartData>>& ShoppingCart, vector<vector<HistoryData>> History);
    static void AdminControlPanal(Admin admin, vector<Customer>& Customers, vector<Goods>& Store, vector<vector<ShoppingCartData>>& ShoppingCart, vector<vector<HistoryData>> History);
    
    static void CustomerMainInterface(Admin admin, vector<Customer>& Customers, vector<Goods>& Store, vector<vector<ShoppingCartData>>& ShoppingCart, vector<vector<HistoryData>> History);
    static void CustomerLogin(Admin admin, vector<Customer>& Customers, vector<Goods>& Store, vector<vector<ShoppingCartData>>& ShoppingCart, vector<vector<HistoryData>> History);
    static void CustomerControlPanal(Admin admin, vector<Customer>& Customers, int Customer_index, vector<Goods>& Store, vector<vector<ShoppingCartData>>& ShoppingCart, vector<vector<HistoryData>> History);
};
