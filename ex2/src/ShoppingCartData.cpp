#include "ShoppingCartData.hpp"
#include "People.hpp"
#include "Goods.hpp"
ShoppingCartData::ShoppingCartData(string category, string name, double single_price, string description, double number, double subtotal_price, string IsInSettlementList)
{
    this->category=category;
    this->name=name;
    this->single_price=single_price;
    this->description=description;
    this->number=number;
    this->subtotal_price=subtotal_price;
    this->IsInSettlementList=IsInSettlementList;
}

void ShoppingCartData::CheckShoppingCartExist(vector<Customer>& Customers,int Customer_Index)
{
    stringstream ss;
    ss<<"D:/CodingProjects/oop-experiment/ex2/db/Customer_ShoppingCart_Info/";
    ss<<Customers[Customer_Index].account;
    ss<<"_ShoppingCart.txt";
    string filename= ss.str();
    ifstream file(filename);
    if(!file)
    {
        ofstream newFile(filename);
        file.close();
    }
    else return;
}

void ShoppingCartData::LoadShoppingCartData(vector<ShoppingCartData>& ShoppingCart, vector<Customer>& Customers, int Customer_Index)
{
    ShoppingCart.clear();
    stringstream ss;
    ss<<"D:/CodingProjects/oop-experiment/ex2/db/Customer_ShoppingCart_Info/";
    ss<<Customers[Customer_Index].account;
    ss<<"_ShoppingCart.txt";
    string filename= ss.str();
    fstream file;
    file.open(filename, ios::in);
    string line;
    while(getline(file, line))
    {
        istringstream iss(line);
        string Category, Name, Single_price, Description, Number, Subtotal_price, IsInSettlementList;
        iss>>Category>>Name>>Single_price>>Description>>Number>>Subtotal_price>>IsInSettlementList;
        ShoppingCart.emplace_back(Category, Name, stod(Single_price), Description, stod(Number), stod(Subtotal_price), IsInSettlementList); //load data and push to vector
    }
    file.close();
}

void ShoppingCartData::SaveShoppingCartData(vector<ShoppingCartData>& ShoppingCart, vector<Customer>& Customers,int Customer_Index)
{
    stringstream ss;
    ss<<"D:/CodingProjects/oop-experiment/ex2/db/Customer_ShoppingCart_Info/";
    ss<<Customers[Customer_Index].account;
    ss<<"_ShoppingCart.txt";
    string filename= ss.str();
    ofstream file;
    file.open(filename, ios::trunc); //rewrite file, which means the file can be modified
    int size=ShoppingCart.size();
    for(int i=0;i<size;i++)
    {
        file<<ShoppingCart[i].category<<" "<<ShoppingCart[i].name<<" "<<ShoppingCart[i].single_price<<" "<<ShoppingCart[i].description<<" "<<ShoppingCart[i].number<<" "<<ShoppingCart[i].subtotal_price<<" "<<ShoppingCart[i].IsInSettlementList<<"\n";
    }
    file.close();
}

void ShoppingCartData::DisplayShoppingCart(vector<ShoppingCartData>& ShoppingCart)
{
    int size=ShoppingCart.size();
    cout<<"All goods in your shopping cart are displayed below\n\n";
    for(int i=0;i<size;i++)
    {
        cout<<ShoppingCart[i].category<<" "<<ShoppingCart[i].name<<" "<<ShoppingCart[i].single_price<<" "<<ShoppingCart[i].description<<" "<<ShoppingCart[i].number<<" "<<ShoppingCart[i].subtotal_price<<" "<<ShoppingCart[i].IsInSettlementList<<"\n";
    }
    cout<<"\n";
    double cost=0;
    for(int i=0;i<size;i++)
    {
        cost+=ShoppingCart[i].subtotal_price;
    }
    cout<<"The price of all the goods in your shopping cart is: "<<cost<<'\n';

    double cost_inlist=0;
    for(int i=0;i<size;i++)
    {
        if(ShoppingCart[i].IsInSettlementList=="1")
        cost_inlist+=ShoppingCart[i].subtotal_price;
    }
    cout<<"The price of all the goods in settlement list is: "<<cost_inlist<<'\n';

}

void ShoppingCartData::AddToShoppingCart(vector<ShoppingCartData>& ShoppingCart, vector<Goods>& Store, vector<Customer>& Customers, int Customer_Index)
{
    cout<<"Input the name of goods and the number you want to add to the shopping cart\n";
    string name, number;
    cout<<"Format: [name] [number]\n";
    cin>>name>>number;
    int Goods_Index=Goods::ReturnGoodsIndex(Store, name);
    if(Goods_Index==-1)
    {
        cout<<"The goods doesn't exist\n";
    }
    else if(stod(number)==0)
    {
        cout<<"The number you buy should be larger than 0\n";
    }
    else if(Goods_Index!=-1 && stod(number)>Store[Goods_Index].inventory)
    {
        cout<<"Beyond inventory. Please decrese the number you buy\n";
    }
    else if(Goods_Index!=-1 && stod(number)<=Store[Goods_Index].inventory)
    {
        double subtotal_price=stod(number)*Store[Goods_Index].price;
        ShoppingCartData data(Store[Goods_Index].category, Store[Goods_Index].name, Store[Goods_Index].price, Store[Goods_Index].description, stod(number), subtotal_price, "0");
        ShoppingCart.push_back(data);
        Store[Goods_Index].inventory-=stod(number);
        SaveShoppingCartData(ShoppingCart, Customers, Customer_Index);
        Goods::SaveStoreData(Store);
        cout<<"Add to shopping cart successful\n";
    }
}

