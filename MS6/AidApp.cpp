#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include <string>
#include "AidApp.h"

using namespace std;

namespace sict
{
    //function to dellocate all the products
    void AidApp::deallocateProduct()
    {
        for (int i = 0; i < MAX_NO_RECS; i++)
            product_[i] = nullptr;
    }
    //AidApp constructor
    AidApp::AidApp(const char* filename)
    {
        filename_[0] = '\0';
        strncpy(filename_, filename, strlen(filename) + 1);
        filename_[strlen(filename)] = '\0';

        deallocateProduct();

        noOfProducts_ = 0;

        loadRecs();
    }
    void AidApp::pause()const
    {
        cout << "Press Enter to continue..." << endl;
        cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
    }
    int AidApp::menu()
    {
        int choice;
        cout << "Disaster Aid Supply Management Program" << endl;
        cout << "1 - List products" << endl;
        cout << "2 - Display product" << endl;
        cout << "3 - Add non - perishable product" << endl;
        cout << "4 - Add perishable product" << endl;
        cout << "5 - Add to quantity of purchased products" << endl;
        cout << "0 - Exit program" << endl;
        cout << "> ";
        cin >> choice;
        cin.ignore(100, '\n');
        if (cin.fail())
        {
            choice = -1;
            cin.clear();
            cin.ignore(100, '\n');
        }
        else if (choice < 0 || choice > 5)
        {
            choice = -1;
        }
        cin.clear();

        return choice;
    }
    void AidApp::loadRecs()
    {
        int readIndex = 0;
        datafile_.open(filename_, ios::in);
        if (datafile_.fail())
        {
            datafile_.clear();
            datafile_.close();
            datafile_.open(filename_, ios::out);
            datafile_.close();
        }
        else
        {
            while (!datafile_.eof())
            {
                char isTaxed;
                datafile_ >> isTaxed;
                if (!datafile_.fail()) {
                    //delete product_[readIndex];
                    product_[readIndex] = nullptr;
                    if (isTaxed == 'P')
                    {
                        product_[readIndex] = new AmaPerishable;
                        datafile_.ignore();
                        product_[readIndex]->load(datafile_);
                        readIndex++;
                    }
                    else if (isTaxed == 'N')
                    {
                        product_[readIndex] = new AmaProduct;
                        datafile_.ignore();
                        product_[readIndex]->load(datafile_);
                        readIndex++;
                    }
                }
            }
            noOfProducts_ = readIndex;
            datafile_.close();
        }
    }
    void AidApp::saveRecs()
    {
        datafile_.open(filename_, ios::out);
        for (int i = 0; i < noOfProducts_; i++)
        {
            product_[i]->store(datafile_);
        }
        datafile_.close();
    }
    void  AidApp::listProducts()const
    {
        double totalPrice = 0;
        cout << " Row | SKU    | Product Name       | Cost  | QTY| Unit     |Need| Expiry" << endl;
        cout << "-----|--------|--------------------|-------|----|----------|----|----------" << endl;

        for (int i = 0; i < noOfProducts_; i++)
        {
            cout.clear();
            cout.setf(ios::fixed);
            cout.setf(ios::right);
            cout.width(4);
            cout << i + 1 << " | ";
            product_[i]->write(cout, true);
            cout << endl;
            if ((i + 1) % 10 == 0)
            {
                pause();
            }
            totalPrice += *product_[i];
        }
        cout << "---------------------------------------------------------------------------" << endl;
        cout.setf(ios::fixed);
        cout.precision(2);
        cout << "Total cost of support: $" << totalPrice << endl;
    }
    int AidApp::SearchProducts(const char* sku)const
    {
        int result = -1;
        for (int i = 0; i < noOfProducts_; i++)
        {
            if (*product_[i] == sku)
            {
                result = i;
            }
        }
        return result;
    }
    void AidApp::addQty(const char* sku)
    {
        int qty = 0, reqAmount = 0;
        int found = SearchProducts(sku);
        if (found != -1)
        {
            product_[found]->write(cout, false);
            cout << endl;
            cout << "Please enter the number of purchased items: ";
            cin >> qty;
            cin.clear();
            cin.ignore();
            if (cin.fail())
            {
                cout << "Invalid quantity value! " << endl;
            }
            else
            {
                reqAmount = product_[found]->qtyNeeded() - product_[found]->quantity();
                if (qty <= reqAmount)
                {
                    *product_[found] += qty;
                }
                else
                {
                    int leftovers = qty - reqAmount;
                    *product_[found] += reqAmount;
                    cout << "Too many items; only " << reqAmount << " is needed, please return the extra " << leftovers << " items." << endl;

                }
                saveRecs();
                cout << "Updated!" << endl;
                cin.clear();
            }

        }
        else
        {
            cout << "Not found!" << endl;
        }
    }
    void AidApp::addProduct(bool isPerishable)
    {
        if (isPerishable)
        {
            AmaPerishable tmp;
            if (tmp.read(cin).fail())
            {
                tmp.write(cout, false);
            }
            else
            {
                product_[noOfProducts_++] = &tmp;
                saveRecs();
            }

        }
        else
        {
            AmaProduct tmp;
            if (tmp.read(cin).fail())
            {
                tmp.write(cout, false);
            }
            else
            {
                product_[noOfProducts_++] = &tmp;
                saveRecs();
            }

        }

    }
    int AidApp::run()
    {
        char sku_[MAX_SKU_LEN + 1];
        int found = 0;
        int breakTheLoop = 1;
        while (breakTheLoop) {
            sku_[0] = '\0';
            switch (menu()) {
            case 1:
                listProducts();
                pause();
                break;
            case 2:
                cin.clear();
                cout << "Please enter the SKU :";
                cin >> sku_;
                cin.ignore();
                found = SearchProducts(sku_);
                if (found == -1)
                {
                    cout << "Not found!" << endl;
                }
                else
                {
                    product_[found]->write(cout, false);
                }
                pause();
                break;
            case 3:
                addProduct(false);
                loadRecs();
                pause();
                break;
            case 4:
                cin.clear();
                addProduct(true);
                cin.ignore();
                loadRecs();
                pause();
                break;
            case 5:
                cout << "Please enter the SKU :";
                cin >> sku_;
                addQty(sku_);
                pause();
                break;
            case 0:
                breakTheLoop = 0;
                cout << "Goodbye!!" << endl;
                break;
            default:
                cout << "===Invalid Selection, try again.===" << endl;
                pause();
                break;
            }
        }
        return breakTheLoop;
    }
}