#pragma once
#include <bits/stdc++.h>
#include "Goods.hpp"
#include "People.hpp"
#include "HistoryData.hpp"
using namespace std;
class ShoppingCartData
{
    private:
    string category;
    string name;
    double single_price;
    string description;
    double number;
    double subtotal_price;
    string IsInSettlementList;

    public:
    ShoppingCartData(string category, string name, double single_price, string description, double number, double subtotal_price, string IsInSettlementList);
    static void CheckShoppingCartExist(vector<Customer>& Customers,int Customer_Index);
    static void LoadShoppingCartData(vector<ShoppingCartData>& ShoppingCart, vector<Customer>& Customers,int Customer_Index);
    static void SaveShoppingCartData(vector<ShoppingCartData>& ShoppingCart, vector<Customer>& Customers,int Customer_Index);
    static void DisplayShoppingCart(vector<ShoppingCartData>& ShoppingCart);
    static void AddToShoppingCart(vector<ShoppingCartData>& ShoppingCart, vector<Goods>& Store, vector<Customer>& Customers,int Customer_Index);
    static int ReturnIndexInShoppingCart(vector<ShoppingCartData>& ShoppingCart, string name);
    static void SearchGoodsInShoppingCart(vector<ShoppingCartData>& ShoppingCart);
    static void DeleteGoodsInShoppingCart(vector<ShoppingCartData>& ShoppingCart, vector<Goods>& Store, vector<Customer>& Customers,int Customer_Index);
    static void MofifyGoodsInShoppingCart(vector<ShoppingCartData>& ShoppingCart, vector<Goods>& Store, vector<Customer>& Customers,int Customer_Index);

    static void AddtoSettlementList(vector<ShoppingCartData>& ShoppingCart, vector<Customer>& Customers,int Customer_Index);
    static void RemoveFromSettlementList(vector<ShoppingCartData>& ShoppingCart, vector<Customer>& Customers,int Customer_Index);
    static string GenerateDiscountCode(size_t length);
    static int GenerateDiscountNum(int min, int max);
    static bool IsInFestival(struct tm& date);
    static void SettleGoods(vector<ShoppingCartData>& ShoppingCart, vector<HistoryData> History, vector<Customer>& Customers,int Customer_Index);

};
