// AmaPersishable.cpp
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include <string>
#include "AmaPerishable.h"

using namespace std;

namespace sict
{
    const Date& AmaPerishable::expiry()const
    {
        return expiry_;
    }
    void AmaPerishable::expiry(const Date &value)
    {
        expiry_ = value;
    }
    std::fstream& AmaPerishable::store(std::fstream& file, bool addNewLine)const
    {
        AmaProduct::store(file, false);
        file << "," << expiry_;
        if (addNewLine) {
            file << endl;
        }
        return file;
    }
    std::fstream& AmaPerishable::load(std::fstream& file)
    {
        AmaProduct::load(file);
        Date tmp_;

        file >> tmp_;
        file.ignore();

        expiry(tmp_);

        return file;
    }
    std::ostream& AmaPerishable::write(std::ostream& os, bool linear)const
    {
        AmaProduct::write(os, linear);
        if (err_.isClear() && !Product::isEmpty())
        {
            if (linear)
            {
                os << expiry_;
            }
            else
            {
                os << endl;
                os << "Expiry date: " << expiry_;
            }
        }
        return os;
    }
    std::istream& AmaPerishable::read(std::istream& is)
    {
        Date tmp_;
        err_.clear();
        AmaProduct::read(is);
        if (err_.isClear() && is)
        {
            cout << "Expiry date (YYYY/MM/DD): ";
            is >> tmp_;
            if (tmp_.errCode() == CIN_FAILED)
            {
                err_.message("Invalid Date Entry");
                is.setstate(ios::failbit);
            }
            else if (tmp_.errCode() == YEAR_ERROR)
            {
                err_.message("Invalid Year in Date Entry");
                is.setstate(ios::failbit);
            }
            else if (tmp_.errCode() == MON_ERROR)
            {
                err_.message("Invalid Month in Date Entry");
                is.setstate(ios::failbit);
            }
            else if (tmp_.errCode() == DAY_ERROR)
            {
                err_.message("Invalid Day in Date Entry");
                is.setstate(ios::failbit);
            }

        }
        if (err_.isClear())
        {
            expiry(tmp_);
        }
        return is;
    }
}