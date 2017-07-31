// Product.h

#ifndef SICT_PRODUCT_H__
#define SICT_PRODUCT_H__

#include<iostream>
#include <cstring>
#include "Streamable.h"
#include "general.h"
using namespace std;
namespace sict
{
    class Product : public Streamable
    {
    private:
        char sku_[MAX_SKU_LEN+1];
        char* name_;
        double price_;
        bool taxed_;
        int quantity_;
        int qtyNeeded_;

        void setEmpty();
        void setTheObject(const Product& obj);
    public:
        Product();
        Product(const char* sku_btch, const char* name_btch, bool taxed_btch = true, double price_btch = 0, int qty = 0);
        Product(const Product&  obj);
        Product& operator=(const Product&  obj);
        virtual ~Product() { delete[] name_; };

        //Setters
        void sku(const char* sku);
        void price(double price);
        void name(const char* name);
        void taxed(bool taxed_btch);
        void quantity(int qty);
        void qtyNeeded(int qtyNeed);

        //Getters
        const char* sku()const;
        double price() const;
        const char* name() const;
        bool taxed() const;
        int quantity() const;
        int qtyNeeded() const;

        double cost() const;
        bool isEmpty() const;
        bool operator== (const char* sku)const;
        int operator+=(int qty);
        int operator-=(int qty);

    };
        double operator+=(double& price, const Product& RO);
        std::istream& operator>> (std::istream& istr, Product& obj);
        std::ostream& operator<< (std::ostream& ostr, const Product& obj);

}



#endif