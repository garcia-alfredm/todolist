#ifndef DATE_H
#define DATE_H

#include <iostream>

class Date 
{
  public:
    Date() {};
    Date(int month, int day, int year); 

    ~Date();

    const int& getMonth() const { return d_month; };
    const int& getDay() const { return d_day; };
    const int& getYear() const { return d_year; };

    //operator< handles comparing dates
    bool operator<(const Date& rhs) const;

    //operator== handles determining 
    bool operator==(const Date& rhs) const;

  private:
    int d_month, d_day, d_year;
};

#endif