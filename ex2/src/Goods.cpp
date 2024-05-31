#include "Goods.hpp"
using namespace std;
#define Store_Info_PATH "D:/CodingProjects/oop-experiment/ex2/db/Store_Info.txt" //define file path

Goods::Goods(string category, string name, double price, string description, double inventory) //constructor
{
    this->category=category;
    this->name=name;
    this->price=price;
    this->description=description;
    this->inventory=inventory;
}

void Goods::CheckStoreExist()
{
    ifstream file(Store_Info_PATH);
    if(!file)//not exist
    {
        ofstream newFile(Store_Info_PATH); //crete file
        file.close();
    }
    else return;
}

void Goods::LoadStoreData(vector<Goods>& Store) //load store data from file
{
    Store.clear(); //clear vector first to avoid repeating 
    fstream file; 
    file.open(Store_Info_PATH, ios::in);//open file in read mode
    string line;
    while(getline(file, line))
    {
        istringstream iss(line); //define istringstream
        string Category, Name, Price, Description, Inventory;
        iss>>Category>>Name>>Price>>Description>>Inventory; //read data
        Store.emplace_back(Category, Name, stod(Price), Description, stod(Inventory)); //push to vector
    }
    file.close();//close file
}

void Goods::SaveStoreData(vector<Goods>& Store) //Save all info in vector to file
{
    ofstream file;
    file.open(Store_Info_PATH, ios::trunc); //rewrite file, which means the file is erased at first 
    int size=Store.size();
    for(int i=0;i<size;i++)
    {
        file<<Store[i].category<<" "<<Store[i].name<<" "<<Store[i].price<<" "<<Store[i].description<<" "<<Store[i].inventory<<"\n"; //write to file in certain format
    }
    file.close();//close file
}

void Goods::DisplayStore(vector<Goods>& Store)//display store info
{
    int size=Store.size();
    cout<<"All goods in the store are displayed below\n\n";
    for(int i=0;i<size;i++)
    {
        cout<<Store[i].category<<" "<<Store[i].name<<" "<<Store[i].price<<" "<<Store[i].description<<" "<<Store[i].inventory<<"\n";
    }
    cout<<"\n";
}

int Goods::ReturnGoodsIndex(vector<Goods> Store, string name) //return goods index in store by name
{
    int size=Store.size();
    for(int i=0; i<size; i++)
    {
        if(name==Store[i].name) return i; //index
    }
    return -1;//not found sign
}

void Goods::AddGoods(vector<Goods>& Store)//add goods to store
{
    string Category, Name, Price, Description, Inventory;
    cout<<"Input the information of goods to be added\n";
    cout<<"Format: [category] [name] [price] [description] [inventory]\n";
    cin>>Category>>Name>>Price>>Description>>Inventory;
    //avoid existence
    int size=Store.size();
    for(int i=0;i<size;i++)
    {
        if(Store[i].name==Name)
        {
            cout<<"The goods is already in store\n";
            return;
        }
    }
    Goods new_goods(Category, Name, stod(Price), Description, stod(Inventory));//create new object
    Store.push_back(new_goods);//push to vector
    SaveStoreData(Store);//save data after updating vector
    cout<<"Add goods Successful\n";
}

void Goods::DeleteGoods(vector<Goods>& Store)//detele goods in store
{
    cout<<"Input the name of goods to be deleted\n";
    string Name;
    cin>>Name;
    int Goods_index=Goods::ReturnGoodsIndex(Store, Name);
    if(Goods_index==-1)//not found
    {
        cout<<"The goods doesn't exist\n";
    }
    else
    {
        Store.erase(Store.begin()+Goods_index);//erase according to index in store
        Goods::SaveStoreData(Store);//save data after updating vector
        cout<<"Delete goods in store successful\n";
    }
}

void Goods::ModifyGoods(vector<Goods>& Store)//modify information
{
    cout<<"Input the name of goods to be modified\n";
    string Name;
    cin>>Name;
    int Goods_index=Goods::ReturnGoodsIndex(Store, Name);
    if(Goods_index==-1)//not found
    {
        cout<<"The goods doesn't exist\n";
    }
    else
    {
        cout<<"Input the information of goods to be modified\n";
        cout<<"Format: [price] [description] [inventory]\n";
        string Price, Description, Inventory;
        cin>>Price>>Description>>Inventory;
        if(stod(Inventory)<0) //illegal input
        {
            cout<<"Inventory should be no less than 0\n";
        }
        else
        {
            //modify information according to index
            Store[Goods_index].price=stod(Price);
            Store[Goods_index].description=Description;
            Store[Goods_index].inventory=stod(Inventory);
            Goods::SaveStoreData(Store);//save data after updating vector
            cout<<"Modify goods successful\n";
        }
        
    }
}

void Goods::SearchGoodsInStore(vector<Goods>& Store) //keyword search
{
    cout<<"Input keyword or name of the goods\n";
    string keyword;
    cin>>keyword;
    int ClosestMatchIndex=Goods::ClosestMatch(Store, keyword);
    cout<<"Information of the most similar goods is displayed below\n\n";
    cout<<Store[ClosestMatchIndex].category<<" "<<Store[ClosestMatchIndex].name<<" "<<Store[ClosestMatchIndex].price<<" "<<Store[ClosestMatchIndex].description<<" "<<Store[ClosestMatchIndex].inventory<<"\n\n";
}

int Goods::LevenshteinDistance(string& s1, string& s2) //calculate LD
{
    int m=s1.length();
    int n=s2.length();
    vector<vector<int>> dp(m+1, vector<int>(n+1,0));
    for(int i=0;i<=m;++i)
    {
        dp[i][0]=i;
    }
    for(int j=0;j<=n;++j)
    {
        dp[0][j]=j;
    }
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if(s1[i-1]==s2[j-1])
            {
                dp[i][j]=dp[i-1][j-1];
            }
            else
            {
                dp[i][j]=1 + min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
            }
        }
    }
    return dp[m][n];
}

int Goods::ClosestMatch(vector<Goods>& Store, string& keyword) //find min LD Index
{
    int ClosestMatchIndex=-1;
    int minDistance= numeric_limits<int>::max();
    int size=Store.size();
    for(int i=0;i<size;i++)//
    {
        int distance=Goods::LevenshteinDistance(Store[i].name, keyword);
        if(distance< minDistance)
        {
            minDistance=distance; //update min distance
            ClosestMatchIndex=i;
        }
    }
    return ClosestMatchIndex;
}