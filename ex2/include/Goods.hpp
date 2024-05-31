#pragma once
#include <bits/stdc++.h>
using namespace std;
class Goods
{
    private:
    string category;
    string name;
    double price;
    string description;
    double inventory;

    public:
    friend class ShoppingCartData;
    Goods(string category, string name, double price, string description, double inventory);
    static void CheckStoreExist();
    static void LoadStoreData(vector<Goods>& Store);
    static void SaveStoreData(vector<Goods>& Store);
    static void DisplayStore(vector<Goods>& Store);
    static int ReturnGoodsIndex(vector<Goods> Store, string name);
    static void AddGoods(vector<Goods>& Store);
    static void DeleteGoods(vector<Goods>& Store);
    static void ModifyGoods(vector<Goods>& Store);
    static void SearchGoodsInStore(vector<Goods>& Store);
    static int LevenshteinDistance(string& s1, string& s2);
    static int ClosestMatch(vector<Goods>& Store, string& keyword);
};
