// AmaPerishable.h
#ifndef SICT_AMAPERISHABLE_H__
#define SICT_AMAPERISHABLE_H__

#include<iostream>
#include <cstring>
#include "Streamable.h"
#include "general.h"
#include "Date.h"
#include "ErrorMessage.h"
#include "AmaProduct.h"

using namespace std;

namespace sict
{
    class AmaPerishable : public AmaProduct
    {
    private:
        Date expiry_;
    public:
        AmaPerishable(char filetag = 'P') : AmaProduct(filetag) {};
        const Date& expiry()const;
        void expiry(const Date &value);
        std::fstream& store(std::fstream& file, bool addNewLine = true)const;
        std::fstream& load(std::fstream& file);
        std::ostream& write(std::ostream& os, bool linear)const;
        std::istream& read(std::istream& is);

    };


}

#endif