#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include <cstring>
#include "Product.h"

using namespace std;

namespace sict
{
    void Product::setEmpty()
    {
       sku_[0] = '\0';
       name_ = nullptr;
       price_ = 0;
       quantity_ = 0;
       qtyNeeded_ = 0;
    }
    Product::Product()
    {
        setEmpty();
    }
    Product::Product(const char* sku_btch, const char* name_btch, bool taxed_btch, double price_btch, int qty)
    {
        if (sku_btch != '\0' && name_btch != nullptr)
        {
            sku(sku_btch);
            name(name_btch);
            quantity(0);
            price(price_btch);
            qtyNeeded(qty);
            taxed(taxed_btch);
        }
    }
    void Product::setTheObject(const Product& obj)
    {
        sku(obj.sku());
        name(obj.name());
        quantity(obj.quantity());
        price(obj.price());
        qtyNeeded(obj.qtyNeeded());
        taxed(obj.taxed());
    }
    Product::Product(const Product& obj)
    {
        setTheObject(obj);
    }
    Product& Product::operator=(const Product& obj)
    {
        if (this != &obj) {
            delete[] name_;
            setTheObject(obj);
        }
        return *this;
    }
    //Setters
    void Product::sku(const char* sku)
    {
        sku_[0] = '\0';
        strncpy(sku_, sku, MAX_SKU_LEN+1);
        sku_[MAX_SKU_LEN+1] = '\0';
    }
    void Product::name(const char* name)
    {
        name_ = new char[strlen(name)+1];
        strncpy(name_, name, strlen(name));
        name_[strlen(name)] = '\0';
    }
    void  Product::price(double price)
    {
        price_ = price;
    }
    void  Product::taxed(bool taxed_btch)
    {
        taxed_ = taxed_btch;
    }
    void  Product::quantity(int qty)
    {
        quantity_ = qty;
    }
    void  Product::qtyNeeded(int qtyNeed)
    {
        qtyNeeded_ = qtyNeed;
    }
    //Getters
    const char* Product::sku()const
    {
        return sku_;
    }
    double Product::price() const
    {
        return price_;
    }
    const char* Product::name() const
    {
        return name_;
    }
    bool Product::taxed() const
    {
        return taxed_;
    }
    int Product::quantity() const
    {
        return quantity_;
    }
    int Product::qtyNeeded() const
    {
        return qtyNeeded_;
    }
    double Product::cost() const
    {
        double newPrice = price();
        newPrice += price()*TAX;

        return taxed() ? newPrice : price();
    }
    bool Product::isEmpty() const
    {
        return sku_[0] == '\0';
    }
    bool Product::operator== (const char* sku)const
    {
        return strcmp(sku_, sku) == 0;
    }
    int Product::operator+=(int qty)
    {
        return quantity_ += qty;
    }
    int Product::operator-=(int qty)
    {
        return quantity_ -= qty;
    }

    double operator+=(double& price, const Product& RO)
    {
       return price += RO.cost()*RO.quantity();
    }
    std::istream& operator>> (std::istream& istr, Product& obj)
    {
        return obj.read(istr);
    }
    std::ostream& operator<< (std::ostream& ostr, const Product& obj)
    {
        return obj.write(ostr, true);
    }
}
