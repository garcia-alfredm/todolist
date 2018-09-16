#include "Date.h"

#include<iomanip>

Date::Date(int month, int  day, int year): d_month(month), d_day(day), d_year(year)
{} 

Date::~Date() { };

bool Date::operator<(const Date& rhs) const
{
    if(this->d_year < rhs.d_year)
    {
        return true;
    }
    //if the years are equal, we need to determine if months are less than or equal
    else if(this->d_year == rhs.d_year)
    {
        if(this->d_month < rhs.d_month)
        {
            return true;
        }
        //if month is equal, determing which date is less than
        else if(this->d_month == rhs.d_month)
        {
            if(this->d_day < rhs.d_day)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
    return false;
};

bool Date::operator==(const Date& rhs) const
{
    if(this->d_year == rhs.d_year)
    {
        if(this->d_month == rhs.d_month)
        {
            if(this->d_day == rhs.d_day)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}