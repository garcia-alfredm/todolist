#include "Date.h"

bool Date::operator<(const Date& rhs) const{
    if(this->d_year < rhs.d_year){
        return true;
    }
    /* if the years are equal, we need to determine if months are less than or equal */
    else if(this->d_year == rhs.d_year){
        if(this->d_month < rhs.d_month){
            return true;
        }
        /* if month is equal, determing which date is less than */
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

std::ostream& operator<<(std::ostream& out, const Date& date){
    out << std::setfill('0') << std::setw(2) << date.getMonth() << "/" 
        << std::setfill('0') << std::setw(2) << date.getDay() << "/" 
		<< std::setw(4) << date.getYear();
    return out;    
};
