// Final Project Milestone 1
// Version 1.0
// Date 2017-07-04
// Author Galina Erostenko
// Description - Milestone 1 of the Project
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////
#ifndef SICT_DATE_H__
#define SICT_DATE_H__
#include <iostream>
using namespace std;
#define NO_ERROR   0  //--No error the date is valid
#define CIN_FAILED 1  //--istream failed when entering information
#define YEAR_ERROR 2  //--Year value is invalid
#define MON_ERROR  3  //--Month value is invalid
#define DAY_ERROR  4  //--Day value is invalid

namespace sict{
    class Date
    {
    private: 
        int year_;
        int mon_;
        int day_;
        int readErrorCode_; // var holds an error code 
        void setEmpty();
        void errCode(int errorCode);
        int value()const; //provided


    public:
        Date(); //default constructor
        Date(int year, int month, int day); //three arguments constructor
        bool isEmpty() const;
        int mdays()const; //provided
        bool operator==(const Date& D)const;
        bool operator!=(const Date& D)const;
        bool operator<(const Date& D)const;
        bool operator>(const Date& D)const;
        bool operator<=(const Date& D)const;
        bool operator>=(const Date& D)const;
        int errCode()const;
        bool bad()const;
        std::istream& read(std::istream& istr);
        std::ostream& write(std::ostream& ostr)const;

    };
    std::istream& operator>>(std::istream& istr, Date& obj);
    std::ostream& operator << (std::ostream& ostr, const Date& obj);

}
#endif