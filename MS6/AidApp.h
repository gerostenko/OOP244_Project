#ifndef SICT_AIDAPP_H__
#define SICT_AIDAPP_H__
#include <iostream>
#include <fstream>
#include "general.h"
#include"Product.h"
#include"AmaProduct.h"
#include"AmaPerishable.h"
#include"ErrorMessage.h"

namespace sict {
    class AidApp
    {
    private:
        char filename_[256];
        Product* product_[MAX_NO_RECS];
        fstream datafile_;
        int noOfProducts_;

    public:
        AidApp(const char* filename);
        AidApp(const AidApp& em) = delete;
        AidApp& operator=(const AidApp& em) = delete;
        int run();
    private:
        void deallocateProduct();
        void pause()const;
        int menu(); 
        void loadRecs();
        void saveRecs();
        void listProducts()const;
        int SearchProducts(const char* sku)const;
        void addQty(const char* sku);
        void addProduct(bool isPerishable);
    };
}
#endif