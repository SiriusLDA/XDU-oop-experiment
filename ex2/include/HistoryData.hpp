#pragma once
#include <bits/stdc++.h>
#include "People.hpp"
using namespace std;

class HistoryData
{
    private:
    string year;
    string month;
    string date;
    string category;
    string name;
    double subtotal_price;
    double subtotal_price_afte_discount;

    public:
    friend class ShoppingCartData;
    HistoryData(string year, string month, string date, string category, string name, double subtotal_price, double subtotal_price_afte_discount);
    static void CheckHistoryExist(vector<Customer>& Customers,int Customer_Index);
    static void LoadHistoryData(vector<HistoryData>& History, vector<Customer>& Customers,int Customer_Index);
    static void SaveHistoryData(vector<HistoryData>& History, vector<Customer>& Customers,int Customer_Index);
    static void DisplayHistory(vector<HistoryData>& History);
    static void CategorizeData(vector<HistoryData>& History, string year, string month, string date);
    static void HistoryAnalysis(vector<HistoryData>& History);
    
};