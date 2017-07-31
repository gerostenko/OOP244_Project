// AmaProduct.h
#ifndef SICT_AMAPRODUCT_H__
#define SICT_AMAPRODUCT_H__

#include<iostream>
#include <cstring>
#include "Streamable.h"
#include "general.h"
#include "Product.h"
#include "ErrorMessage.h"

using namespace std;

namespace sict
{
    class AmaProduct : public Product
    {
    private:
        char fileTag_;
        char unit_[11];
    protected:
        ErrorMessage err_;
    public:
        AmaProduct(char filetag = 'N');
        const char* unit()const;
        void unit(const char* value);
        virtual std::fstream& store(std::fstream& file, bool addNewLine = true)const;
        virtual std::fstream& load(std::fstream& file);
        virtual std::ostream& write(std::ostream& os, bool linear)const;
        virtual std::istream& read(std::istream& is);

    };
}

#endif