int ShoppingCartData::ReturnIndexInShoppingCart(vector<ShoppingCartData>& ShoppingCart, string name)
{
    int size=ShoppingCart.size();
    for(int i=0; i<size; i++)
    {
        if(name==ShoppingCart[i].name) return i;
    }
    return -1;
}

void ShoppingCartData::SearchGoodsInShoppingCart(vector<ShoppingCartData>& ShoppingCart)
{
    cout<<"Input name of the goods you want to search\n";
    string name;
    cin>>name;
    int GoodsIndex=ShoppingCartData::ReturnIndexInShoppingCart(ShoppingCart, name);
    if(GoodsIndex==-1)
    {
        cout<<"The goods doesn't exist\n";
    }
    else
    {
        cout<<"Information of the goods is displayed below\n\n";
        cout<<ShoppingCart[GoodsIndex].category<<" "<<ShoppingCart[GoodsIndex].name<<" "<<ShoppingCart[GoodsIndex].single_price<<" "<<ShoppingCart[GoodsIndex].description<<" "<<ShoppingCart[GoodsIndex].number<<" "<<ShoppingCart[GoodsIndex].subtotal_price<<"\n\n";
    }
}

void ShoppingCartData::DeleteGoodsInShoppingCart(vector<ShoppingCartData>& ShoppingCart, vector<Goods>& Store, vector<Customer>& Customers,int Customer_Index)
{
    cout<<"Input the name of goods to be deleted\n";
    string Name;
    cin>>Name;
    int Goods_index_sp=ShoppingCartData::ReturnIndexInShoppingCart(ShoppingCart, Name);
    int Goods_index_st=Goods::ReturnGoodsIndex(Store, Name);
    if(Goods_index_sp==-1)
    {
        cout<<"The goods doesn't exist\n";
    }
    else
    {
        Store[Goods_index_st].inventory+= ShoppingCart[Goods_index_sp].number;
        ShoppingCart.erase(ShoppingCart.begin()+Goods_index_sp);
        Goods::SaveStoreData(Store);
        ShoppingCartData::SaveShoppingCartData(ShoppingCart, Customers, Customer_Index);
        cout<<"Delete goods in shopping cart successful\n";
    }
}

void ShoppingCartData::MofifyGoodsInShoppingCart(vector<ShoppingCartData>& ShoppingCart, vector<Goods>& Store, vector<Customer>& Customers,int Customer_Index)
{
    cout<<"Input the name of goods to be modified\n";
    string Name;
    cin>>Name;
    int Goods_index_sp=ShoppingCartData::ReturnIndexInShoppingCart(ShoppingCart, Name);
    int Goods_index_st=Goods::ReturnGoodsIndex(Store, Name);
    if(Goods_index_sp==-1)
    {
        cout<<"The goods doesn't exist\n";
    }
    else
    {
        cout<<"Input the number you want to buy\n";
        double Number;
        cin>>Number;
        if(Number== 0)
        {
            cout<<"The number you buy should be larger than 0\n";
        }
        else if(Number> Store[Goods_index_st].inventory+ ShoppingCart[Goods_index_sp].number)
        {
            cout<<"Beyond inventory. Please decrese the number you buy\n";
        }
        else if(Number<= Store[Goods_index_st].inventory+ ShoppingCart[Goods_index_sp].number)
        {
            Store[Goods_index_st].inventory=Store[Goods_index_st].inventory+ ShoppingCart[Goods_index_sp].number- Number;
            ShoppingCart[Goods_index_sp].number= Number;
            ShoppingCart[Goods_index_sp].subtotal_price= Number * ShoppingCart[Goods_index_sp].single_price;
            Goods::SaveStoreData(Store);
            ShoppingCartData::SaveShoppingCartData(ShoppingCart, Customers, Customer_Index);
            cout<<"Modify goods successful\n";
        }
    }
}

void ShoppingCartData::AddtoSettlementList(vector<ShoppingCartData>& ShoppingCart, vector<Customer>& Customers,int Customer_Index)
{
    cout<<"Input the name of goods you want to add to the settlement list\n";
    string Name;
    cin>>Name;
    int Goods_index_sp=ShoppingCartData::ReturnIndexInShoppingCart(ShoppingCart, Name);
    if(Goods_index_sp==-1)
    {
        cout<<"The goods doesn't exist\n";
    }
    else
    {
        ShoppingCart[Goods_index_sp].IsInSettlementList="1";
        ShoppingCartData::SaveShoppingCartData(ShoppingCart, Customers, Customer_Index);
        cout<<"Add to settlement list successful\n";
    }
}

