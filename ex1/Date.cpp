#include<bits/stdc++.h>
#include"Date.hpp"

int Date::calculate_difference(struct tm Time)
{
    time_t stamp=mktime(&Time);
    return stamp/86400;
}

void Date::init(int y, int m, int d)
{
    struct tm Time={0};
    Time.tm_year=y-1900;
    Time.tm_mon=m-1;
    Time.tm_mday=d;
    Time.tm_hour=8; //UTC +8:00
    day_difference=Date::calculate_difference(Time);
    std::cout<<day_difference<<std::endl;
}

void Date::add_year(int y)
{
    struct tm* Time=NULL;
    time_t raw=day_difference*86400; //original time difference in seconds
    Time=localtime(&raw);
    Time->tm_year+=y;//add the years
    day_difference=Date::calculate_difference(*Time);
    std::cout<<day_difference<<std::endl;
}

void Date::add_month(int m)
{
    struct tm* Time=NULL;
    time_t raw=day_difference*86400; //original time difference in seconds
    Time=localtime(&raw);
    Time->tm_year+=(Time->tm_mon+m)/12;
    Time->tm_mon=(Time->tm_mon+m)%12;
    day_difference=Date::calculate_difference(*Time);
    std::cout<<day_difference<<std::endl;
}

void Date::add_day(int d)
{
    struct tm* Time=NULL;
    time_t raw=(day_difference+d)*86400; //add the days
    Time=localtime(&raw);
    day_difference=Date::calculate_difference(*Time);
    std::cout<<day_difference<<std::endl;
}

