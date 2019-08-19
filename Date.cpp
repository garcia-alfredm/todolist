#include "Date.h"

/* Overload operator< to handle comparing Date objects
 * Returns true if Date is less than rhs
 * Returns false if object is greater or equal to rhs
 * @rhs: Date object begin compared to
 * Precondition: Date object data members are initialized
 */
bool Date::operator<(const Date& rhs) const{
    if(this->d_year < rhs.d_year){
        return true;
    }
    /* if the years are equal, determine if months are less than or equal */
    else if(this->d_year == rhs.d_year){
        if(this->d_month < rhs.d_month){
            return true;
        }
        /* if month is equal, determine which date is less than */
        else if(this->d_month == rhs.d_month){
            if(this->d_day < rhs.d_day){
                return true;
            }
            else{
                return false;
            }
        }
    }
    return false;
};

/* Overload operator== to determine if Date
 * objects are equal to eachother
 * @rhs: Date object being compared to
 * @return: true if Dates are equal, false else
 * Precondition: Date object data members are initialized
 */
bool Date::operator==(const Date& rhs) const{
    if(this->d_year == rhs.d_year){
        if(this->d_month == rhs.d_month){
            if(this->d_day == rhs.d_day){
                return true;
            }
            else{
                return false;
            }
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
};
/* Overload operator<< to print Date data members to output
 * @out: ostream object initizlied to standard output
 * @date: Date object being printed
 * @returns object at @out
 * Precondition: @out and @date are initialized
 * Postcondition: returns ostream object with formatted dates
 */
std::ostream& operator<<(std::ostream& out, const Date& date){
    out << std::setfill('0') << std::setw(2) << date.getMonth() << "/" 
        << std::setfill('0') << std::setw(2) << date.getDay() << "/" 
		<< std::setw(4) << date.getYear();
    return out;    
};
