// Final Project Milestone 1
// Version 1.0
// Date 2017-07-04
// Author Galina Erostenko
// Description - Milestone 1 of the Project
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////
#include <iostream>
#include <cstring>
#include "Date.h"
#include "general.h"
#define _CRT_SECURE_NO_WARNINGS
using namespace std;

namespace sict{
    //provided function
    int Date::value()const {
        return year_ * 372 + mon_ * 31 + day_;
    }
    //provided function
    int Date::mdays()const {
        int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
        int mon = mon_ >= 1 && mon_ <= 12 ? mon_ : 13;
        mon--;
        return days[mon] + int((mon == 1)*((year_ % 4 == 0) && (year_ % 100 != 0)) || (year_ % 400 == 0));
    }

    //sets an object to an empty state
    void Date::setEmpty()
    {
         year_ = 0;
         mon_ = 0;
         day_ = 0;
         readErrorCode_ = NO_ERROR;
    }
    // assigns the error code
    void Date::errCode(int errorCode)
    {
        readErrorCode_ = errorCode;
    }
    //default constructor, sets to emty state
    Date::Date()
    {
        setEmpty();
    }
    //returns true if object is empty
    bool Date::isEmpty() const
    {
        return (year_ == 0 && mon_ == 0 && day_ == 0);
    }
    //three parameters constructor
    Date::Date(int year, int month, int day)
    {
        if (MIN_YEAR < year &&  year < MAX_YEAR && 1 <= month && month <= 12 && 1 <= day && day <= 31)
        {
             year_ = year;
             mon_ = month;
             readErrorCode_ = NO_ERROR;
            if (day <= mdays())
            {
                 day_ = day;
            }
            else
            {
                setEmpty();
            }
        }
        else
        {
            setEmpty();
        }
    }
    // "==" operator overload
    bool Date::operator==(const Date& D)const
    {
        return this->value() == D.value();
    }
    // "!=" operator overload
    bool Date::operator!=(const Date& D)const
    {
        return this->value() != D.value();
    }
    // "<" operator overload
    bool Date::operator<(const Date& D)const
    {
        return this->value() < D.value();
    }
    // ">" operator overload
    bool Date::operator>(const Date& D)const
    {
        return this->value() > D.value();
    }
    // "<=" operator overload
    bool Date::operator<=(const Date& D)const
    {
        return this->value() <= D.value();
    }
    // ">=" operator overload
    bool Date::operator>=(const Date& D)const
    {
        return this->value() >= D.value();
    }
    //returns error code
    int Date::errCode()const
    {
        return readErrorCode_;
    }
    //return true if there is an error
    bool Date::bad()const
    {
        return readErrorCode_ != NO_ERROR;
    }
    //stores the date and validate it
    std::istream& Date::read(std::istream& istr)
    {
        char del;

        istr >> year_ >> del >> mon_ >> del >> day_;

        if (istr.fail())
        {
            errCode(CIN_FAILED);
            return istr;
        }

        if (MIN_YEAR > year_ ||  year_ > MAX_YEAR)
        {
            errCode(YEAR_ERROR);
        }
        else if (1 > mon_ || mon_ > 12)
        {
            errCode(MON_ERROR);
        }
        else if (1 > day_ || day_ > mdays())
        {
            errCode(DAY_ERROR);
        }
        return istr;
    }
    //format the date
    std::ostream& Date::write(std::ostream& ostr)const
    {
        ostr << year_ << "/";
        cout.fill('0');
        cout.width(2);
        ostr << mon_ << "/";
        cout.width(2);
        ostr << day_;
        cout.fill(' ');

        return ostr;
    }
    //">>" overload
    std::istream& operator >> (std::istream& istr, Date& obj)
    {
        return obj.read(istr);
    }
    //"<<" overload
    std::ostream& operator << (std::ostream& ostr, const Date& obj)
    {
        return obj.write(ostr);
    }
}
