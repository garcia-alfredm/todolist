#ifndef DATE_H
#define DATE_H

#include <iomanip>
#include <ostream>
#include <utility>

class Date 
{
  public:
    Date() {};
    Date(const int & month, const int & day, const int & year): 
      d_month{std::move(month)}, 
      d_day{std::move(day)}, 
      d_year{std::move(year)} {}; 

    ~Date() {};

    const int& getMonth() const { return d_month; };
    const int& getDay() const { return d_day; };
    const int& getYear() const { return d_year; };

    /* handles comparing dates */
    bool operator<(const Date& rhs) const;

    /* Determines if dates are equal */ 
    bool operator==(const Date& rhs) const;

    friend std::ostream& operator<<(std::ostream& out, const Date& date);

  private:
    int d_month, d_day, d_year;
};

#endif
