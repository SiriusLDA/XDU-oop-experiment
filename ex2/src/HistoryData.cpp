#include"HistoryData.hpp"
#include"People.hpp"
HistoryData::HistoryData(string year, string month, string date, string category, string name, double subtotal_price, double subtotal_price_afte_discount)
{
    this->year=year;
    this->month=month;
    this->date=date;
    this->category=category;
    this->name=name;
    this->subtotal_price=subtotal_price;
    this->subtotal_price_afte_discount=subtotal_price_afte_discount;
}
void HistoryData::CheckHistoryExist(vector<Customer>& Customers,int Customer_Index) //Check and create file
{
    stringstream ss;
    ss<<"D:/CodingProjects/oop-experiment/ex2/db/Customer_ShoppingHistory_Info/";
    ss<<Customers[Customer_Index].account;
    ss<<"_ShoppingHistory.txt";
    string filename= ss.str();
    ifstream file(filename);
    if(!file)
    {
        ofstream newFile(filename);
        file.close();
    }
    else return;
}
void HistoryData::LoadHistoryData(vector<HistoryData>& History, vector<Customer>& Customers,int Customer_Index)//load data
{
    History.clear();
    stringstream ss;
    ss<<"D:/CodingProjects/oop-experiment/ex2/db/Customer_ShoppingHistory_Info/";
    ss<<Customers[Customer_Index].account;
    ss<<"_ShoppingHistory.txt";
    string filename= ss.str();
    fstream file;
    file.open(filename, ios::in);
    string line;
    while(getline(file, line))
    {
        istringstream iss(line);
        string Year, Month, Date, Category, Name, Subtotal_price, Subtotal_price_after_discount;
        iss>>Year>>Month>>Date>>Category>>Name>>Subtotal_price>>Subtotal_price_after_discount;
        History.emplace_back(Year, Month, Date, Category, Name, stod(Subtotal_price), stod(Subtotal_price_after_discount)); //load data and push to vector
    }
    file.close();
}
void HistoryData::SaveHistoryData(vector<HistoryData>& History, vector<Customer>& Customers,int Customer_Index)//save data
{
    stringstream ss;
    ss<<"D:/CodingProjects/oop-experiment/ex2/db/Customer_ShoppingHistory_Info/";
    ss<<Customers[Customer_Index].account;
    ss<<"_ShoppingHistory.txt";
    string filename= ss.str();
    ofstream file;
    file.open(filename, ios::trunc); //rewrite file, which means the file can be modified
    int size=History.size();
    for(int i=0;i<size;i++)
    {
        file<<History[i].year<<" "<<History[i].month<<" "<<History[i].date<<" "<<History[i].category<<" "<<History[i].name<<" "<<History[i].subtotal_price<<" "<<History[i].subtotal_price_afte_discount<<"\n";
    }
    file.close();
}
void HistoryData::DisplayHistory(vector<HistoryData>& History)
{
    int size=History.size();
    cout<<"History shopping data are displayed below\n\n";
    for(int i=0;i<size;i++)
    {
        cout<<History[i].year<<" "<<History[i].month<<" "<<History[i].date<<" "<<History[i].category<<" "<<History[i].name<<" "<<History[i].subtotal_price<<" "<<History[i].subtotal_price_afte_discount<<"\n";
    }
    cout<<"\n";
}

void HistoryData::CategorizeData(vector<HistoryData>& History, string year, string month, string date)
{
    unordered_map<string, pair<double,double>> CategoryPriceSum;
    int size=History.size();
    for(int i=0;i<size;i++)
    {
        if(History[i].year==year && History[i].month==month && History[i].date==date)
        {
            CategoryPriceSum[History[i].category].first+=History[i].subtotal_price;
            CategoryPriceSum[History[i].category].second+=History[i].subtotal_price_afte_discount;
        }
    }
    cout<<"History Data Analysis Result:\n\n";
    for(const auto& entry : CategoryPriceSum)
    {
        cout<<"Category: "<<entry.first<<", Total Price: "<<entry.second.first<<", Total Price after discount: "<<entry.second.second<<"\n";
    }
    cout<<"\n";
}

void HistoryData::HistoryAnalysis(vector<HistoryData>& History)
{
    cout<<"Input the date to analysis history data\n";
    cout<<"Format: [year] [month] [date]\n";
    string Year, Month, Date;
    cin>>Year>>Month>>Date;
    HistoryData::CategorizeData(History, Year, Month, Date);
}