void ShoppingCartData::RemoveFromSettlementList(vector<ShoppingCartData>& ShoppingCart, vector<Customer>& Customers,int Customer_Index)
{
    cout<<"Input the name of goods you want to remove from the settlement list\n";
    string Name;
    cin>>Name;
    int Goods_index_sp=ShoppingCartData::ReturnIndexInShoppingCart(ShoppingCart, Name);
    if(Goods_index_sp==-1)
    {
        cout<<"The goods doesn't exist\n";
    }
    else
    {
        ShoppingCart[Goods_index_sp].IsInSettlementList="0";
        ShoppingCartData::SaveShoppingCartData(ShoppingCart, Customers, Customer_Index);
        cout<<"Remove from settlement list successful\n";
    }
}

string ShoppingCartData::GenerateDiscountCode(size_t length)
{
    const char charset[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    const size_t max_index = sizeof(charset) - 2;  // Delete '\0' 

    random_device rd;  // Get random seed
    mt19937 generator(rd());  // Create generator
    uniform_int_distribution<size_t> distribution(0, max_index); 

    string random_string;
    random_string.reserve(length);

    for (size_t i = 0; i < length; i++) 
    {
        random_string += charset[distribution(generator)];  // Choose character from charset
    }

    return random_string;
}

int ShoppingCartData::GenerateDiscountNum(int min, int max)
{
    random_device rd;  // Get random seed
    mt19937 gen(rd());  // Create generator
    uniform_int_distribution<int> dis(min, max);
    int random_number = dis(gen);
    return random_number;
}

bool ShoppingCartData::IsInFestival(struct tm& date)
{
    tm start={0,0,0,1,4,124}; //2024-5-1
    tm end={0,0,0,1,5,124}; //2024-6-1
    time_t dateT= mktime(const_cast<tm*>(&date));
    time_t startT= mktime(const_cast<tm*>(&start));
    time_t endT= mktime(const_cast<tm*>(&end));
    return (dateT >= startT && dateT <= endT);
}

void ShoppingCartData::SettleGoods(vector<ShoppingCartData>& ShoppingCart, vector<HistoryData> History, vector<Customer>& Customers,int Customer_Index)
{
    string DiscountCode=ShoppingCartData::GenerateDiscountCode(8);
    int DiscountNumber=ShoppingCartData::GenerateDiscountNum(5,15);
    int FestivalDiscountNumber=ShoppingCartData::GenerateDiscountNum(5,10);

    auto now = chrono::system_clock::now(); //current time point
    time_t now_time = chrono::system_clock::to_time_t(now); //time point transform to time_t
    struct tm* date = localtime(&now_time);//time_t transform to tm struct
    string Year= to_string(date->tm_year+ 1900);
    string Month= to_string(date->tm_mon+ 1);
    string Date= to_string(date->tm_mday);
    bool InFestivalFlag=ShoppingCartData::IsInFestival(*date);

    int TotalDiscount=0;
    if(InFestivalFlag==true)
    {
        cout<<"Good news! During the festival, you will get a "<<FestivalDiscountNumber<<"% off!\n";
        TotalDiscount+=FestivalDiscountNumber;
    }
    cout<<"Good news! You have got a "<<DiscountNumber<<"% off from the system!\n";
    cout<<"Input "<<DiscountCode<<" to enjoy the discount\n";
    string cus_code;
    cin>>cus_code;
    if(cus_code==DiscountCode)
    {
        TotalDiscount+=DiscountNumber;
        cout<<"You have enjoyed the discount\n";
    }
    else
    {
        cout<<"Invaild code\n";
    }
    cout<<"Do you want to settle the goods now?\n";
    cout<<"Press 1 to settle\n";
    int choice;
    cin>>choice;
    if(choice==1)
    {
        int size=ShoppingCart.size();
        double sum=0;
        double sum_after_discount=0;
        for(int i=0;i<size;i++)
        {
            if(ShoppingCart[i].IsInSettlementList=="1")
            {
                sum+=ShoppingCart[i].subtotal_price;
                double Subtotal_price_after_discount= ShoppingCart[i].subtotal_price * (100-TotalDiscount) * 1.0 / 100.0;
                sum_after_discount+=Subtotal_price_after_discount;
                HistoryData his(Year, Month, Date, ShoppingCart[i].category, ShoppingCart[i].name, ShoppingCart[i].subtotal_price, Subtotal_price_after_discount);
                History.push_back(his);
            }
            ShoppingCart.erase(std::remove_if(ShoppingCart.begin(), ShoppingCart.end(), [](const ShoppingCartData& element) {
            return element.IsInSettlementList== "1";
            }), ShoppingCart.end());
        }
        
        ShoppingCartData::SaveShoppingCartData(ShoppingCart, Customers, Customer_Index);
        HistoryData::SaveHistoryData(History, Customers, Customer_Index);
        cout<<"Original Price: "<<sum<<"\n";
        cout<<"Price after discount: "<<sum_after_discount<<"\n";
        cout<<"Settle goods successful\n";
    }
    else
    {
        cout<<"Settle goods abort\n";
        return;
    }

}