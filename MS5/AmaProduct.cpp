// AmaProduct.cpp
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include <string>
#include "AmaProduct.h"

using namespace std;

namespace sict
{
    //AmaProduct constructor
    AmaProduct::AmaProduct(char filetag)
    {
        fileTag_ = filetag;
    }
    //pointer to the unit_ 
    const char* AmaProduct::unit()const
    {
        return unit_;
    }
    //copies into unit_
    void AmaProduct::unit(const char* value)
    {
        unit_[0] = '\0';
        strncpy(unit_, value, 11);
        unit_[11] = '\0';
    }
    //
    std::fstream& AmaProduct::store(std::fstream& file, bool addNewLine)const
    {
        if (file.is_open())
        {
            file << fileTag_ << "," << sku() << "," << name() << "," << price() << "," << taxed() << "," << quantity() << "," << unit_ << "," << qtyNeeded();
            if (addNewLine) {
                file << endl;
            }
        }
        return file;
    }
    std::fstream& AmaProduct::load(std::fstream& file)
    {
        char tmp_sku[100];   
        char tmp_name[100]; 
        double tmp_price;    
        bool tmp_taxed;      
        int tmp_quantity;
        int tmp_needed;

        file.getline(tmp_sku, 100, ',');
        file.getline(tmp_name, 100, ',');
        file >> tmp_price;
        file.ignore();
        file >> tmp_taxed;
        file.ignore();
        file >> tmp_quantity;
        file.ignore();
        file.getline(unit_, 11, ',');
        file >> tmp_needed;
        file.ignore();

        sku(tmp_sku);    
        name(tmp_name);          
        price(tmp_price);        
        taxed(tmp_taxed);        
        quantity(tmp_quantity);
        qtyNeeded(tmp_needed);

        return file;
    }
    std::ostream& AmaProduct::write(std::ostream& os, bool linear)const
    {
        if (!err_.isClear())
        {
            os << err_;
        }
        else if (linear)
        {
            os.setf(ios::fixed);
            os.unsetf(ios::right);
            os.setf(ios::left);
            os.width(MAX_SKU_LEN);
            os << sku() << "|";
            os.width(20);
            os.unsetf(ios::right);
            os.setf(ios::left);
            os << name() << "|";
            os.setf(ios::right);
            os.width(7);
            os.precision(2);
            os << cost() << "|";
            os.setf(ios::right);
            os.width(4);
            os << quantity() << "|";
            os.width(10);
            os.unsetf(ios::right);
            os.setf(ios::left);
            os << unit_ << "|";
            os.setf(ios::right);
            os.width(4);
            os << qtyNeeded() << "|";
        }
        else
        {
            os << "Sku: " << sku() << endl;
            os << "Name: " << name() << endl;
            os << "Price: " << price() << endl;
            os << "Price after tax: ";
            if (taxed())
            os << cost() << endl;
            else
            {
                os << "N/A" << endl;
            }
            os << "Quantity On Hand: " << quantity() << " " << unit_ << endl;
            os << "Quantity Needed: " << qtyNeeded();
        }
        return os;
    }
    std::istream& AmaProduct::read(std::istream& is)
    {
        char tmp_sku[100];
        char tmp_name[100];
        double tmp_price;
        char tmp_taxed;
        int tmp_quantity;
        int qtyNeed;
        bool taxed__;
        err_.clear();

        if (is) {
            cout << "Sku: ";
            is >> tmp_sku;

            cout << "Name: ";
            is >> tmp_name;

            cout << "Unit: ";
            is >> unit_;

            cout << "Taxed? (y/n): ";
            is >> tmp_taxed;
            if (tmp_taxed == 'y' || tmp_taxed == 'Y') {
                taxed__ = true;
                is.clear();
            }
            else if (tmp_taxed == 'n' || tmp_taxed == 'N'){
                taxed__ = false;
                is.clear();
            }
            else
            {
                err_.message("Only (Y)es or (N)o are acceptable");
                is.setstate(ios::failbit);
            }
            if (!is.fail())
            {
                cout << "Price: ";
                is >> tmp_price;
                if (is.fail())
                {
                    err_.message("Invalid Price Entry");
                    is.setstate(ios::failbit);
                }
            }

            if (!is.fail())
            {
            cout << "Quantity On hand: ";
            is >> tmp_quantity;
            if (is.fail())
            {
                err_.message("Invalid Quantity Entry");
                is.setstate(ios::failbit);
            }
            }
            if (!is.fail())
            {
            cout << "Quantity Needed: ";
            is >> qtyNeed;
            if (is.fail())
            {
                err_.message("Invalid Quantity Needed Entry");
                is.setstate(ios::failbit);
            }
            }
    
        }
        if (err_.isClear())
        {
            sku(tmp_sku);
            name(tmp_name);
            price(tmp_price);
            quantity(tmp_quantity);
            qtyNeeded(qtyNeed);
            taxed(taxed__);
        }
        return is;
    }
}

